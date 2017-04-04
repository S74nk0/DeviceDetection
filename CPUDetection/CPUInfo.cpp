#include "CPUInfo.h"

#include <stdexcept>
#include <iostream>

using namespace std;

CPUInfo::CPUInfo()
{
}


CPUInfo::~CPUInfo()
{
}


// static
const char* CPUInfo::mapVendor(cpu_vendor_t vendor) {
	switch (vendor) {
	case VENDOR_INTEL:
		return "intel";

	case VENDOR_AMD:
		return "amd";

	case VENDOR_CYRIX:
		return "cyrix";

	case VENDOR_NEXGEN:
		return "nexgen";

	case VENDOR_TRANSMETA:
		return "transmeta";

	case VENDOR_UMC:
		return "umc";

	case VENDOR_CENTAUR:
		return "idt";

	case VENDOR_RISE:
		return "rise";

	case VENDOR_SIS:
		return "sis";

	case VENDOR_NSC:
		return "nsc";

	default:
		return "unknown";
	}
}

// static 
void CPUInfo::fillFeatures(CPUFeatures &Features, cpu_id_t& cpuData) {
	Features.SSE2 = cpuData.flags[CPU_FEATURE_SSE2] == 1;
	Features.SSE41 = cpuData.flags[CPU_FEATURE_SSE4_1] == 1;
	Features.SSE42 = cpuData.flags[CPU_FEATURE_SSE4_2] == 1;
	Features.AES = cpuData.flags[CPU_FEATURE_AES] == 1;
	Features.AVX = cpuData.flags[CPU_FEATURE_AVX] == 1;
	Features.AVX2 = cpuData.flags[CPU_FEATURE_AVX2] == 1;
}

bool CPUInfo::Query() {
	const unsigned int UUID_SIZE = 128;
	try {
		cpu_raw_data_t raw;
		if (cpuid_get_raw_data(&raw) < 0) {
			throw std::runtime_error("Could not execute CPUID");
		}

		cpu_id_t cpuData;
		if (cpu_identify(&raw, &cpuData) < 0) {
			throw std::runtime_error("Could not parse CPUID data");
		}

		VendorName = cpuData.vendor_str;
		Vendor = mapVendor(cpuData.vendor);
		//VendorNumber = cpuData.vendor;
		Brand = cpuData.brand_str;
		CodeName = cpuData.cpu_codename;
		PhysicalCores = cpuData.num_cores;
		LogicalCores = cpuData.num_logical_cpus;
		TotalCores = cpuData.total_logical_cpus;
		ClockSpeed = cpu_clock();

		PhysicalCPUsCount = TotalCores / LogicalCores;
		
		fillFeatures(Features, cpuData);
	}
	catch (runtime_error &err) {
		return false;
	}
	return true;
}

std::string getTrueFalse(bool b) {
	return b ? "true" : "false";
}

void CPUInfo::PrintInfo() {
	cout << "{" << endl;
	cout << "\t\"Brand\" : \"" << Brand << "\"," << endl; // string

	cout << "\t\"PhysicalCores\" : " << PhysicalCores << "," << endl; // num
	cout << "\t\"LogicalCores\" : " << LogicalCores << "," << endl; // num
	cout << "\t\"TotalCores\" : " << TotalCores << "," << endl; // num
	cout << "\t\"PhysicalCPUsCount\" : " << PhysicalCPUsCount << "," << endl; // num

	cout << "\t\"Features\" : {" << endl;
	cout << "\t\t\"AVX2\" : " << getTrueFalse(Features.AVX2) << "," << endl; // bool
	cout << "\t\t\"AVX\" : " << getTrueFalse(Features.AVX) << "," << endl; // bool
	cout << "\t\t\"AES\" : " << getTrueFalse(Features.AES) << "," << endl; // bool
	cout << "\t\t\"SSE42\" : " << getTrueFalse(Features.SSE42) << "," << endl; // bool
	cout << "\t\t\"SSE41\" : " << getTrueFalse(Features.SSE41) << "," << endl; // bool
	cout << "\t\t\"SSE2\" : " << getTrueFalse(Features.SSE2) << endl; // bool
	cout << "\t}" << endl;
	cout << "}" << endl;
}

void CPUInfo::PrintInfo_d() {
	cout << "{";
	cout << "\"Brand\" : \"" << Brand << "\","; // string

	cout << "\"PhysicalCores\" : " << PhysicalCores << ","; // num
	cout << "\"LogicalCores\" : " << LogicalCores << ","; // num
	cout << "\"TotalCores\" : " << TotalCores << ","; // num
	cout << "\"PhysicalCPUsCount\" : " << PhysicalCPUsCount << ","; // num

	cout << "\"Features\" : {";
	cout << "\"AVX2\" : " << getTrueFalse(Features.AVX2) << ","; // bool
	cout << "\"AVX\" : " << getTrueFalse(Features.AVX) << ","; // bool
	cout << "\"AES\" : " << getTrueFalse(Features.AES) << ","; // bool
	cout << "\"SSE42\" : " << getTrueFalse(Features.SSE42) << ","; // bool
	cout << "\"SSE41\" : " << getTrueFalse(Features.SSE41) << ","; // bool
	cout << "\"SSE2\" : " << getTrueFalse(Features.SSE2); // bool
	cout << "}";
	cout << "}" << endl;
}
#pragma once

#include <libcpuid.h>

#include <string>
#include "CPUFeatures.h"

class CPUInfo
{
public:
	CPUInfo();
	~CPUInfo();

	std::string VendorName;
	std::string Vendor;
	//VendorNumber;
	std::string Brand;
	std::string CodeName;
	int32_t PhysicalCores;
	int32_t LogicalCores;
	int32_t TotalCores;
	int ClockSpeed;

	int32_t PhysicalCPUsCount;

	CPUFeatures Features;

	bool Query();

	void PrintInfo();

	// statics
	static const char* mapVendor(cpu_vendor_t vendor);
	static void fillFeatures(CPUFeatures &Features, cpu_id_t& cpuData);
};


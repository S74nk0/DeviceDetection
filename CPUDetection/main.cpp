#include "CPUInfo.h"

int main(int argc, char* argv[]) {
	CPUInfo detection;
	if (detection.Query()) {
		if (argc < 2) {
			detection.PrintInfo_d();
		}
		else {
			detection.PrintInfo();
		}
	}
	return 0;
}
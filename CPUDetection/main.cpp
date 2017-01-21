#include "CPUInfo.h"

int main() {
	CPUInfo detection;
	if (detection.Query()) {
		detection.PrintInfo();
	}
	return 0;
}
#include "MemoryUsageInfo.h"


MemoryUsageInfo::MemoryUsageInfo()
{
}


MemoryUsageInfo::~MemoryUsageInfo()
{
}

std::pair<long, long> MemoryUsageInfo::getMemoryUsageInfo()
{
	MEMORYSTATUSEX statex;

	statex.dwLength = sizeof(statex);

	GlobalMemoryStatusEx(&statex);

	/*_tprintf(TEXT("There is  %*ld percent of memory in use.\n"), WIDTH, statex.dwMemoryLoad);
	_tprintf(TEXT("There are %*I64d total Mbytes of physical memory.\n"), WIDTH, statex.ullTotalPhys / (1024*1024));
	_tprintf(TEXT("There are %*I64d free Mbytes of physical memory.\n"), WIDTH, statex.ullAvailPhys / (1024 * 1024));
	_tprintf(TEXT("There are %*I64d total Mbytes of paging file.\n"), WIDTH, statex.ullTotalPageFile / (1024 * 1024));
	_tprintf(TEXT("There are %*I64d free Mbytes of paging file.\n"), WIDTH, statex.ullAvailPageFile / (1024 * 1024));
	_tprintf(TEXT("There are %*I64d total Mbytes of virtual memory.\n"), WIDTH, statex.ullTotalVirtual / (1024 * 1024));
	_tprintf(TEXT("There are %*I64d free Mbytes of virtual memory.\n"), WIDTH, statex.ullAvailVirtual / (1024 * 1024));
	_tprintf(TEXT("There are %*I64d free Mbytes of extended memory.\n"), WIDTH, statex.ullAvailExtendedVirtual / (1024 * 1024));*/

	return std::make_pair(statex.dwMemoryLoad/*statex.ullTotalPhys-statex.ullAvailPhys*/, statex.ullAvailPhys);
}

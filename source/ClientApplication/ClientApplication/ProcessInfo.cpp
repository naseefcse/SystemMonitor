#include "ProcessInfo.h"


ProcessInfo::ProcessInfo()
{
}


ProcessInfo::~ProcessInfo()
{
}

int ProcessInfo::getNumberOfRunningProcesses()
{
	DWORD aProcesses[1024], cbNeeded, cProcesses;

	if (!EnumProcesses(aProcesses, sizeof(aProcesses), &cbNeeded))
	{
		return -1;
	}

	cProcesses = cbNeeded / sizeof(DWORD);

	return cProcesses;
}

CpuAndMemoryInfoForEachProcess ProcessInfo::getProcessInfo(int processID)
{
	CpuAndMemoryInfoForEachProcess info;

	TCHAR szProcessName[MAX_PATH] = TEXT("<unknown>");

	// Get a handle to the process.

	HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION |
		PROCESS_VM_READ,
		FALSE, processID);

	// Get the process name.

	PROCESS_MEMORY_COUNTERS pmc;

	if (NULL != hProcess)
	{
		HMODULE hMod;
		DWORD cbNeeded;

		if (EnumProcessModules(hProcess, &hMod, sizeof(hMod),
			&cbNeeded))
		{
			GetModuleBaseName(hProcess, hMod, szProcessName,
				sizeof(szProcessName) / sizeof(TCHAR));
		}

		if (GetProcessMemoryInfo(hProcess, &pmc, sizeof(pmc)))
		{
			//printf("Memory Info Paisi\n");
			info.memoryConsumed = pmc.WorkingSetSize/(1024);
		}

		CpuUsage cpuUsage;

		info.cpuConsumed = cpuUsage.GetUsage(hProcess);
	}

	info.processName = TcharToStdString(szProcessName);

	///printf("ProcessName: %s, Memory Usage %ld, CPU Usage %.03lf\n", info.processName.c_str(), info.memoryConsumed, info.cpuConsumed);


	return info;
}

std::vector<CpuAndMemoryInfoForEachProcess> ProcessInfo::getAllProcessInfo()
{
	std::vector<CpuAndMemoryInfoForEachProcess> data;

	DWORD aProcesses[1024], cbNeeded, cProcesses;

	if (!EnumProcesses(aProcesses, sizeof(aProcesses), &cbNeeded))
	{
		return data;
	}

	cProcesses = cbNeeded / sizeof(DWORD);

	for (int i = 0; i < cProcesses; i++)
	{
		CpuAndMemoryInfoForEachProcess info = getProcessInfo(aProcesses[i]);

		data.push_back(info);
	}

	return data;
}

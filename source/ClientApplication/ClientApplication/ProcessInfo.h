#ifndef PROCESS_INFO_H
#define PROCESS_INFO_H

#pragma once

#include "windows.h"
#include "psapi.h"
#include <iostream>
#include <stdio.h>
#include <vector>

#include "CpuUsage.h"




struct CpuAndMemoryInfoForEachProcess
{
	std::string processName;
	long memoryConsumed;
	double cpuConsumed;
};

class ProcessInfo
{
public:
	ProcessInfo();
	virtual ~ProcessInfo();
	int getNumberOfRunningProcesses();

	std::vector<CpuAndMemoryInfoForEachProcess> getAllProcessInfo();

private:
	CpuAndMemoryInfoForEachProcess getProcessInfo(int processID);

	ULARGE_INTEGER lastCPU, lastSysCPU, lastUserCPU;
	int numProcessors;
	HANDLE self;


	void init(HANDLE hProcess){
		SYSTEM_INFO sysInfo;
		FILETIME ftime, fsys, fuser;


		GetSystemInfo(&sysInfo);
		numProcessors = sysInfo.dwNumberOfProcessors;


		GetSystemTimeAsFileTime(&ftime);
		memcpy(&lastCPU, &ftime, sizeof(FILETIME));

		self = hProcess;

		self = GetCurrentProcess();

		GetProcessTimes(self, &ftime, &ftime, &fsys, &fuser);
		memcpy(&lastSysCPU, &fsys, sizeof(FILETIME));
		memcpy(&lastUserCPU, &fuser, sizeof(FILETIME));
	}


	double getCurrentValue(){
		FILETIME ftime, fsys, fuser;
		ULARGE_INTEGER now, sys, user;
		double percent;


		GetSystemTimeAsFileTime(&ftime);
		memcpy(&now, &ftime, sizeof(FILETIME));


		GetProcessTimes(self, &ftime, &ftime, &fsys, &fuser);
		memcpy(&sys, &fsys, sizeof(FILETIME));
		memcpy(&user, &fuser, sizeof(FILETIME));
		percent = (sys.QuadPart - lastSysCPU.QuadPart) +
			(user.QuadPart - lastUserCPU.QuadPart);
		percent /= (now.QuadPart - lastCPU.QuadPart);
		percent /= numProcessors;
		lastCPU = now;
		lastUserCPU = user;
		lastSysCPU = sys;


		return percent * 100;
	}

	std::string TcharToStdString(TCHAR* arr)
	{
		std::wstring arr_w(arr);
		std::string arr_s(arr_w.begin(), arr_w.end());
		return arr_s;
	}

};

#endif

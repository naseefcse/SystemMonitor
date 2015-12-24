#ifndef CPU_USAGE_CALCULATOR
#define CPU_USAGE_CALCULATOR
#pragma once

#include "windows.h"
#include <stdio.h>
#include "tchar.h"

#define WIDTH 7

typedef BOOL(__stdcall * pfnGetSystemTimes)(LPFILETIME lpIdleTime, LPFILETIME lpKernelTime, LPFILETIME lpUserTime);
static pfnGetSystemTimes s_pfnGetSystemTimes = NULL;

static HMODULE s_hKernel = NULL;
//-----------------------------------------------------
class CCpuUsageCalculator
{
public:
	CCpuUsageCalculator();
	virtual ~CCpuUsageCalculator();

	char getCPUUsage();

	char calculateCPUUsage();

	char m_fCPUUsage;

	void GetSystemTimesAddress()
	{
		if (s_hKernel == NULL)
		{
			s_hKernel = LoadLibrary(L"Kernel32.dll");
			if (s_hKernel != NULL)
			{
				s_pfnGetSystemTimes = (pfnGetSystemTimes)GetProcAddress(s_hKernel, "GetSystemTimes");
				if (s_pfnGetSystemTimes == NULL)
				{
					FreeLibrary(s_hKernel); s_hKernel = NULL;
				}
			}
		}
	}

};
#endif

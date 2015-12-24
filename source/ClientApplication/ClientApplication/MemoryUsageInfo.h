#ifndef MEMORY_USAGE_INFO_H
#define MEMORY_USAGE_INFO_H
#pragma once

#include <iostream>
#include "windows.h"
#include <tchar.h>

#define WIDTH 7

class MemoryUsageInfo
{
public:
	MemoryUsageInfo();
	virtual ~MemoryUsageInfo();
	std::pair<long, long> getMemoryUsageInfo();
};

#endif


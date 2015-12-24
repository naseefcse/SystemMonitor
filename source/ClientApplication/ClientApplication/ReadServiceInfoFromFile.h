#ifndef READ_SERVICE_INFO_FROM_FILE
#define READ_SERVICE_INFO_FROM_FILE

#include <stdio.h>
#include <iostream>
#include <vector>
#include <windows.h>

#pragma once
class ReadServiceInfoFromFile
{
public:
	ReadServiceInfoFromFile();
	virtual ~ReadServiceInfoFromFile();
	static std::vector<std::string> getAuthentiactionInfo(FILE* pFile);
};

#endif



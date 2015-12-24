#include "Utils.h"

std::string wStringToStdString(std::wstring ws)
{
	std::string s(ws.begin(), ws.end());

	return s;
}
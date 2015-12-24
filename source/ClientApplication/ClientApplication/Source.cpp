#include "CpuUsageCalculator.h"
#include "MemoryUsageInfo.h"
#include "ProcessInfo.h"
#include "HTTPNotify.h"

int main()
{
	CCpuUsageCalculator obj;

	MemoryUsageInfo obb;

	ProcessInfo pObj;

	printf("Number of Running Processes %d\n", pObj.getNumberOfRunningProcesses());

	pObj.getAllProcessInfo();

	obb.getMemoryUsageInfo();

	try{

		HTTPNotify httpn;

		httpn.initateHTTPClient();
	}
	catch (...)
	{
		printf("Got Exception, exiting...\n");
		Sleep(1000);
		return 0;
	}

	int t;
	scanf_s("%d", &t);

	return 0;
}
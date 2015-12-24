#if 1
#include "HTTPNotify.h"
#include <fstream>


HTTPNotify::HTTPNotify()
{
}


HTTPNotify::~HTTPNotify()
{
}

void HTTPNotify::initateHTTPClient()
{
	std::wstring linkUrl = constructAPIUrl();

	http_client client(linkUrl);


	try{
		make_request(client, methods::POST, json::value::null());
	}
	catch (...)
	{
		printf("No Response or wrong response from server\n");
		exit(1);
	}
	
}

void HTTPNotify::make_request(http_client & client, method mtd, json::value const & jvalue)
{
	make_task_request(client, mtd, jvalue);
	//		.then([](http_response response)
	//	{
	//		if (response.status_code() == status_codes::OK)
	//		{
	//			//return response.extract_json();
	//		}
	//		else
	//		{
	//			//printf("Something wrong happened\n");
	//		}
	//		return pplx::task_from_result(json::value());
	//	});/*
		 //  .then([](pplx::task<json::value> previousTask)*/
		/*{
		})
		.wait();*/
}

pplx::task<http_response> HTTPNotify::make_task_request(http_client & client, method mtd, json::value const & jvalue)
{
	std::vector<CpuAndMemoryInfoForEachProcess> data;

	CCpuUsageCalculator cpu;
	MemoryUsageInfo memU;

	ProcessInfo prInfo;

	int avg = 0;

	for (int i = 0; i < 20; i++)
	{
		avg += cpu.getCPUUsage();
		Sleep(500);
	}

	std::string proc_info = "";

	data = prInfo.getAllProcessInfo();

	for (int i = 0; i < data.size(); i++)
	{
		CpuAndMemoryInfoForEachProcess cpuAndMemInfo = data[i];

		proc_info += "ProcessName: " + cpuAndMemInfo.processName + " MemoryUsage: " + std::to_string(cpuAndMemInfo.memoryConsumed) + ";";
	}

	printf("CPU Usage:%s, Memory Usage: %s, Number of Running Processes: %s\n", std::to_string(avg/20).c_str(), std::to_string(memU.getMemoryUsageInfo().first).c_str()
		, std::to_string(data.size()).c_str());

	std::string cpuUsage = "&cpu=" + std::to_string(avg/20);

	std::string memUsage = "&mem=" + std::to_string(memU.getMemoryUsageInfo().first);

	std::string sProcess = "&process=" + std::to_string(data.size());

	std::string sss = constructInfoUrl() + cpuUsage + memUsage + sProcess;

	utility::string_t url;
	url.assign(sss.begin(), sss.end());

	return client.request(mtd, url);
}

std::string HTTPNotify::constructInfoUrl()
{
	if (urlData.size() < 3)
		return "";

	std::string str = "";

	str += urlData[0];
	str += "?";
	str += "pass=" + urlData[1];

	return str;
}

std::wstring HTTPNotify::constructAPIUrl()
{
	FILE* file = fopen("serviceInfo.txt", "r");

	std::string sAuthMessage = "";

	std::ifstream fin("serviceInfo.txt");

	urlData.clear();

	if(!fin) {
		std::cout << "Could not open file" << std::endl;
		exit(1);
		return L"";
	}

	std::string word; // You only need one word at a time.

	while (fin >> word) 
	{
		urlData.push_back(word);
	}


	if (urlData.size() < 3)
	{
		return L"";
	}

	std::string url = "";

	url += urlData[2];

	std::wstring ws;
	ws.assign(url.begin(), url.end());

	return ws;
}
#endif

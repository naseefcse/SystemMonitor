#if 1
#ifndef HTTP_NOTIFY_H
#define HTTP_NOTIFY_H

#pragma once

#include <iostream>
#include <iomanip>
#include <sstream>
#include <thread>
#include <chrono>
#include <ctime>

#include <cpprest/http_client.h>
#include <cpprest/http_headers.h>
#include <cpprest/json.h>
#include <iostream>
#include "MemoryUsageInfo.h"
#include "CpuUsage.h"
#include "CpuUsageCalculator.h"
#include "ReadServiceInfoFromFile.h"
#include "ProcessInfo.h"

using namespace web;
using namespace web::http;
using namespace web::http::client;

class HTTPNotify
{
public:
	HTTPNotify();
	virtual ~HTTPNotify();
	void initateHTTPClient();
private:
	void make_request(http_client & client, method mtd, json::value const & jvalue);
	pplx::task<http_response> make_task_request(http_client & client, method mtd, json::value const & jvalue);
	utility::string_t constructAPIUrl();
	std::string constructInfoUrl();
	std::vector<std::string> urlData;
};

#endif
#endif



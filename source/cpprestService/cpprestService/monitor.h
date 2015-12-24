#ifndef MONITOR_H
#define MONITOR_H

#include <cpprest/http_listener.h>
#include <cpprest/json.h>
#include "config.h"
#include "mailsender.h"

using namespace std;
using namespace web;
using namespace utility;
using namespace http;
using namespace web::http::experimental::listener;

class Monitor
{
public:
    Monitor(utility::string_t baseUrl, string configFile);

    pplx::task<void> open() { return m_listener.open(); }
    pplx::task<void> close() { return m_listener.close(); }

private:

    void handle_post(http_request message);

    http_listener m_listener;
    Config *config;
    MailSender *mailSender;
};

#endif // MONITOR_H

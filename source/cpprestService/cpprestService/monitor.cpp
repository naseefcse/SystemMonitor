#include "monitor.h"
#include "mailsender.h"
#include "Utils.h"

Monitor::Monitor(string_t baseUrl, string configFile) : m_listener(baseUrl)
{
    m_listener.support(methods::POST, std::bind(&Monitor::handle_post, this, std::placeholders::_1));
    config = new Config();
    bool isLoaded = config->loadConfig(configFile);
    if (!isLoaded)
    {
        ucout<<"Configuration is not loaded"<<endl;
    }
    mailSender = new MailSender(config->getAdminInfo());
}

void Monitor::handle_post(http_request message)
{
    ucout <<  message.to_string() << endl;

    auto paths = uri::split_path(uri::decode(message.relative_uri().path()));
    ucout<<paths.size()<<endl;
    if (paths.empty())
    {
        json::value val("user not given");
        message.reply(status_codes::NotFound, val);
        return;
    }
    Client client;
    client.userName = wStringToStdString(paths[0]);

    cout<<"user = "<<client.userName<<endl;

    std::map<utility::string_t, utility::string_t> query = uri::split_query(uri::decode(message.request_uri().query()));

    string details;
    for (auto it=query.begin(); it!=query.end(); it++)
    {
		string type = wStringToStdString((*it).first);
		string value = wStringToStdString((*it).second);

        cout<<type<<" "<<value<<endl;

        if (type == "pass")
        {
            client.password = value;
        }
        else if (type == "cpu")
        {
            client.cpu = stoi(value);
        }
        else if (type == "mem")
        {
            client.mem = stoi(value);
        }
        else if (type == "process")
        {
            client.process = stoi(value);
        }
        else if (type == "proc_details")
        {
            details = value;
        }
    }
	fstream outputFile;
	outputFile.open(client.userName + ".log", std::fstream::app);
	outputFile << "******File Opened*******" << endl;
	outputFile << "CPU Usage: " << client.cpu<< "%" << endl;
	outputFile << "Memory Usage: " << client.mem<< "%" << endl;
	outputFile << "Number of Running Processes: " << client.process << endl;
	outputFile << "*******File Closed*******"<<endl<<endl;
	outputFile.close();

    auto status = config->checkStatus(client);
    json::value response;
    status_code responseCode;
    cout<<status<<" "<<"details "<<details<<endl;
    switch (status) {
    case Config::Status::OK:
    {
        response = json::value("OK");
        responseCode = status_codes::OK;
        break;
    }
    case Config::Status::AUTH_ERROR:
    {
        response = json::value("Auth Error");
        responseCode = status_codes::Forbidden;
        break;
    }
    case Config::Status::NOT_FOUND:
    {
        response = json::value("User not found");
        responseCode = status_codes::NotFound;
        break;
    }
    case Config::Status::LIMIT_EXCEEDED:
    {
        response = json::value("limit exceeded");
        responseCode = status_codes::OK;
        mailSender->notifyUser(config->getActualClient(client.userName), client);
        break;
    }
    default:
        break;
    }
    message.reply(responseCode, response);
};

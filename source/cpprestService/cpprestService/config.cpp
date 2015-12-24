#include "config.h"
#include <tinyxml2.h>
#include <fstream>
#include <iostream>

using namespace std;
using namespace tinyxml2;

Config::Config()
{
    admin.name="NA";
    admin.mail="NA";
}

bool Config::loadConfig(string configFile)
{
    XMLDocument doc;
    doc.LoadFile(configFile.c_str());
    if (doc.Error())
    {
        cout<<doc.ErrorName()<<endl;
        return false;
    }

    auto monitorElement = doc.FirstChildElement("monitor");
    if (!monitorElement)
    {
        return false;
    }

    auto adminElement = monitorElement->FirstChildElement("admin");
    if (!adminElement) return false;
    admin.name = adminElement->FirstChildElement("name")->GetText();
    admin.mail = adminElement->FirstChildElement("mail")->GetText();
    admin.password = adminElement->FirstChildElement("password")->GetText();
    cout<<admin.name<<" "<<admin.mail<<" "<<admin.password<<endl;


    auto clientsElement = monitorElement->FirstChildElement("clients");
    if (!clientsElement) return false;


    for (auto clientElement = clientsElement->FirstChildElement(); clientElement; clientElement = clientElement->NextSiblingElement())
    {
        Client client;
        client.userName = clientElement->Attribute("login");
        client.mail = clientElement->Attribute("mail");
        client.password = clientElement->Attribute("pass");

        for (auto alertElement = clientElement->FirstChildElement(); alertElement; alertElement = alertElement->NextSiblingElement())
        {
            string type = alertElement->Attribute("type");
            string limit = alertElement->Attribute("limit");

            if (type == "memory")
            {
                limit.pop_back();
                client.mem = stoi(limit);
            }
            else if (type == "cpu")
            {
                limit.pop_back();
                client.cpu = stoi(limit);
            }
            else if (type == "processes")
            {
                client.process = stoi(limit);
            }
        }

        clientMap[client.userName] = client;
    }
    return true;
}

Config::Status Config::checkStatus(Client client)
{
    auto it = clientMap.find(client.userName);
    if (it == clientMap.end())
    {
        return Status::NOT_FOUND;
    }

    Client actualClient = (*it).second;
    if (actualClient.password != client.password)
    {
        return Status::AUTH_ERROR;
    }

    if (actualClient.cpu < client.cpu ||
            actualClient.mem < client.mem ||
            actualClient.process < client.process)
    {
        return Status::LIMIT_EXCEEDED;
    }

    return Status::OK;
}

Client Config::getActualClient(string userName)
{
    return clientMap[userName];
}

Admin Config::getAdminInfo()
{
    return admin;
}

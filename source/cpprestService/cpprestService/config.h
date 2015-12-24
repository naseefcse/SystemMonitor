#ifndef CLIENTS_H
#define CLIENTS_H

#include <string>
#include <unordered_map>
#include "client.h"

using namespace std;

class Config
{
public:
    enum Status {
        OK,
        NOT_FOUND,
        AUTH_ERROR,
        LIMIT_EXCEEDED
    };

    Config();
    bool loadConfig(string configFile);
    Status checkStatus(Client client);
    Client getActualClient(string userName);
    Admin getAdminInfo();

private:
    unordered_map<string, Client> clientMap;
    Admin admin;
};

#endif // CLIENTS_H

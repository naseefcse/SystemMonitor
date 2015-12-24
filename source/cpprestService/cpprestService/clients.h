#ifndef CLIENTS_H
#define CLIENTS_H

#include <string>
#include <unordered_map>

using namespace std;

struct Client
{
    string userName;
    string password;
    int cpu;
    int mem;
    int process;
};

class Clients
{
public:
    enum Status {
        OK,
        NOT_FOUND,
        AUTH_ERROR,
        LIMIT_EXCEEDED
    };

    Clients();
    Status checkStatus(Client client);

private:
    unordered_map<string, Client> clientMap;
};

#endif // CLIENTS_H

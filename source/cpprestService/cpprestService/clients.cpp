#include "clients.h"

Clients::Clients()
{
    clientMap["dipal"] = {"dipal", "abcd", 20,50,50};
}

Clients::Status Clients::checkStatus(Client client)
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

    if (actualClient.cpu <= client.cpu ||
            actualClient.mem <= client.mem ||
            actualClient.process <= client.process)
    {
        return Status::LIMIT_EXCEEDED;
    }

    return Status::OK;
}

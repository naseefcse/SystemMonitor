#ifndef MAILSENDER_H
#define MAILSENDER_H

#include "client.h""
#include <thread>
#include <queue>

using namespace std;
class MailSender
{
public:
    MailSender(Admin admin);
    ~MailSender();
    void notifyUser(Client actualClient, Client currentStatus);

private:
    void run();
	void sendMail(Admin admin, Client actualClient, Client currentCleintStatus);
    Admin admin;
    thread t;
    bool isRunning{false};
    queue<pair<Client, Client> > q;
};

#endif // MAILSENDER_H

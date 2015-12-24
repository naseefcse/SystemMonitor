#include "mailsender.h"

#include <stdio.h>
#include <string.h>
#include <iostream>
#include "smtp/CSmtp.h"

MailSender::MailSender(Admin admin) : admin(admin)
{
    isRunning = true;
    t = thread(&MailSender::run, this);
    t.detach();
}

MailSender::~MailSender()
{
    isRunning = false;
}

void MailSender::run()
{
    while (isRunning)
    {
        if (!q.empty())
        {
            auto pop = q.front();
            q.pop();
            sendMail(admin,pop.first, pop.second);
        }

        this_thread::sleep_for(chrono::milliseconds(1000));
    }
}

void MailSender::sendMail(Admin admin, Client actualClient, Client currentCleintStatus)
{
	bool bError = false;
	try
	{
		CSmtp mail;
		cout << admin.mail << " " << admin.password << endl;

		cout << "Sending to: " << actualClient.mail << endl;
		string str;
		mail.SetSMTPServer("smtp.gmail.com", 587);
		mail.SetSecurityType(USE_TLS);
		mail.SetLogin(admin.mail.c_str());
		mail.SetPassword(admin.password.c_str());
		mail.SetSenderName("Lesli Kivit");
		mail.SetSenderMail(admin.mail.c_str());
		mail.SetReplyTo(admin.mail.c_str());
		mail.SetSubject("Job offer from Booking.com!");
		mail.AddRecipient(actualClient.mail.c_str());
		mail.SetXPriority(XPRIORITY_NORMAL);
		mail.SetXMailer("Lesli Kivit");
		mail.AddMsgLine("Congratulations!\nThis as an auto generated mail. Your CPU, Memory or Processes limit is not as expected. Please check it out.");
		mail.AddMsgLine("");
		str = "Current CPU : " + to_string(currentCleintStatus.cpu) + "%\t\tExpected CPU :" + to_string(actualClient.cpu) + "%";
		mail.AddMsgLine(str.c_str());
		str = "Current Memory : " + to_string(currentCleintStatus.mem) + "%\t\tExpected Memory :" + to_string(actualClient.mem) + "%";
		mail.AddMsgLine(str.c_str());
		str = "Number of Running Processes : " + to_string(currentCleintStatus.process) + "\t\tExpected Number of Running Processes :" + to_string(actualClient.process);
		mail.AddMsgLine(str.c_str());
		mail.AddMsgLine("");
		mail.AddMsgLine("Regards");
		mail.Send();
	}
	catch (ECSmtp e)
	{
		std::cout << "Error: " << e.GetErrorText().c_str() << ".\n";

		//printf("Error Code: %d\n", GetLastError());

		bError = true;
	}
	if (!bError)
		std::cout << "Mail was send successfully.\n";

}


void MailSender::notifyUser(Client actualClient, Client currentStatus)
{
    q.push({actualClient, currentStatus});
}

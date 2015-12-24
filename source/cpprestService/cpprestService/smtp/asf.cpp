//#include "CSmtp.h"
//#include <iostream>
//
//int main()
//{
//	bool bError = false;
//
//	try
//	{
//		CSmtp mail;
//
//		mail.SetSMTPServer("smtp.gmail.com",587);
//		mail.SetLogin("crossover.cpp.assignment@gmail.com");
//		mail.SetPassword("1q2s3c1234");
//  		mail.SetSenderName("Naseefadasdasfsadf");
//  		mail.SetSenderMail("crossover.cpp.assignment@gmail.com");
//  		mail.SetReplyTo("naseefcse@gmail.com");
//  		mail.SetSubject("The message");
//  		mail.AddRecipient("dipal.soul@gmail.com");
//  		mail.SetXPriority(XPRIORITY_NORMAL);
//  		mail.SetXMailer("The Bat! (v3.02) Professional");
//  		mail.AddMsgLine("Hello,");
//		mail.AddMsgLine("");
//		mail.AddMsgLine("...");
//		mail.AddMsgLine("How are you today?");
//		mail.AddMsgLine("");
//		mail.AddMsgLine("Regards");
//		mail.ModMsgLine(5,"regards");
//		mail.DelMsgLine(2);
//		mail.AddMsgLine("User");
//		
//  		//mail.AddAttachment("../test1.jpg");
//  		//mail.AddAttachment("c:\\test2.exe");
//		//mail.AddAttachment("c:\\test3.txt");
//		mail.Send();
//	}
//	catch(ECSmtp e)
//	{
//		std::cout << "Error: " << e.GetErrorText().c_str() << ".\n";
//		bError = true;
//	}
//	if(!bError)
//		std::cout << "Mail was send successfully.\n";
//
//	int t;
//
//	std::cin >> t;
//	return 0;
//}

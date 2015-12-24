
#include "monitor.h"
#include "config.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main()
{
	ifstream ifs("link_config.txt");

	std::string link = "";

	ifs >> link;

	wstring wsLink(link.begin(), link.end());

    Monitor *monitor = new Monitor(wsLink, "config.xml");
    monitor->open().wait();
    string line;
    getline(cin, line);

    monitor->close().wait();
    //Config config;
    //cout<<config.loadConfig("/home/dipal/qt/config.xml")<<endl;
    return 0;
}

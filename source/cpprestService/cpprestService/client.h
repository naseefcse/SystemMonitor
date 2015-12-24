#ifndef CLIENT_H
#define CLIENT_H

#include <string>

using namespace std;


struct Client
{
    string userName;
    string password;
    string mail;
    int cpu;
    int mem;
    int process;
};

struct Admin
{
    string name;
    string mail;
    string password;
};


#endif // CLIENT_H

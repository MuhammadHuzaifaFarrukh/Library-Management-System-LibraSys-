#pragma once
#include <string>

using namespace std;

// User Credentials
class User
{
protected:
    string username;
    string password;

    // Here they are just used to check the login (saved for the current Member) which can also be done through local variables
    // Though username and password are saved inside the Member once logged in and then they are not used until another Member logs in

public:
    virtual ~User(); // Added so that the other classes it extends will use virtual by default
    virtual bool login() = 0;
    string getUsername() const;
    string getPassword() const;
    void setUsername(const string &u);
    void setPassword(const string &p);
};
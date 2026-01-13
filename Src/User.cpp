#include <iostream>
#include <string>
#include "User.h"

using namespace std;

// Virtual destructor for safety with inheritance for sub-classes
User ::~User() {}

string User::getUsername() const
{
    return username;
}

string User::getPassword() const
{
    return password;
}

void User::setUsername(const string &u)
{
    username = u;
}
void User::setPassword(const string &p)
{
    password = p;
}
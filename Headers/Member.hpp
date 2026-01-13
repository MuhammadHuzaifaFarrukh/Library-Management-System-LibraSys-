#pragma once
#include "User.h"

using namespace std;

// Members
class Member : public User
{
public:
    bool login() override;
    void viewBooks(const Library &lib) const;
    void checkDues(const Library &lib) const;
    void memberMenu(const Library &lib);
};
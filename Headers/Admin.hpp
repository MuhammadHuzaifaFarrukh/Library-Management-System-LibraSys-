#pragma once
#include "User.h"
#include "Library.h"

using namespace std;

class Library; // Forward declaration
// Admin Class
class Admin : public User
{
private:
    Library &library;

public:
    Admin(Library &lib) : library(lib) {}

    bool login();
    void adminMenu();
};
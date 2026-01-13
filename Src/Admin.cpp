#include <iostream>
#include "Admin.h"

using namespace std;

bool Admin::login()
{
    // Actual login logic moved to Library::adminLogin()
    return true;
}

void Admin::adminMenu()
{
    library.adminMenu();
}
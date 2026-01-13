#include <iostream>
#include <iomanip>
#include "Member.h"
#include "Library.h"

using namespace std;

bool Member::login()
{
    // Actual login logic moved to Library::memberLogin()
    return true;
}

void Member::viewBooks(const Library &lib) const
{
    lib.showAllBooks();
}

void Member::checkDues(const Library &lib) const
{
    lib.showMemberDues(username);
}

void Member::memberMenu(const Library &lib)
{
    int choice;
    while (true)
    {
        cout << "\n=============================================" << endl;
        cout << "             MEMBER MENU" << endl;
        cout << "=============================================" << endl;
        cout << "1. View All Books" << endl;
        cout << "2. Check My Dues" << endl;
        cout << "3. Logout" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            viewBooks(lib);
            break;
        case 2:
            checkDues(lib);
            break;
        case 3:
            cout << "\n\tLogging out..." << endl;
            return;
        default:
            cout << "\n\tInvalid choice. Please try again." << endl;
        }
    }
}
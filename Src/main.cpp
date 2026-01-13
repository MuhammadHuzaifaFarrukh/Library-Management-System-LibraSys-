#include <iostream>
#include <string>

#include "Library.h"
#include "Admin.h"
#include "Member.h"
#include "Book.h"
#include "IssuedBook.h"
#include "Date.h"
#include "global.h"
#include "User.h"

using namespace std;

int main()
{
    Library lib;

    // First check if files exist at all
    if (lib.isFirstRun())
    {
        cout << "\nFirst run detected - setting up admin...\n";
        if (!lib.registerFirstAdmin())
        {
            cout << "\n\tAdmin registration failed. Exiting." << endl;
            return 1;
        }
        cout << "\nAdmin created. Please restart the program.\n";
        return 0;
    }

    // Loading all the data from files
    if (!lib.loadAllData())
    {
        cout << "\n\tFailed to load library data. Check file permissions or corruption." << endl;
        cout << "Files expected:\n";
        cout << "  - " << Library::ADMIN_FILE << endl;
        cout << "  - " << Library::MEMBERS_FILE << endl;
        cout << "  - " << Library::BOOKS_FILE << endl;
        cout << "  - " << Library::ISSUED_FILE << endl;
        return 1;
    }

    cout << "\nData loaded successfully.\n";

    while (true)
    {
        cout << "\n=============================================" << endl;
        cout << "       LIBRARY MANAGEMENT SYSTEM" << endl;
        cout << "=============================================" << endl;
        cout << "1. Admin Login" << endl;
        cout << "2. Member Login" << endl;
        cout << "3. Exit Program" << endl;
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;

        if (choice == 1)
        {
            if (lib.adminLogin())
            {
                lib.adminMenu();
            }
        }
        else if (choice == 2)
        {
            string loggedInUsername;
            if (lib.memberLogin(loggedInUsername))
            {
                lib.memberMenu(loggedInUsername);
            }
        }
        else if (choice == 3)
        {
            cout << "\n\tExiting program. Goodbye!" << endl;
            return 0;
        }
        else
        {
            cout << "\n\tInvalid choice. Please try again." << endl;
        }
    }

    return 0;
}
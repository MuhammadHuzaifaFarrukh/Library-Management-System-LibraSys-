#include "Library.h"

Library::Library() : theAdmin(*this) {}

const string Library::ADMIN_FILE = "admin_info.txt";
const string Library::MEMBERS_FILE = "members.txt";
const string Library::BOOKS_FILE = "books.txt";
const string Library::ISSUED_FILE = "issued_books.txt";

bool Library::loadAllData()
{
    bool success = true;

    // 1. Load Admin - This is REQUIRED for the program to function after setup
    ifstream adminFile(ADMIN_FILE);
    if (adminFile.is_open())
    {
        string line;
        if (getline(adminFile, line))
        {
            size_t pos = line.find(':');
            if (pos != string::npos)
            {
                string uname = line.substr(0, pos);
                string pass = line.substr(pos + 1);
                theAdmin.setUsername(uname);
                theAdmin.setPassword(pass);
            }
        }
        adminFile.close();
    }
    else
    {
        // If admin file is missing, we cannot log in, so this is a failure
        success = false;
    }

    // 2. Load Members - Optional (file may not exist yet)
    ifstream membersFile(MEMBERS_FILE);
    if (membersFile.is_open())
    {
        string line;
        while (getline(membersFile, line))
        {
            size_t pos = line.find(':');
            if (pos != string::npos)
            {
                Member m;
                string uname = line.substr(0, pos);
                string pass = line.substr(pos + 1);
                m.setUsername(uname);
                m.setPassword(pass);
                members.push_back(m);
            }
        }
        membersFile.close();
    }
    // No 'else success = false' here because it's okay if this file is missing

    // 3. Load Books - Optional
    ifstream booksFile(BOOKS_FILE);
    if (booksFile.is_open())
    {
        string line;
        while (getline(booksFile, line))
        {
            if (!line.empty())
                books.push_back(Book::fromFileLine(line));
        }
        booksFile.close();
    }

    // 4. Load Issued Books - Optional
    ifstream issuedFile(ISSUED_FILE);
    if (issuedFile.is_open())
    {
        string line;
        while (getline(issuedFile, line))
        {
            if (!line.empty())
                issuedBooks.push_back(IssuedBook::fromFileLine(line));
        }
        issuedFile.close();
    }

    return success;
}

bool Library::saveAllData() const
{
    bool success = true;

    // Save admin
    ofstream adminFile(ADMIN_FILE);
    if (adminFile.is_open())
    {
        adminFile << theAdmin.getUsername() << ":" << theAdmin.getPassword() << endl;
        adminFile.close();
    }
    else
        success = false;

    // Save members
    ofstream membersFile(MEMBERS_FILE);
    if (membersFile.is_open())
    {
        for (const auto &m : members)
        {
            membersFile << m.getUsername() << ":" << m.getPassword() << endl;
        }
        membersFile.close();
    }
    else
        success = false;

    // Save books
    ofstream booksFile(BOOKS_FILE);
    if (booksFile.is_open())
    {
        for (const auto &b : books)
        {
            booksFile << b.toFileLine() << endl;
        }
        booksFile.close();
    }
    else
        success = false;

    // Save issued books
    ofstream issuedFile(ISSUED_FILE);
    if (issuedFile.is_open())
    {
        for (const auto &ib : issuedBooks)
        {
            issuedFile << ib.toFileLine() << endl;
        }
        issuedFile.close();
    }
    else
        success = false;

    return success;
}

// ─────────────────────────────────────────────
// First run & admin
// ─────────────────────────────────────────────

bool Library::isFirstRun() const
{
    ifstream file(ADMIN_FILE);
    bool exists = file.good();
    file.close();
    return !exists;
}

bool Library::registerFirstAdmin()
{
    string username, password;

    cout << "\n=== First-time Admin Setup ===\n";
    cout << "Enter new admin username: ";
    cin >> username;

    cout << "Enter admin password: ";
    cin >> password;

    // Very important: check if file can actually be created/opened
    ofstream adminFile(ADMIN_FILE);
    if (!adminFile.is_open())
    {
        cout << "\nERROR: Cannot create or write to file '" << ADMIN_FILE << "'\n";
        cout << "   → Check folder permissions or move project to Documents/Desktop\n";
        return false;
    }

    // Write in the exact format your loadAllData() expects
    adminFile << username << ":" << password << endl;
    adminFile.close();

    cout << "\nAdmin account created successfully!\n";
    cout << "Please restart the program to login.\n";

    return true;
}

bool Library::adminLogin()
{
    string uname, pword;
    cout << "\n\tEnter username: ";
    cin >> uname;
    cout << "\tEnter password: ";
    cin >> pword;

    if (uname == theAdmin.getUsername() && pword == theAdmin.getPassword())
    {
        cout << "\n\tLogin successful!" << endl;
        return true;
    }
    cout << "\n\tInvalid username or password." << endl;
    return false;
}

// ─────────────────────────────────────────────
// Member login & menu
// ─────────────────────────────────────────────

bool Library::memberLogin(string &loggedUsername)
{
    string uname, pword;
    cout << "\n\tEnter username: ";
    cin >> uname;
    cout << "\tEnter password: ";
    cin >> pword;

    for (const auto &m : members)
    {
        if (m.getUsername() == uname && m.getPassword() == pword)
        {
            loggedUsername = uname;
            cout << "\n\tLogin successful!" << endl;
            return true;
        }
    }
    cout << "\n\tInvalid username or password." << endl;
    return false;
}

// ─────────────────────────────────────────────
// Admin menu & operations
// ─────────────────────────────────────────────

void Library::adminMenu()
{
    int choice;
    while (true)
    {
        cout << "\n=============================================" << endl;
        cout << "           ADMIN MENU" << endl;
        cout << "=============================================" << endl;
        cout << "1. Add Member" << endl;
        cout << "2. Remove Member" << endl;
        cout << "3. Add Book" << endl;
        cout << "4. Remove Book" << endl;
        cout << "5. Issue Book" << endl;
        cout << "6. Collect Book" << endl;
        cout << "7. Check Due Dates" << endl;
        cout << "8. List All Members" << endl;
        cout << "9. Search (Books/Members)" << endl;
        cout << "10. Logout" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            addMember();
            break;
        case 2:
            removeMember();
            break;
        case 3:
            addBook();
            break;
        case 4:
            removeBook();
            break;
        case 5:
            issueBook();
            break;
        case 6:
            collectBook();
            break;
        case 7:
            checkDueDates();
            break;
        case 8:
            listMembers();
            break;
        case 9:
            search();
            break;
        case 10:
            cout << "\n\tLogging out..." << endl;
            return;
        default:
            cout << "\n\tInvalid choice. Please try again." << endl;
        }
    }
}

bool Library::addMember()
{
    string uname, pword, confirmPword;

    cout << "\n---------------------------------" << endl;
    cout << "         Adding a New Member" << endl;
    cout << "---------------------------------" << endl;

    // --- 1. Loop for UNIQUE Username ---
    while (true)
    {
        cout << "Enter new member username: ";
        cin >> uname;

        if (isMemberUsernameTaken(uname))
        {
            cout << "\n\t[!] Username already exists. Please try another.\n"
                 << endl;
        }
        else
        {
            break; // Username is unique, exit loop
        }
    }

    // --- 2. Loop for UNIQUE Password ---
    while (true)
    {
        cout << "Enter new member password: ";
        cin >> pword;

        if (isMemberPasswordTaken(pword))
        {
            cout << "\n\t[!] Password already taken by another user. Choose a unique one.\n"
                 << endl;
            continue;
        }

        cout << "Re-enter password to confirm: ";
        cin >> confirmPword;

        if (pword == confirmPword)
        {
            break; // Password is unique AND matches, exit loop
        }
        else
        {
            cout << "\n\t[!] Passwords do not match. Try setting the password again.\n"
                 << endl;
        }
    }

    Member newMember;
    newMember.setUsername(uname);
    newMember.setPassword(pword);
    
    members.push_back(newMember);

    if (saveAllData())
    {
        cout << "\n\tMember '" << uname << "' added successfully!" << endl;
        return true;
    }
    else
    {
        cout << "\n\tError saving members." << endl;
        return false;
    }
}

bool Library::removeMember()
{
    string uname;
    cout << "\n---------------------------------" << endl;
    cout << "         Removing a Member" << endl;
    cout << "---------------------------------" << endl;
    cout << "Enter username of member to remove: ";
    cin >> uname;

    auto it = find_if(members.begin(), members.end(),
                      [&](const Member &m)
                      { return m.getUsername() == uname; });

    if (it == members.end())
    {
        cout << "\n\tMember not found." << endl;
        return false;
    }

    members.erase(it);

    if (saveAllData())
    {
        cout << "\n\tMember '" << uname << "' removed successfully!" << endl;
        return true;
    }
    else
    {
        cout << "\n\tError saving members." << endl;
        return false;
    }
}

bool Library::addBook()
{
    string isbn, title, author, seller;
    int quantity;

    cout << "\n---------------------------------" << endl;
    cout << "         Adding a New Book" << endl;
    cout << "---------------------------------" << endl;
    cout << "Enter book ISBN: ";
    cin.ignore();
    getline(cin, isbn);
    cout << "Enter book title: ";
    getline(cin, title);
    cout << "Enter author: ";
    getline(cin, author);
    cout << "Enter seller: ";
    getline(cin, seller);
    cout << "Enter quantity: ";
    cin >> quantity;

    Book newBook(isbn, title, author, seller, quantity);
    books.push_back(newBook);

    if (saveAllData())
    {
        cout << "\n\tBook '" << title << "' added successfully!" << endl;
        return true;
    }
    else
    {
        cout << "\n\tError saving books." << endl;
        return false;
    }
}

bool Library::removeBook()
{
    string isbn;
    cout << "\n---------------------------------" << endl;
    cout << "         Removing a Book" << endl;
    cout << "---------------------------------" << endl;
    cout << "Enter ISBN of book to remove: ";
    cin.ignore();
    getline(cin, isbn);

    auto it = find_if(books.begin(), books.end(),
                      [&](const Book &b)
                      { return b.getISBN() == isbn; });

    if (it == books.end())
    {
        cout << "\n\tBook not found." << endl;
        return false;
    }

    books.erase(it);

    if (saveAllData())
    {
        cout << "\n\tBook removed successfully!" << endl;
        return true;
    }
    else
    {
        cout << "\n\tError saving books." << endl;
        return false;
    }
}

bool Library::issueBook()
{
    string memberU, bookISBN;
    cout << "\n---------------------------------" << endl;
    cout << "         Issuing a Book" << endl;
    cout << "---------------------------------" << endl;
    cout << "Enter member username: ";
    cin >> memberU;
    cout << "Enter book ISBN: ";
    cin.ignore();
    getline(cin, bookISBN);

    Member *member = findMember(memberU);
    if (!member)
    {
        cout << "\n\tMember not found." << endl;
        return false;
    }

    Book *book = findBook(bookISBN);
    if (!book || book->getAvailable() <= 0)
    {
        cout << "\n\tBook not found or not available." << endl;
        return false;
    }

    book->decreaseAvailable();

    Date current = Date::getCurrentDate();
    Date due = Date::calculateDueDate();

    IssuedBook ib(memberU, bookISBN, book->getTitle(), current, due);
    issuedBooks.push_back(ib);

    if (saveAllData())
    {
        cout << "\n\tBook issued successfully to '" << memberU << "'!" << endl;
        return true;
    }
    else
    {
        cout << "\n\tError saving issued books." << endl;
        return false;
    }
}

bool Library::collectBook()
{
    string memberU, bookISBN;
    cout << "\n---------------------------------" << endl;
    cout << "         Collecting a Book" << endl;
    cout << "---------------------------------" << endl;
    cout << "Enter member username: ";
    cin >> memberU;
    cout << "Enter book ISBN: ";
    cin.ignore();
    getline(cin, bookISBN);

    auto it = find_if(issuedBooks.begin(), issuedBooks.end(),
                      [&](const IssuedBook &ib)
                      {
                          return ib.getMember() == memberU && ib.getISBN() == bookISBN;
                      });

    if (it == issuedBooks.end())
    {
        cout << "\n\tNo such issued book found." << endl;
        return false;
    }

    issuedBooks.erase(it);

    Book *book = findBook(bookISBN);
    if (book)
        book->increaseAvailable();

    if (saveAllData())
    {
        cout << "\n\tBook collected successfully from '" << memberU << "'!" << endl;
        return true;
    }
    else
    {
        cout << "\n\tError saving data." << endl;
        return false;
    }
}

void Library::checkDueDates()
{
    cout << "\n---------------------------------" << endl;
    cout << "         Checking Due Dates" << endl;
    cout << "---------------------------------" << endl;
    cout << left << setw(20) << "Member" << setw(40) << "Book Title"
         << setw(15) << "Status" << setw(10) << "Fine" << endl;
    cout << string(85, '-') << endl;

    Date today = Date::getCurrentDate();

    for (const auto &ib : issuedBooks)
    {
        int days = today.getDaysUntil(ib.getDueDate());
        string status = (days >= 0) ? to_string(days) + " days left" : "Overdue";
        double fine = (days < 0) ? (-days * 50.0) : 0.0;

        cout << left << setw(20) << ib.getMember()
             << setw(40) << ib.getTitle()
             << setw(15) << status
             << setw(10) << fine << endl;
    }
}

void Library::listMembers()
{
    cout << "\n---------------------------------" << endl;
    cout << "         Registered Members" << endl;
    cout << "---------------------------------" << endl;

    for (const auto &m : members)
    {
        cout << "Username: " << m.getUsername() << endl;
    }
}

void Library::search()
{
    int ch;
    cout << "\nSearch for (1) Books or (2) Members? ";
    cin >> ch;

    if (ch == 1)
    {
        string query;
        cout << "Enter book title or author to search: ";
        cin.ignore();
        getline(cin, query);

        bool found = false;
        for (const auto &b : books)
        {
            if (b.getTitle().find(query) != string::npos || b.getAuthor().find(query) != string::npos)
            {
                cout << "\n\t-------------------------" << endl;
                cout << "\tTitle: " << b.getTitle() << endl;
                cout << "\tAuthor: " << b.getAuthor() << endl;
                cout << "\tSeller: " << b.getSeller() << endl;
                cout << "\tTotal Quantity: " << b.getTotalQty() << endl;
                cout << "\tAvailable: " << b.getAvailable() << endl;
                cout << "\t-------------------------" << endl;
                found = true;
            }
        }
        if (!found)
        {
            cout << "\n\tNo matching books found." << endl;
        }
    }
    else if (ch == 2)
    {
        string query;
        cout << "Enter member username to search: ";
        cin >> query;

        bool found = false;
        for (const auto &m : members)
        {
            if (m.getUsername().find(query) != string::npos)
            {
                cout << "\n\tMember found: " << m.getUsername() << endl;
                found = true;
            }
        }
        if (!found)
        {
            cout << "\n\tNo matching members found." << endl;
        }
    }
    else
    {
        cout << "\n\tInvalid choice." << endl;
    }
}

void Library::showAllBooks() const
{
    cout << "\n---------------------------------" << endl;
    cout << "         Available Books" << endl;
    cout << "---------------------------------" << endl;
    cout << left << setw(40) << "Title" << setw(30) << "Author" << setw(15) << "Seller" << setw(10) << "Quantity" << endl;
    cout << string(95, '-') << endl;

    for (const auto &b : books)
    {
        if (b.getAvailable() > 0)
        {
            cout << left << setw(40) << b.getTitle()
                 << setw(30) << b.getAuthor()
                 << setw(15) << b.getSeller()
                 << setw(10) << b.getAvailable() << endl;
        }
    }
}

void Library::showMemberDues(const string &username) const
{
    cout << "\n---------------------------------" << endl;
    cout << "            My Dues" << endl;
    cout << "---------------------------------" << endl;
    cout << left << setw(40) << "Book Title" << setw(15) << "Days Left" << setw(15) << "Fine" << endl;
    cout << string(70, '-') << endl;

    Date today = Date::getCurrentDate();
    bool hasAny = false;

    for (const auto &ib : issuedBooks)
    {
        if (ib.getMember() == username)
        {
            hasAny = true;
            int daysRemaining = today.getDaysUntil(ib.getDueDate());
            string daysStr = (daysRemaining >= 0) ? to_string(daysRemaining) : "Overdue";
            string fineStatus = (daysRemaining < 0) ? to_string(-daysRemaining * 50.0) : "N/A";

            cout << left << setw(40) << ib.getTitle()
                 << setw(15) << daysStr
                 << setw(15) << fineStatus << endl;
        }
    }

    if (!hasAny)
    {
        cout << "\n\tNo books have been issued to you." << endl;
    }
}

// ─────────────────────────────────────────────
// Private helpers
// ─────────────────────────────────────────────

bool Library::isMemberUsernameTaken(const string &uname) const
{
    for (const auto &m : members)
    {
        if (m.getUsername() == uname)
            return true;
    }
    return false;
}

bool Library::isMemberPasswordTaken(const string &pword) const
{
    for (const auto &m : members)
    {
        if (m.getPassword() == pword)
            return true;
    }
    return false;
}

Member *Library::findMember(const string &uname)
{
    for (auto &m : members)
    {
        if (m.getUsername() == uname)
            return &m;
    }
    return nullptr;
}

const Member *Library::findMember(const string &uname) const
{
    for (const auto &m : members)
    {
        if (m.getUsername() == uname)
            return &m;
    }
    return nullptr;
}

Book *Library::findBook(const string &isbn)
{
    for (auto &b : books)
    {
        if (b.getISBN() == isbn)
            return &b;
    }
    return nullptr;
}

const Book *Library::findBook(const string &isbn) const
{
    for (const auto &b : books)
    {
        if (b.getISBN() == isbn)
            return &b;
    }
    return nullptr;
}

void Library::memberMenu(const string &loggedUsername)
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
            showAllBooks();
            break;
        case 2:
            showMemberDues(loggedUsername);
            break;
        case 3:
            cout << "\n\tLogging out..." << endl;
            return;
        default:
            cout << "\n\tInvalid choice. Please try again." << endl;
        }
    }
}
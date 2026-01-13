#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <algorithm>

#include "Admin.h"
#include "Member.h"
#include "Book.h"
#include "IssuedBook.h"
#include "Date.h"

using namespace std;

class Library
{
private:
    Admin theAdmin;
    vector<Member> members;
    vector<Book> books;
    vector<IssuedBook> issuedBooks;

public:
    static const string ADMIN_FILE ;
    static const string MEMBERS_FILE ;
    static const string BOOKS_FILE ;
    static const string ISSUED_FILE ;
    
    Library();

    // Persistence
    bool loadAllData();
    bool saveAllData() const;

    // First run & admin
    bool isFirstRun() const;
    bool registerFirstAdmin();
    bool adminLogin();
    void adminMenu();

    // Member login & menu
    bool memberLogin(string &loggedUsername);
    void memberMenu(const string &loggedUsername);

    // Core business logic Functions
    bool addMember();
    bool removeMember();
    bool addBook();
    bool removeBook();
    bool issueBook();
    bool collectBook();
    void checkDueDates();
    void listMembers();
    void search();

    // Member-facing views
    void showAllBooks() const;
    void showMemberDues(const string &username) const;

private:
    // Helpers
    bool isMemberUsernameTaken(const string &uname) const;
    bool isMemberPasswordTaken(const string &pword) const;
    Member *findMember(const string &uname);
    const Member *findMember(const string &uname) const;
    Book *findBook(const string &isbn);
    const Book *findBook(const string &isbn) const;
};

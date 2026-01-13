#pragma once
#include <string>
#include <sstream>
#include "Date.h"

using namespace std;

class IssuedBook
{
private:
    string memberUsername;  //Like a foreign key to Member
    string bookISBN;        //Like a foreign key to Book
    string bookTitle;
    Date issueDate;
    Date dueDate;

public:
    IssuedBook();
    IssuedBook(string user, string isbn, string title, Date issue, Date due);

    const string &getMember() const;
    const string &getISBN() const;
    const string &getTitle() const;
    const Date &getIssueDate() const;
    const Date &getDueDate() const;

    string toFileLine() const;
    static IssuedBook fromFileLine(const string &line);
};
#include "IssuedBook.h"

using namespace std;

IssuedBook::IssuedBook() {}

IssuedBook::IssuedBook(string user, string isbn, string title, Date issue, Date due)
    : memberUsername(user), bookISBN(isbn), bookTitle(title),
      issueDate(issue), dueDate(due) {}

const string &IssuedBook::getMember() const { return memberUsername; }
const string &IssuedBook::getISBN() const { return bookISBN; }
const string &IssuedBook::getTitle() const { return bookTitle; }
const Date &IssuedBook::getIssueDate() const { return issueDate; }
const Date &IssuedBook::getDueDate() const { return dueDate; }

string IssuedBook::toFileLine() const
{
    return memberUsername + "|" + bookISBN + "|" + bookTitle + "|" + issueDate.toString() + "|" + dueDate.toString();
}

IssuedBook IssuedBook::fromFileLine(const string &line)
{
    stringstream ss(line);
    string user, isbn, title, issueStr, dueStr;
    getline(ss, user, '|');
    getline(ss, isbn, '|');
    getline(ss, title, '|');
    getline(ss, issueStr, '|');
    getline(ss, dueStr);

    return IssuedBook(user, isbn, title,
                      Date::fromString(issueStr),
                      Date::fromString(dueStr));
}
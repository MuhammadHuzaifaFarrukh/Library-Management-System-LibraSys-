#pragma once
#include <string>
#include <sstream>

using namespace std;

class Book
{
private:
    string isbn;
    string title;
    string author;
    string seller;
    int totalQty;
    int availQty;

public:
    Book();
    Book(string i, string t, string a, string s, int q);

    const string &getISBN() const;
    const string &getTitle() const;
    const string &getAuthor() const;
    const string &getSeller() const;
    int getTotalQty() const;
    int getAvailable() const;

    void setISBN(const string &i);
    void setTitle(const string &t);
    void setAuthor(const string &a);
    void setSeller(const string &s);
    void setTotalQty(int q);
    void setAvailable(int q);

    void decreaseAvailable();
    void increaseAvailable();

    string toFileLine() const;
    static Book fromFileLine(const string &line);
};
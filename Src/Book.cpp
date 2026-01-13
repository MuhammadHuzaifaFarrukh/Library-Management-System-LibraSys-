#include "Book.h"
#include <sstream>
#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

Book::Book() : totalQty(0), availQty(0) {}

Book::Book(string i, string t, string a, string s, int q)
    : isbn(i), title(t), author(a), seller(s), totalQty(q), availQty(q) {}

const string &Book::getISBN() const { return isbn; }
const string &Book::getTitle() const { return title; }
const string &Book::getAuthor() const { return author; }
const string &Book::getSeller() const { return seller; }
int Book::getTotalQty() const { return totalQty; }
int Book::getAvailable() const { return availQty; }

void Book::setISBN(const string &i) { isbn = i; }
void Book::setTitle(const string &t) { title = t; }
void Book::setAuthor(const string &a) { author = a; }
void Book::setSeller(const string &s) { seller = s; }
void Book::setTotalQty(int q) { totalQty = q; }
void Book::setAvailable(int q) { availQty = q; }

void Book::decreaseAvailable()
{
    if (availQty > 0)
        availQty--;
}
void Book::increaseAvailable() { availQty++; }

string Book::toFileLine() const
{
    stringstream ss;
    ss << isbn << "|" << title << "|" << author << "|"
       << seller << "|" << totalQty << "|" << availQty;
    return ss.str();
}

Book Book::fromFileLine(const string &line)
{
    stringstream ss(line);
    string i, t, a, s, totStr, availStr;
    getline(ss, i, '|');
    getline(ss, t, '|');
    getline(ss, a, '|');
    getline(ss, s, '|');
    getline(ss, totStr, '|');
    getline(ss, availStr);

    int total = stoi(totStr);
    int avail = stoi(availStr);

    Book b(i, t, a, s, total);
    b.setAvailable(avail);
    return b;
}
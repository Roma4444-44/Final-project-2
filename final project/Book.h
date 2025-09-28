#ifndef BOOK_H
#define BOOK_H
#include <iostream>
#include <string>
#include <algorithm>
#include <Container.h>
using namespace std;
template <typename T>
class Book {
public:
    string title, author, ISBN, genre;
    bool available;

    Book(string t="", string a="", string i="", string g="", bool av=true)
        : title(t), author(a), ISBN(i), genre(g), available(av) {}

    bool operator==(const Book& other) const {
        return ISBN == other.ISBN; // ISBN as unique ID
    }

    bool operator>(const Book& other) const {
        return title > other.title; // Sort by title default
    }

    friend ostream& operator<<(ostream& os, const Book& b) {
        os << "[" << b.title << " by " << b.author
           << " | ISBN: " << b.ISBN
           << " | Genre: " << b.genre
           << " | " << (b.available ? "Available" : "Borrowed") << "]";
        return os;
    }
};
class Library {
private:
    Container<Book> catalog;

public:
    void addBook(const Book& book) { catalog.insertBack(book); }

    void removeBookByISBN(const string& isbn) {
        Container<Book>::Iterator it = catalog.begin();
        int pos = 0;
        while (it != catalog.end()) {
            if ((*it).ISBN == isbn) {
                catalog.removeAt(pos);
                cout << "Book removed.\n";
                return;
            }
            it.next();
            pos++;
        }
        cout << "Book not found.\n";
    }

    void searchBook(const string& keyword) {
        Container<Book>::Iterator it = catalog.begin();
        while (it != catalog.end()) {
            if ((*it).title == keyword || (*it).author == keyword ||
                (*it).ISBN == keyword || (*it).genre == keyword) {
                cout << *it << endl;
            }
            it.next();
        }
    }

    void borrowBook(const string& isbn) {
        Container<Book>::Iterator it = catalog.begin();
        while (it != catalog.end()) {
            if ((*it).ISBN == isbn && (*it).available) {
                (*it).available = false;
                cout << "Book borrowed successfully.\n";
                return;
            }
            it.next();
        }
        cout << "Book not available.\n";
    }

    void displayBooks() { catalog.display(); }

    void sortBooks() {
        catalog.sortContainer();
        cout << "Books sorted by title.\n";
    }

    void statistics() {
        int total = 0, available = 0, borrowed = 0;
        Container<Book>::Iterator it = catalog.begin();
        while (it != catalog.end()) {
            total++;
            if ((*it).available) available++;
            else borrowed++;
            it.next();
        }
        cout << "Total: " << total
             << " | Available: " << available
             << " | Borrowed: " << borrowed << endl;
    }
};
#endif

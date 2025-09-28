#include <iostream>
#include <string>
#include <algorithm>
#include <Container.h>
#include <Book.h>
using namespace std;
template <typename T>
int main() {
    Library lib;

    lib.addBook(Book("C++ Basics", "Bjarne", "111", "Programming", true));
    lib.addBook(Book("Data Structures", "Mark", "222", "CS", true));
    lib.addBook(Book("Algorithms", "Thomas", "333", "CS", true));

    cout << "=== Library Catalog ===\n";
    lib.displayBooks();

    cout << "\n=== Borrow Book ===\n";
    lib.borrowBook("111");

    cout << "\n=== Search for Book ===\n";
    lib.searchBook("Mark");

    cout << "\n=== Statistics ===\n";
    lib.statistics();

    cout << "\n=== Sort Books ===\n";
    lib.sortBooks();
    lib.displayBooks();

    return 0;
}

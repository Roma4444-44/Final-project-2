#ifndef CONTAINER_H
#define CONTAINER_H
#include <iostream>
#include <string>
#include <algorithm>
#include <Book.h>
using namespace std;
template <typename T>
class Container {
private:
    struct Node {
        T data;
        Node* next;
        Node* prev;
        Node(T val) : data(val), next(nullptr), prev(nullptr) {}
    };
    Node* head;
    Node* tail;
    int size;

public:
    class Iterator {
        Node* current;
    public:
        Iterator(Node* node) : current(node) {}
        T& operator*() { return current->data; }
        Iterator& next() { if (current) current = current->next; return *this; }
        Iterator& prev() { if (current) current = current->prev; return *this; }
        bool operator!=(const Iterator& other) const { return current != other.current; }
    };

    Container() : head(nullptr), tail(nullptr), size(0) {}

    Iterator begin() { return Iterator(head); }
    Iterator end() { return Iterator(nullptr); }

    int getSize() const { return size; }
    void insertFront(const T& value) {
        Node* newNode = new Node(value);
        if (!head) head = tail = newNode;
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
        size++;
    }
    void insertBack(const T& value) {
        Node* newNode = new Node(value);
        if (!tail) head = tail = newNode;
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        size++;
    }
    void insertAt(const T& value, int pos) {
        if (pos < 0 || pos > size) {
            cout << "Invalid position\n";
            return;
        }
        if (pos == 0) { insertFront(value); return; }
        if (pos == size) { insertBack(value); return; }

        Node* newNode = new Node(value);
        Node* temp = head;
        for (int i = 0; i < pos - 1; i++) temp = temp->next;

        newNode->next = temp->next;
        newNode->prev = temp;
        temp->next->prev = newNode;
        temp->next = newNode;
        size++;
    }
    void removeAt(int pos) {
        if (pos < 0 || pos >= size) { cout << "Invalid position\n"; return; }
        Node* temp = head;
        if (pos == 0) {
            head = head->next;
            if (head) head->prev = nullptr;
            else tail = nullptr;
        } else if (pos == size - 1) {
            temp = tail;
            tail = tail->prev;
            if (tail) tail->next = nullptr;
            else head = nullptr;
        } else {
            for (int i = 0; i < pos; i++) temp = temp->next;
            temp->prev->next = temp->next;
            temp->next->prev = temp->prev;
        }
        delete temp;
        size--;
    }
    void removeValue(const T& value) {
        Node* temp = head;
        int pos = 0;
        while (temp) {
            if (temp->data == value) { removeAt(pos); return; }
            temp = temp->next;
            pos++;
        }
        cout << "Value not found\n";
    }
    int search(const T& value) {
        Node* temp = head;
        int pos = 0;
        while (temp) {
            if (temp->data == value) return pos;
            temp = temp->next;
            pos++;
        }
        return -1;
    }
    void display() {
        Node* temp = head;
        while (temp) {
            cout << temp->data << " <-> ";
            temp = temp->next;
        }
        cout << "NULL\n";
    }
    void sortContainer() {
        if (!head) return;
        for (Node* i = head; i != nullptr; i = i->next) {
            for (Node* j = i->next; j != nullptr; j = j->next) {
                if (i->data > j->data) {
                    swap(i->data, j->data);
                }
            }
        }
    }
};
#endif

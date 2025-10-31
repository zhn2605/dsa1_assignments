#ifndef SIMPLE_LIST_HPP
#define SIMPLE_LIST_HPP

#include <string>

// creating a generic template
template <typename T>
class SimpleList {
public:
    SimpleList(std::string& listName) : name(listName), head(nullptr), tail(nullptr) {}

    // list methods
    virtual void push(T& value) = 0;
    virtual T pop() = 0;

    // Getter
    std::string getName() { return name; }

protected:
    // generic insert start and end functions
    void insertStart(const T& value) {
        Node* newNode = new Node(value);
        newNode->next = head;
        head = newNode;
        if (!tail)
            tail = head;
    }

    void insertEnd(const T& value) {
        Node* newNode = new Node(value);
        if (tail)
            tail->next = newNode;
        else
            head = newNode;
        tail = newNode;
    }

    T removeStart() {
        if (!head)
            std::cout << "ERROR: This list is empty!";
        Node* temp = head;
        T val = head->data;
        head = head->next;
        if (!head)
            tail = nullptr;
        delete temp;
        return val;
    }

private:
    // Required nested Node class
    class Node {
    public:
        T data;
        Node* next;
        // in line constructor
        Node(const T& value) : data(value), next(nullptr) {}
    };

    std::string name;
    Node* head;
    Node* tail;

};

#endif
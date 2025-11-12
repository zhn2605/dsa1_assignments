#ifndef STACK_HPP
#define STACK_HPP

#include "simpleList.hpp"

// Again, reduce unecessary class definitions with generic type
template <typename T>
class Stack : public SimpleList<T> {
public:
    explicit Stack(const std::string& name) : SimpleList<T>(name) {}

    // overide base class funcitons
    // stack is LIFO
    void push(const T& value) override {
        this->insertStart(value);
    }

    T pop() override {
        return this->removeStart();
    }
};

#endif
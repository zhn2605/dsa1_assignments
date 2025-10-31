#ifndef QUEUE_HPP
#define QUEUE_HPP

// Again, reduce unecessary class definitions with generic type
template <typename T>
class Stack : public SimpleList<T> {
public:
    explicit Stack(std::string& name) : SimpleList<T>(name) {}

    // overide base class funcitons
    // queue is FIFO
    void push(const T& value) override {
        this->insertEnd(value);
    }

    T pop() override {
        return this->removeStart();
    }
};

#endif
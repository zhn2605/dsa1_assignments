#include "foobar.hpp"

Foobar::Foobar(const std::string &name) {
    foobarName = name;

    // Again, position is assigned 0 for now and assigned later
    position = 0;
}

// Setters
void Foobar::setPosition(int pos) {
    position = pos;
}

// Getters
int Foobar::getPosition() const {
    return position;
}

std::string Foobar::getName() const {
    return foobarName;
}

// virtual function, redefined in derived classes
int Foobar::getStrength() const {
    return position;
}
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
int Foobar::getPosition() {
    return position;
}

std::string Foobar::getName() {
    return foobarName;
}

// virtual function, redefined in derived classes
int Foobar::getStrength() {
    // Add 1, position '0' will have strength of 1 as it is the 
    // first in line.
    return position + 1;
}
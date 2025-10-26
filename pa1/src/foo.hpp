#ifndef FOO_H
#define FOO_H

#include "foobar.hpp"

class Foo : public Foobar {
public:
    // Derived from base constructor
    using Foobar::Foobar;
    int getStrength() const override { return getPosition() * 3; } // inline def because i dont wanna make another file for this
};

#endif
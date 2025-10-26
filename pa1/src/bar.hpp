#ifndef BAR_H
#define BAR_H

#include "foobar.hpp"

class Bar : public Foobar {
public:
    // Derived from base constructor
    using Foobar::Foobar;
    int getStrength() const override { return getPosition() + 1 + 15; }
};

#endif
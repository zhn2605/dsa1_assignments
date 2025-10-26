#ifndef FOOBAR_H
#define FOOBAR_H

#include <string>

class Foobar {
public:
    // Constructor. takes name as an input and position is assumed 0
    Foobar(const std::string& name);

    // Setters
    void setPosition(int pos);

    // Getters
    std::string getName();
    int getStrength();

private:
    // Get position
    int getPosition();

    // Private variables with function calls to get them
    std::string foobarName;
    int position;
};

#endif
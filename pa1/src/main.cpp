#include <iostream>
#include <fstream>
#include <string>

#include "foobar.hpp"

// Read from file and gather 
bool read_input_file(std::string fileName) {
    // Create an ifstream object and open the file
    std::ifstream inputFile(fileName);

    // Check if the file was opened successfully
    if (!inputFile.is_open()) {
        std::cerr << "Error: Could not open the file." << std::endl;
        return 1; // Indicate an error
    }

    std::string line;
    // Read the file line by line until the end
    while (std::getline(inputFile, line)) {
        std::cout << line << std::endl; // Print each line to the console
    }

    // Close the file
    inputFile.close(); 

    return 0; // Indicate successful execution
}

int main() {    
    // Get input file name
    std::string fileName;
    
    std::cout <<  "Enter the name of the input file: ";
    std::cin >> fileName;

    // Testing purposes
    read_input_file(fileName);
    
    return 0;
}
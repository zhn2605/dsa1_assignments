#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <memory>
#include <vector>

#include "foobar.hpp"
#include "foo.hpp"
#include "bar.hpp"

using namespace std;

// Processes foobar and correctly updates position
void process_foobar(vector<unique_ptr<Foobar>>& list ) {
    size_t n = list.size();
    for (size_t i = 0; i < n; ++i) {
        list[i]->setPosition(n-i);
    }
}


// Read from file and gather 
// Returning smart pointers to avoid memory leakage
vector<unique_ptr<Foobar>> load_foobars_from_file(string fileName) {
    vector<unique_ptr<Foobar>> list;

    // Create an ifstream object and open the file
    ifstream inputFile(fileName);

    // Check if the file was opened successfully
    if (!inputFile.is_open()) {
        cerr << "Error: Could not open the file.\n";
        return list; // Return empty list
    }

    string line, foobar_type, name;
    // Read the file line by line until the end
    while (getline(inputFile, line)) {
        // Get string stream from line
        stringstream ss(line);

        // Pass in type and name to its respective variables
        ss >> foobar_type >>  name;
        
        // Construct and insert correct foobar depending on type
        if (foobar_type == "foo") list.push_back(make_unique<Foo>(name));
        else if (foobar_type == "bar") list.push_back(make_unique<Bar>(name));
        else if (foobar_type == "foobar") list.push_back(make_unique<Foobar>(name));
        else cout << name << " is not a valid Foobar!\n";

        cout << line << "\n"; // Print each line to the console
    }

    // Close the file
    inputFile.close(); 

    // Reverse the oder of foobars to correctly set its order
    process_foobar(list);

    return list;
}

bool display_list_into_file(string fileName, vector<unique_ptr<Foobar>>& list) {
    // Create an ofstream object and open the file
    ofstream outputFile(fileName);

    // Check if the file was opened successfully
    if (!outputFile.is_open()) {
        cerr << "Error: Could not open the file.\n";
        return 1; // Return empty list
    }

    for (const auto& foobar : list) {
        // testing
        cout << foobar->getName() << " " <<foobar->getStrength() << "\n";

        outputFile << foobar->getName() << " " << foobar->getStrength() << "\n";
    }

    // Close the file
    outputFile.close();

    return 0;
}

int main() {    
    // Get input file name
    string inputFileName;
    string outputFileName;
    
    cout <<  "Enter the name of the input file: ";
    cin >> inputFileName;
    cout <<  "Enter the name of the output file: ";
    cin >> outputFileName;


    // Load foobar into list with correct positiong
    vector<unique_ptr<Foobar>> list = load_foobars_from_file(inputFileName);
    
    return display_list_into_file(outputFileName, list);
}
#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>
#include <list>

#include "simpleList.hpp"
#include "queue.hpp"
#include "stack.hpp"

using namespace std;

// search function
template <typename T>
SimpleList<T>* searchForList(string listName, list<unique_ptr<SimpleList<T>>> &totalList){
    // linear search for now
    for (auto& simpleList : totalList) {
        if (simpleList->getName() == listName) {
            return simpleList.get();
        }
    }

    return nullptr;
}

// create list function
template <typename T>
unique_ptr<SimpleList<T>> createSimpleList(const string& name, const string& sl_type) {
    if (sl_type == "stack")
        return make_unique<Stack<T>>(name);
    else if (sl_type == "queue")
        return make_unique<Queue<T>>(name);
    else
        throw invalid_argument("Invalid list type: " + sl_type);
}

// mian process function
bool processComands(const string& inputFileName, const string& outputFileName, 
    list<unique_ptr<SimpleList<int>>> &listSLi, list<unique_ptr<SimpleList<double>>> &listSLd, list<unique_ptr<SimpleList<string>>> &listSLs) {

    // open the input and output files
    ifstream inputFile(inputFileName);
    ofstream outputFile(outputFileName);

    // open input file
    if(!inputFile) {
        cerr << "Cannot open file!";
        return 1;
    }

    string line, command, name;
    // Read the file line by line until the end
    while (getline(inputFile, line)) {
        // Get string stream from line
        stringstream ss(line);

        // Pass in type and name to its respective variables
        ss >> command >> name;
        char list_type = name[0];
        
        // Prase command
        outputFile  << "PROCESSING COMMAND: " << line << "\n";
        if (command == "create") {
            string sl_type;
            ss >> sl_type;

            // determine list type based on first char of name
            switch (list_type) {
                case 'i': {
                    // check for repeating
                    auto* target = searchForList<int>(name, listSLi);
                    if (target) outputFile << "ERROR: This name already exists!\n";
                    else listSLi.push_front(createSimpleList<int>(name, sl_type));
                    break;
                }
                case 'd': {
                    auto* target = searchForList<double>(name, listSLd);
                    if (target) outputFile << "ERROR: This name already exists!\n";
                    else listSLd.push_front(createSimpleList<double>(name, sl_type));
                    break;
                }
                case 's': {
                    auto* target = searchForList<string>(name, listSLs);
                    if (target) outputFile << "ERROR: This name already exists!\n";
                    else listSLs.push_front(createSimpleList<string>(name, sl_type));
                    break;
                }
            }
        }

        // handle push
        else if (command == "push") {
            switch (list_type) {
                case 'i': {
                    int i_value;
                    ss >> i_value;
                    auto* target = searchForList<int>(name, listSLi);
                    if (target) target->push(i_value);
                    else outputFile << "ERROR: This name does not exist!\n";
                    break;
                }
                case 'd': {
                    double d_value;
                    ss >> d_value;
                    auto* target = searchForList<double>(name, listSLd);
                    if (target) target->push(d_value);
                    else outputFile << "ERROR: This name does not exist!\n";
                    break;
                }
                case 's': {
                    string s_value;
                    ss >> s_value;
                    auto* target = searchForList<string>(name, listSLs);
                    if (target) target->push(s_value);
                    else outputFile << "ERROR: This name does not exist!\n";
                    break;
                }
            }
        }
        else if (command == "pop") {
            switch (list_type) {
                case 'i': {
                    auto* target = searchForList<int>(name, listSLi);
                    if (!target) {
                        outputFile << "ERROR: This name does not exist!\n";
                        break;
                    }
                    if (target->empty()) {
                        outputFile << "ERROR: This list is empty!\n";
                        break;
                    }
                    int value = target->pop();
                    outputFile << "Value popped: " << value << "\n";
                    break;
                }
        
                case 'd': {
                    auto* target = searchForList<double>(name, listSLd);
                    if (!target) {
                        outputFile << "ERROR: This name does not exist!\n";
                        break;
                    }
                    if (target->empty()) {
                        outputFile << "ERROR: This list is empty!\n";
                        break;
                    }
                    double value = target->pop();
                    outputFile << "Value popped: " << value << "\n";
                    break;
                }
        
                case 's': {
                    auto* target = searchForList<string>(name, listSLs);
                    if (!target) {
                        outputFile << "ERROR: This name does not exist!\n";
                        break;
                    }
                    if (target->empty()) {
                        outputFile << "ERROR: This list is empty!\n";
                        break;
                    }
                    string value = target->pop();
                    outputFile << "Value popped: " << value << "\n";
                    break;
                }
        
                default:
                    outputFile << "ERROR: Unknown list type!\n";
                    break;
            }
        }
        
    }


    // close files
    inputFile.close();
    outputFile.close();

    return 0;
}

int main() {
    // Get input & output file name
    string inputFileName;
    string outputFileName;
    
    cout <<  "Enter the name of the input file: ";
    cin >> inputFileName;
    cout <<  "Enter the name of the output file: ";
    cin >> outputFileName;

    // create lists of stacks and qeues to pass into process commands
    list<unique_ptr<SimpleList<int>>> listSLi; // all integer stacks and queues 
    list<unique_ptr<SimpleList<double>>> listSLd; // all double stacks and queues 
    list<unique_ptr<SimpleList<string>>> listSLs; // all string stacks and queues  

    return processComands(inputFileName, outputFileName, listSLi, listSLd, listSLs);
}
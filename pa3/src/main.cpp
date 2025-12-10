// THIS IS THE PROVIDED CODE FOR PROGRAM #3, DSA 1, FALL 2025

#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>
#include <cmath>
#include <cstring>
#include <cctype>
#include <cstdlib>

using namespace std;

// A simple class; each object holds three public fields
class Data {
public:
  string lastName;
  string firstName;
  string ssn;
};

// Load the data from a specified input file
void loadDataList(list<Data *> &l, const string &filename) {

  ifstream input(filename);
  if (!input) {
    cerr << "Error: could not open " << filename << "\n";
    exit(1);
  }

  // The first line indicates the size
  string line;
  getline(input, line);
  stringstream ss(line);
  int size;
  ss >> size;

  // Load the data
  for (int i = 0; i < size; i++) {
    getline(input, line);
    stringstream ss2(line);
    Data *pData = new Data();
    ss2 >> pData->lastName >> pData->firstName >> pData->ssn;
    l.push_back(pData);
  }

  input.close();
}

// Output the data to a specified output file
void writeDataList(const list<Data *> &l, const string &filename) {

  ofstream output(filename);
  if (!output) {
    cerr << "Error: could not open " << filename << "\n";
    exit(1);
  }

  // Write the size first
  int size = l.size();
  output << size << "\n";

  // Write the data
  for (auto pData:l) {
    output << pData->lastName << " " 
	   << pData->firstName << " " 
	   << pData->ssn << "\n";
  }

  output.close();
}

// Sort the data according to a specified field
// (Implementation of this function will be later in this file)
void sortDataList(list<Data *> &);

// The main function calls routines to get the data, sort the data,
// and output the data. The sort is timed according to CPU time.
int main() {
  string filename;
  cout << "Enter name of input file: ";
  cin >> filename;
  list<Data *> theList;
  loadDataList(theList, filename);

  cout << "Data loaded.\n";

  cout << "Executing sort...\n";
  clock_t t1 = clock();
  sortDataList(theList);
  clock_t t2 = clock();
  double timeDiff = ((double) (t2 - t1)) / CLOCKS_PER_SEC;

  cout << "Sort finished. CPU time was " << timeDiff << " seconds.\n";

  cout << "Enter name of output file: ";
  cin >> filename;
  writeDataList(theList, filename);

  return 0;
}

// -------------------------------------------------
// YOU MAY NOT CHANGE OR ADD ANY CODE ABOVE HERE !!!
// -------------------------------------------------

// You may add global variables, functions, and/or
// class defintions here if you wish.

bool cmpData(const Data* a, const Data* b) {
  // Compare last name
  if (a->lastName != b->lastName) 
    return a->lastName < b->lastName;

    // Compare first name
  if (a->firstName != b->firstName) 
    return a->firstName < b->firstName;
  
  // SSN strings compare
  return a->ssn < b->ssn;
}

// Implement quick sort
int partition(vector<Data*>& arr, int low, int high) {
  int mid = (low + high) / 2;

  // Median-of-three pivot
  if (cmpData(arr[mid], arr[low])) swap(arr[low], arr[mid]);
  if (cmpData(arr[high], arr[low])) swap(arr[low], arr[high]);
  if (cmpData(arr[high], arr[mid])) swap(arr[mid], arr[high]);

  swap(arr[mid], arr[high]);
  Data* pivot = arr[high];

  int i = low - 1;

  for (int j = low; j < high; j++) {
      if (cmpData(arr[j], pivot)) {
          i++;
          swap(arr[i], arr[j]);
      }
  }

  swap(arr[i + 1], arr[high]);
  return i + 1;
}



void quickSort(vector<Data *>& arr, int low, int high) {
  if (low < high) {
    // pi is the partition return index of pivot
    int pi = partition(arr, low, high);

    // recursion calls for smaller elements
    // and greater or equals elements
    quickSort(arr, low, pi - 1);
    quickSort(arr, pi + 1, high);
  }
}

void sortDataList(list<Data *> &l) {
  // Fill this in
  int size = l.size();
  vector<Data *> cpy;
  cpy.reserve(size);

  for (auto node : l) {
    cpy.push_back(node);
  }

  // Sort using quick sort
  quickSort(cpy, 0, size - 1);

  // Copy back into list
  auto it = l.begin();
  for (int i = 0; i < size; i++, it++)
    *it = cpy[i];
}
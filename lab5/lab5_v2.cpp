/////////////////////////////////////////////////////////////
// FileName: lab5.cpp
// Authors: Noah Cook and Scott Malin
// Purpose: To check for homographs in urls
//
/////////////////////////////////////////////////////////////

#include <iostream>
#include <string>
#include <cstddef>

using namespace std;


//prototypes:
double canonizeFunction(string fileName);
bool checkFunction(string fileName1, string fileName2);
string SplitFilename (string str);

// test.txt

int main()
{
    string fileName1;
    string fileName2;

    cout << "Specify the first filename:  ";
    cin >> fileName1;
    cout << "Specify the second filename:  ";
    cin >> fileName2;

    if (checkFunction(fileName1, fileName2)) {
        cout << "The paths are homographs\n";
    }
    else {
        cout << "The paths are not homographs\n";
    }
}


double canonizeFunction(string fileName) {
    double canonized = 1;
    string file;
    file = SplitFilename(fileName);

    for(int i = 0; i < file.size(); i++) {
        canonized = canonized * (int(file[i]) + i + 1);
    }

    return canonized;
}

bool checkFunction(string fileName1, string fileName2) {
    if  (canonizeFunction(fileName1) == canonizeFunction(fileName2)) {
        return 1;
    }
    return 0;
}

string SplitFilename (string str)
{
  size_t found = str.find_last_of("/\\");
  return str.substr(found+1);
}
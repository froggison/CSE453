/////////////////////////////////////////////////////////////
// FileName: lab5.cpp
// Authors: Noah Cook and Scott Malin
// Purpose: To check for homographs in urls
//
/////////////////////////////////////////////////////////////

#include <iostream>
#include <string>

using namespace std;


//prototypes:
double canonizeFunction(string fileName);
bool checkFunction(string fileName1, string fileName2);


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
    string tempString = "a";
    int tempInt1 = fileName.length();
    int tempInt2 = tempInt1 - 8;
    int tempInt3 = tempInt1 - 9;
    
    //find last '/' or '\' in file.  Start from there and make the length from there to the end replace 8.  And make that spot if it exists int2.  Int3 may be unnecessary.

    if (tempInt1 > 8) {
        if ((int(fileName[tempInt3]) == int('/')) || (int(fileName[tempInt3]) == int('\\'))) {
        	for(int i = tempInt2; i < tempInt1; i++) {
            	canonized = canonized * (int(fileName[i]) + i - tempInt2 + 1);
                }
        }
        else {
        	for(int i = 0; i < tempInt1; i++) {
           		canonized = canonized * (int(fileName[i]) + i + 1);
        	}
        }
    }
    else if (tempInt1 == 8){
        for(int i = 0; i < 8; i++) {
            canonized = canonized * (int(fileName[i]) + i + 1);
        }
	}
    else {
        for(int i = 0; i < tempInt1; i++) {
            canonized = canonized * (int(fileName[i]) + i + 1);
        }
    }
    return canonized;
}

bool checkFunction(string fileName1, string fileName2) {
    if  (canonizeFunction(fileName1) == canonizeFunction(fileName2)){
        return 1;
    }
    return 0;
}
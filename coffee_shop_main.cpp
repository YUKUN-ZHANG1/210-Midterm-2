// COMSC-210 | Midterm #2 | Yukun Zhang
// IDE used: Visual Studio Code

//I'm used to opening a separate file to program the project, 
//rather than with the entire code of a class, which is more readable. 
//But since I don't have time to rewrite the header files, I'll just 
//include the .cpp file, which still works. Make sure the 210-midterm-starter.cpp 
//is in the same folder as the current file. And that210-midterm-starter.cppdoes not have a main.

#include <iostream>
#include <fstream>
#include "210-midterm-starter.cpp"
using namespace std;

const string FILENNAME = "names";

int createNameArray (string filename, string* names) {
    ifstream inputFile("names.txt"); 
    if (!inputFile) {
        cout << "File open failure" << endl;
        return 1;
    }

    int count = 0;
    string name = "";
    while (std::getline(inputFile, name)) {
        count++;
    }

    inputFile.clear();
    inputFile.seekg(0, ios::beg);

    if
    names = new string[count];
    
}


int main() {
    string* names;
    int names_size = createNameArray(FILENNAME, names);

    return 0;
}


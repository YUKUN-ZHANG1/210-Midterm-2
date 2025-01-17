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

const string FILENNAME = "names.txt";
const int TIMES = 20;
const double HELP_FRONT_CUSTOMER_PERCENTAGE = 40;
const double NEW_CUSTOMER_JOIN_PERCENTAGE = 60;
const double LEAVE_QUEUE_END_PERCENTAGE = 20;
const double ANY_CUSTOMER_LEAVE_PERCENTAGE = 10;
const double VIP_CUSTOMER_PERCENTAGE = 10;

bool isHappened (double probability){
    int prob = rand() % 100 + 1;  // returns random number 1-100
    if(prob <= probability) {
        return true;
    }
    return false;
}

string getRandomName (string* names, int names_size){
    int value = rand() % (names_size);
    return names[value];
}

void insertCustomer (DoublyLinkedList& coffeeShopLine, string name){
    coffeeShopLine.push_back(name);
    cout<<"    "<<name<<" joins the line"<<endl;
}

void insertVIPCustomer (DoublyLinkedList& coffeeShopLine, string name){
    coffeeShopLine.push_front(name);
    cout<<"    "<<name<<" (VIP) joins the front of the line"<<endl;
}

void serviceCustomer (DoublyLinkedList& coffeeShopLine){
    cout<<"    "<<coffeeShopLine.get_pos(1)<<" is served"<<endl;
    coffeeShopLine.pop_front();
}

void left_line(DoublyLinkedList& coffeeShopLine, int& LineSize){
    int value = rand() % (LineSize)+1;
    cout<<"    "<<coffeeShopLine.get_pos(value)<<" left the line"<<endl;
    coffeeShopLine.delete_pos(value);
}

void last_left_line(DoublyLinkedList& coffeeShopLine, int& LineSize){
    cout<<"    "<<coffeeShopLine.get_pos(LineSize)<<" (at the rear) left the line"<<endl;
    coffeeShopLine.pop_back();
}

int createNameArray (string filename, string* names) {
    ifstream inputFile("names.txt"); 
    if (!inputFile) {
        cout << "File open failure" << endl;
        return -1;
    }

    int count = 0;
    string name = "";
    while (getline(inputFile, name)) {
        count++;
    }

    inputFile.close();
    inputFile.open(filename);

    if(count == 0)
        return -1;

    names = new string[count];
    int i = 0;

    while (getline(inputFile, name)) {
        names[i] = name;
        i++;
    }

    inputFile.close();

    return count;
}

void initializeLine(string* names, int names_size, DoublyLinkedList& coffeeShopLine){
    for(int i = 0; i<5; i++){
        insertCustomer(coffeeShopLine, getRandomName(names,names_size));
    }
}


void open(string* names, int names_size, DoublyLinkedList& coffeeShopLine){
    int line_size = 5;
    cout<<endl<<"Store opens:"<<endl;
    initializeLine(names, names_size, coffeeShopLine);
    cout<<endl;
    cout<<"    Resulting line: "<<endl;
    coffeeShopLine.print();
    cout<<endl;
    for(int i = 2; i <= TIMES; i++){
        cout<<"Time step #"<<i<<":"<<endl;
        if(isHappened(VIP_CUSTOMER_PERCENTAGE)){
            insertVIPCustomer(coffeeShopLine, getRandomName(names, names_size));
            line_size ++;
        }
        if(isHappened(NEW_CUSTOMER_JOIN_PERCENTAGE)){
            insertCustomer(coffeeShopLine, getRandomName(names, names_size));
            line_size ++;
        }
        if(line_size>0 && isHappened(HELP_FRONT_CUSTOMER_PERCENTAGE)){
            serviceCustomer(coffeeShopLine);
            line_size --;
        }
        if(line_size>0 && isHappened(ANY_CUSTOMER_LEAVE_PERCENTAGE)){
            left_line(coffeeShopLine, line_size);
            line_size --;
        }
        if(line_size>0 && isHappened(LEAVE_QUEUE_END_PERCENTAGE)){
            last_left_line(coffeeShopLine, line_size);
            line_size --;
        }
        cout<<"    Resulting line: "<<endl;
        coffeeShopLine.print();
        cout<<endl;
    }
}


int main() {
    string* names;
    int names_size = createNameArray(FILENNAME, names);
    if (names_size <= 0)
        return 1;

    DoublyLinkedList coffeeShopLine;
    open(names, names_size, coffeeShopLine);
    return 0;
}


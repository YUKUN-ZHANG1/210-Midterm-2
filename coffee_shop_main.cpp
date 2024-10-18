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
const string NAMES[99]= {
    "Adam", "Alex", "Andy", "Anne", "Aria", "Beau", "Beth", "Bill", "Brad", "Cara", "Chad", "Cole",
    "Dana", "Dave", "Dean", "Drew", "Elle", "Emma", "Eric", "Erik", "Evan", "Faye", "Finn", "Gabe", 
    "Gary", "Gina", "Greg", "Gwen", "Hank", "Hope", "Iris", "Ivan", "Jack", "Jade", "Jake", "Jane", 
    "Jean", "Jett", "Jill", "Joan", "Joel", "John", "Judy", "June", "Kate", "Katy", "Kirk", "Kyle", 
    "Lana", "Lane", "Leah", "Lena", "Liam", "Lily", "Lisa", "Lucy", "Luna", "Lyle", "Lynn", "Mark", 
    "Mary", "Matt", "Maya", "Mike", "Milo", "Mina", "Neal", "Neil", "Nell", "Nina", "Noah", "Noel", 
    "Nora", "Omar", "Otis", "Owen", "Paul", "Pete", "Reed", "Rene", "Rita", "Ross", "Ruby", "Ryan", 
    "Sage", "Sara", "Seth", "Tara", "Tess", "Tina", "Toby", "Tony", "Troy", "Vera", "Wade", "Will", 
    "Yara", "Zane", "Zara"
};
const int NAMESIZE = 99;
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

string getRandomName (){
    int value = rand() % NAMESIZE;
    return NAMES[value];
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


void initializeLine(DoublyLinkedList& coffeeShopLine){
    for(int i = 0; i<5; i++){
        insertCustomer(coffeeShopLine, getRandomName());
    }
}


void open(DoublyLinkedList& coffeeShopLine){
    int line_size = 5;
    cout<<endl<<"Store opens:"<<endl;
    initializeLine(coffeeShopLine);
    cout<<endl;
    cout<<"    Resulting line: "<<endl;
    coffeeShopLine.print();
    cout<<endl;
    for(int i = 2; i <= TIMES; i++){
        cout<<"Time step #"<<i<<":"<<endl;
        if(isHappened(VIP_CUSTOMER_PERCENTAGE)){
            insertVIPCustomer(coffeeShopLine, getRandomName());
            line_size ++;
        }
        if(isHappened(NEW_CUSTOMER_JOIN_PERCENTAGE)){
            insertCustomer(coffeeShopLine, getRandomName());
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
    DoublyLinkedList coffeeShopLine;
    open(coffeeShopLine);
    return 0;
}


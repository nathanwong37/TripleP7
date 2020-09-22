//program just to remove whitespaces in my text file

#include<fstream>
#include<iostream>
#include<sstream>
using namespace std;
int main() {
    ofstream myFile;
    ifstream inFile;
    inFile.open("Pi.txt");
    stringstream buffer;
    buffer << inFile.rdbuf();
    inFile.close();
    myFile.open("Pi.txt");
    string temp;
    string str = "";
    while(getline(buffer,temp,' ')) {
        str = str + temp;
    }
    myFile << str;
    myFile.close();
    return 0;
}
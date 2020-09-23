//Author: Nathan Wong
//Date: 9/21/2020
//This program will find the first 7 prime palindromic numbers of pi
//Will take in a file from command line with digits of pi, and return an int of the 7 digits if found, or -1 if not found
//If no file is found will prompt to type in a file until found

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <set>

using namespace std;
//global prime number variables
bool prime[10] = {false, false, true, true, false, true, false, true, false, false};
//helper methods
int findPrimePalindrome(string pi);
bool expandAroundCenter(int index, string pi);

//main function, accepts an address for a file with digits of pi
int main(int argc, char *argv[])
{
    string pi;
    ifstream inFile;
    inFile.open(argv[1]);
    while (!inFile.is_open())
    {
        cout << "Address not found, please enter a valid address or press q to quit" << endl;
        string input;
        cin >> input;
        if (input == "q" || input == "Q")
        {
            cout << "Exit" << endl;
            return 0;
        }
        inFile.open(input);
    }
    //needs input sanitization
    stringstream buffer;
    char c;
    bool flag = false;
    //make sure each character is valid
    while (inFile.get(c))
    {
        //not a digit
        if (!isdigit(c) && c != '.')
        {
            cerr << "invalid character found" << endl;
            return -1;
        }
        //too many decimals
        if (c == '.' && flag)
        {
            cerr << "too many decimals" << endl;
            return -1;
        }
        else if (c == '.')
        {
            flag = true;
        }
        buffer << c;
    }
    pi = buffer.str();
    int ans = findPrimePalindrome(pi);
    cout << ans << endl;
    return 0;
}

//method to find the 7 prime palindrome digits
int findPrimePalindrome(string pi)
{
    //erases . if exists
    if (pi.at(1) == '.')
    {
        pi.erase(pi.begin() + 1);
    }
    int index = 3;
    while (index < pi.length())
    {
        //if the number is not prime skip ahead 4, can't be used
        if (!prime[pi.at(index) - 48])
        {
            index += 4;
            continue;
        }
        //otherwise expand and see if solution is found
        if (expandAroundCenter(index, pi))
        {
            break;
        }
        //increase index if not
        index++;
    }
    string ans = pi.substr(index - 3, 7);
    return atoi(ans.c_str());
}

//method that expands around the center starting at an index
bool expandAroundCenter(int index, string pi)
{
    int i = index;
    int j = index;
    while (j < pi.length() && i >= 0 && j - i <= 6)
    {
        if (prime[pi.at(j) - 48] && prime[pi.at(i) - 48] && pi.at(i) == pi.at(j))
        {
            //found answer
            if (j - i == 6)
            {
                break;
            }
            j++;
            i--;
            continue;
        }
        return false;
    }
    return j - i == 6;
}
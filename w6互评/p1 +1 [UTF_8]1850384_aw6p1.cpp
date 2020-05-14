//
// Created by Zhengyi on 2020/4/7.
// Using Google Naming Regulations
// Using C++11 standard, compiled with 0 warnings on
// Apple clang version 11.0.3 (clang-1103.0.32.29).
// Compiling configuration is [g++ -Wall -std=gnu++11 aw6p1.cpp]
//


#include <iostream>
#include <string>
#include <cstdlib>

/* Interface */
// The functions below are visible to users.
int readData(std::istream &is, std::string &telegram);
void encrypt(std::string &telegram, int shift);


int main() {
    using namespace std;
    int code = 0;
    string tel;
    code = readData(cin, tel);
    encrypt(tel, code);

    cout << tel;
    return 0;
}

/* Assistant functions */
// User should not know the existence of them.
bool isUpper(char c) {
    return (c >= 'A' && c <= 'Z');
}

bool isLower(char c) {
    return (c >= 'a' && c <= 'z');
}

/* Implement the interface functions.*/
// Read and check.
int readData(std::istream &is, std::string &telegram) {
    int shift = -1;
    bool first_time = true;
    while (shift < 0 || shift > 25) {     // keep reading until shift is reasonable
        if (first_time) {
            first_time = false;
        } else {
            std::cout << "Illegal, try a number between 0 and 25.\n";
        }
        if(!is) {
            std::cerr << "You just jammed my input stream!\n"
                      << "Exiting."<< std::endl;
            exit(0);
        }
        is >> shift;
    }
    std::getline(is, telegram);    // read the rest of line and throw it.
    std::getline(is, telegram);
    return shift;
}


void encrypt(std::string &telegram, int shift) {
    for (auto &c : telegram) {
        if (isUpper(c)) {
            c = (c + shift - 'A') % 26 + 'A';
        } else if (isLower(c)) {
            c = (c + shift - 'a') % 26 + 'a';
        }
        // else do nothing
    }
}

/*
 * Advent of Code Day 02
 *
 */
#include <fstream>
#include <iostream>

#define FILENAME01 "../input.txt"
#define FILENAME02 "../test_data.txt"

using namespace std;

int main() {

    const std::string filename = FILENAME01;
    std::fstream inputFile(filename);
    if (!inputFile.is_open()) {
        std::cerr << "Could not open file " << filename << std::endl;
        exit(1);
    }

    std::string line;
    int password = 0;
    int dialPointer = 50;
    int clicks = 0;

    while (!inputFile.eof()) {
        std::getline(inputFile, line);
        if (line.size() > 0) {
            clicks = std::stoi(line.substr(1));
            clicks = clicks % 100;
            if (line[0] == 'L') {
                dialPointer -= clicks;
                if (dialPointer < 0) dialPointer = 100 + dialPointer;
                if (dialPointer == 0) {
                    password ++;
                }
            } else {
                // Assume that it's always 'R'
                dialPointer += clicks;
                dialPointer = dialPointer % 100;
                if (dialPointer == 0) {
                    password ++;
                }
            }
            cout << dialPointer << endl;
        }
    }
    std::cout << "Password is " << password << endl;
    return 0;
}
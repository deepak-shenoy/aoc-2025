/*
* Advent of Code Day 03 Part 2
 *
 */
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#define FILENAME01 "../input.txt"
#define FILENAME02 "../test_data.txt"

const std::string filename = FILENAME01;

long processLine(std::string line) {
    int lineSize = line.size();
    long largestNumber = 0;
    long result = 0;
    int index = 0;
    for (int numbersLeft = 12; numbersLeft > 0; numbersLeft--) {
        largestNumber = 0;
        for (int i = index; i < lineSize - numbersLeft + 1; i++) {
            long numberAtIndex = std::stol(std::to_string(line[i] - '0'));
            if (numberAtIndex > largestNumber) {
                largestNumber = numberAtIndex;
                index = i + 1;
            }
        }
        //std::cout << largestNumber;
        result += (largestNumber * (std::pow(10,(numbersLeft-1))));
    }
    //std::cout << std::endl;
    //std::cout << result << std::endl;
    return result;
}

int main() {
    std::fstream inputFile(filename);
    std::string line;
    long result = 0;
    while (!inputFile.eof()) {
        std::getline(inputFile, line);
        result += processLine(line);
    }
    std::cout << "Result: " << result << std::endl;
    return 0;
}
/*
* Advent of Code Day 03 Part 1
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
    int index1 = 0;
    long largestNumber = 0;
    long secondLargestNumber = 0;
    for (int i = 0; i < lineSize - 1; i++) {
        long numberAtIndex = std::stol(std::to_string(line[i] - '0'));
        if (numberAtIndex > largestNumber) {
            largestNumber = numberAtIndex;
            index1 = i;
        }
    }
    for (int j = lineSize; j > index1; j--) {
        long numberAtIndex = std::stol(std::to_string(line[j] - '0'));
        if (numberAtIndex > secondLargestNumber) {
            secondLargestNumber = numberAtIndex;
        }
    }
    return largestNumber * 10 + secondLargestNumber;
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
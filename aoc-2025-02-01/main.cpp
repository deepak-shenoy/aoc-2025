/*
* Advent of Code Day 02
 *
 */
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#define FILENAME01 "../input.txt"
#define FILENAME02 "../test_data.txt"

const std::string filename = FILENAME01;

long getInvalidNumber(std::string token) {
    if (token.size() % 2 != 0) return 0;
    // Don't waste time on odd length number
    int middleIndex = token.size() / 2;
    // Simple solution - should be symmetrical from the center
    std::string firstNumber = token.substr(0, middleIndex);
    std::string secondNumber = token.substr(middleIndex);
    if (firstNumber.compare(secondNumber) == 0 ) {
        // Match
        return std::stol(token);
    }
    else return 0;
}

int main() {
    // Read in data
    std::fstream inputFile(filename);
    // Assumption - data is on one line
    std::string rawLine;
    std::getline(inputFile, rawLine);
    // Process line by creating a stream from the line
    std::stringstream line(rawLine);
    std::string rawToken, range1, range2;
    long result = 0;
    // std::cout << "Full line: " << line.str() << std::endl;  // Debugging
    // Process tokens from CSV
    while (std::getline(line, rawToken, ',')) {
        std::stringstream token(rawToken);
        // std::cout << token.str() << std::endl;  // Debuging
        // Get from to range separated by the dash character
        std::getline(token, range1, '-');
        std::getline(token, range2, '-');
        for (long i = std::stol(range1); i <= std::stol(range2); i++) {
            result += getInvalidNumber(std::to_string(i));
        }
    }
    std::cout << "Result: " << result << std::endl;
    return 0;
}
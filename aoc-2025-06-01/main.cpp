/*
* Advent of Code Day 06 Part 1
 *
 */
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#define FILENAME01 "../input.txt"
#define FILENAME02 "../test_data.txt"

const std::string filename = FILENAME01;

int main() {
    std::fstream inputFile(filename);
    std::string rawLine;
    std::vector<std::vector<std::string>> problemMap;
    while (!inputFile.eof()) {
        std::getline(inputFile, rawLine);
        std::stringstream inputLine(rawLine);
        std::string columnValue;
        std::vector<std::string> line;
        while (!inputLine.eof()) {
            getline(inputLine, columnValue, ' ');
            if (columnValue[0] == NULL) continue;
            line.push_back(columnValue);
            std::cout << columnValue << " ";
        }
        problemMap.push_back(line);
        std::cout<<std::endl;
    }

    long result = 0;

    // Assumption that the rows are of equal size
    for (int j = 0; j < problemMap.at(0).size(); j++) {
        char mathOperator = problemMap.at(problemMap.size() - 1).at(j)[0];
        long columnResult = -1;
        for (int i = 1; i < problemMap.size() - 1; i ++) {
            if (columnResult == -1) columnResult = std::stol(problemMap.at(0).at(j));
            if (mathOperator == '+') {
                columnResult = columnResult + std::stol(problemMap.at(i).at(j));
            } else {
                columnResult = columnResult * std::stol(problemMap.at(i).at(j));
            }
        }
        result += columnResult;
    }

    std::cout << "Result: " << result << std::endl;

    return 0;
}
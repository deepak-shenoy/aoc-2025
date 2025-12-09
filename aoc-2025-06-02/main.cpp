/*
* Advent of Code Day 06 Part 2
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
    std::vector<std::string> problemMap;
    int maxLineSize = 0;
    while (!inputFile.eof()) {
        std::getline(inputFile, rawLine);
        problemMap.push_back(rawLine);
        if (rawLine.size() > maxLineSize) maxLineSize = rawLine.size();
    }

    std::string operatorLine = problemMap.at(problemMap.size() - 1);
    int currentIndex = 0; int nextIndex = 0;
    long result = 0;

    // Get the current operator and move the index here
    // Find out how far the next operator is or if we will reach the end of the line (then stop)
    char plusChar = '+';
    char multChar = '*';

    bool endOfNumbers = false;
    bool plusOperator = true;
    while (!endOfNumbers) {
        int nextOperator1 = operatorLine.find(plusChar, currentIndex + 1);
        int nextOperator2 = operatorLine.find(multChar, currentIndex + 1);
        if (nextOperator1 == std::string::npos && nextOperator2 == std::string::npos) {
            endOfNumbers = true;
            nextIndex = maxLineSize + 1;
        } else if (nextOperator1 == std::string::npos) nextIndex = nextOperator2;
        else if (nextOperator2 == std::string::npos) nextIndex = nextOperator1;
        else nextIndex = nextOperator1 < nextOperator2 ? nextOperator1: nextOperator2;
        plusOperator = operatorLine[currentIndex] == plusChar ? true : false;

        // From the next operator and minus two steps back is where the first column begins
        long columnResult = -1;
        for (int i = nextIndex - 2; i >=  currentIndex; i--) {
            std::string thinColumnValue = "";
            for (int j = 0; j < problemMap.size() - 1; j ++) {
                if (i <= problemMap.at(j).size()) {
                    char valueFound = problemMap.at(j)[i];
                    thinColumnValue.push_back(valueFound != NULL ? valueFound : ' ');
                } else thinColumnValue.push_back(' ');
            }
            long value = std::stol(thinColumnValue);
            //std::cout << value << std::endl;
            if (columnResult == -1) columnResult = value;
            else {
                if (plusOperator) columnResult += value;
                else columnResult *= value;
            }
        }
        //std::cout << columnResult << std::endl;
        currentIndex = nextIndex;
        // from that column to the index of the current operator
        // Go down the rows and perform the arithmetic
        // if we haven't reached the end of the line then move the index to the next operator and start from above
        result += columnResult;
    }


    std::cout << "Result: " << result << std::endl;

    return 0;
}
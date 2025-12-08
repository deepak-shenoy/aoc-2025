/*
* Advent of Code Day 04 Part 1
 *
 */
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#define FILENAME01 "../input.txt"
#define FILENAME02 "../test_data.txt"

#define PAPER_ROLL '@'
#define REMVD_ROLL 'x'
#define BLANK_SPCE '.'

const std::string filename = FILENAME01;

int MAX_X = 0;
int MAX_Y = 0;

bool validCoordinate(int x, int y, std::vector<std::string> &paperMap) {
    if (paperMap.at(y).at(x) != PAPER_ROLL) return false;;
    int numberOfRolls = 0;
    bool checkLeft = true, checkRight = true, checkTop = true, checkBottom = true;
    if (x == 0) {
        // We cannot check values to the left
        checkLeft = false;
    }
    if (x == MAX_X -1) {
        // We cannot check values to the right
        checkRight = false;
    }
    if (y == 0) {
        // We cannot check values at the top
        checkTop = false;
    }
    if (y == MAX_Y -1) {
        // We cannot check values at the bottom
        checkBottom = false;
    }
    if (checkLeft && (paperMap.at(y).at(x - 1) == PAPER_ROLL || paperMap.at(y).at(x - 1) == REMVD_ROLL)) {
        numberOfRolls++;
    }
    if (checkRight && (paperMap.at(y).at(x + 1) == PAPER_ROLL || paperMap.at(y).at(x + 1) == REMVD_ROLL)) {
        numberOfRolls++;
    }
    if (checkTop && (paperMap.at(y - 1).at(x) == PAPER_ROLL || paperMap.at(y - 1).at(x) == REMVD_ROLL)) {
        numberOfRolls++;
    }
    if (checkBottom && (paperMap.at(y + 1).at(x) == PAPER_ROLL || paperMap.at(y + 1).at(x) == REMVD_ROLL)) {
        numberOfRolls++;
    }

    // Top left
    if (checkTop && checkLeft && (paperMap.at(y - 1).at(x - 1) == PAPER_ROLL || paperMap.at(y - 1).at(x - 1) == REMVD_ROLL)) {
        numberOfRolls++;
    }
    // Bottom left
    if (checkBottom && checkLeft && (paperMap.at(y + 1).at(x - 1) == PAPER_ROLL || paperMap.at(y + 1).at(x - 1) == REMVD_ROLL)) {
        numberOfRolls++;
    }

    // Top right
    if (checkTop && checkRight && (paperMap.at(y - 1).at(x + 1) == PAPER_ROLL || paperMap.at(y - 1).at(x + 1) == REMVD_ROLL)) {
        numberOfRolls++;
    }
    // Bottom right
    if (checkBottom && checkRight && (paperMap.at(y + 1).at(x + 1) == PAPER_ROLL || paperMap.at(y + 1).at(x + 1) == REMVD_ROLL)) {
        numberOfRolls++;
    }
    if (numberOfRolls > 3) return false;
    else {
        paperMap.at(y).at(x) = REMVD_ROLL;
        return true;
    }
}

void cleanMap(std::vector<std::string> &paperMap) {
    for (int y = 0; y < MAX_Y; y++) {
        for (int x = 0; x < MAX_X; x++) {
            if (paperMap.at(y).at(x) == REMVD_ROLL) {
                paperMap.at(y).at(x) = BLANK_SPCE;
            }
        }
    }
}

int main() {
    std::vector<std::string> paperMap;
    std::fstream inputFile(filename);
    std::string inputLine;
    while (!inputFile.eof()) {
        std::getline(inputFile, inputLine);
        paperMap.push_back(inputLine);
    }

    // Assumption that the map has common X and Y sizes
    MAX_X = paperMap.at(0).size();
    MAX_Y = paperMap.size();

    int result = 0;
    int rollsRemoved;
    do {
        rollsRemoved = 0;
        for (int y = 0; y < MAX_Y; y++) {
            for (int x = 0; x < MAX_X; x++) {
                if (validCoordinate(x, y, paperMap)) rollsRemoved++;
            }
        }
        cleanMap(paperMap);
        result += rollsRemoved;
    } while (rollsRemoved !=0);

    std::cout << "Result: " << result << std::endl;
    return 0;
}
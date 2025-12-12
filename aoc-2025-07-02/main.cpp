/*
* Advent of Code Day 07 Part 2
 *
 */
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <chrono>
#include <set>

#define FILENAME01 "../input.txt"
#define FILENAME02 "../test_data.txt"

#define BEAM__CHAR '|'
#define SPLIT_CHAR '^'
#define FREE_SPACE '.'

const std::string filename = FILENAME01;

int MAX_X;
int counter = 0;

class Coordinate {
public:
    Coordinate(int xx, int yy): x{xx}, y{yy} {};
    int x;
    int y;
    long sum;
    bool operator< (const Coordinate &otherCoordinate) const {
        if (x != otherCoordinate.x) {
            return x < otherCoordinate.x;
        }
        return y < otherCoordinate.y;
    }
};

std::set<Coordinate> coordinates;

long findPaths(std::vector<std::string> &rawMap, int x, int y) {
    long levelResult = 0;
    if (y == rawMap.size()) return 1;
    if (rawMap.at(y).at(x) == BEAM__CHAR) {
        levelResult = findPaths(rawMap, x, y + 1);
    } else {
        Coordinate coordinate(x, y);
        if (!coordinates.contains(coordinate)) {
            if (rawMap.at(y).at(x) == SPLIT_CHAR && (x - 1 >= 0) && rawMap.at(y).at(x - 1) && rawMap.at(y).at(x - 1) == BEAM__CHAR) { // && rawMap.at(y - 1).at(x - 1) != BEAM__CHAR) {
                levelResult += findPaths(rawMap, x - 1, y + 1);
            }
            if (rawMap.at(y).at(x) == SPLIT_CHAR && (x + 1 < MAX_X) && rawMap.at(y).at(x + 1) && rawMap.at(y).at(x + 1) == BEAM__CHAR) { // && rawMap.at(y - 1).at(x + 1) != BEAM__CHAR) {
                levelResult += findPaths(rawMap, x + 1, y + 1);
            }
            coordinate.sum = levelResult;
            coordinates.insert(coordinate);
        } else {
            Coordinate cachedCoordinate = *coordinates.find(coordinate);
            return cachedCoordinate.sum;
        }
    }
    return levelResult;
}

int main() {
    std::fstream inputFile (filename);
    std::vector<std::string> rawMap;
    std::string rawLine;
    while (!inputFile.eof()) {
        std::getline(inputFile, rawLine);
        rawMap.push_back(rawLine);
    }

    std::vector<int> beamXCoordinates;

    // Seed the first beam - assumption that an 'S' marker exists
    int firstBeam = 0;
    // Assumption that the width is the same
    MAX_X = rawMap.at(0).size();
    for (; firstBeam < MAX_X && rawMap.at(0)[firstBeam] != 'S'; firstBeam++);
    beamXCoordinates.push_back(firstBeam);

    long result = 0;

    // Start timer
    auto start = std::chrono::high_resolution_clock::now();
    long counter = 0;

    for (int y = 1; y < rawMap.size(); y ++) {
        for (int x = 0; x < MAX_X; x++) {
            std::vector<int> copyOfBeamXCoordinates(beamXCoordinates);
            for (int b = 0; b <  copyOfBeamXCoordinates.size(); b++) {
                // Continue existing beams
                if (copyOfBeamXCoordinates[b] == x && rawMap.at(y).at(x) == FREE_SPACE) rawMap.at(y).at(x) = BEAM__CHAR;
                if (copyOfBeamXCoordinates[b] == x && rawMap.at(y).at(x) == SPLIT_CHAR) {
                    // Stop this existing beam
                    beamXCoordinates.erase(std::remove_if(beamXCoordinates.begin(), beamXCoordinates.end(), [x](int value){return value == x;}), beamXCoordinates.end());
                    // Is there a beam to the left of the splitter?
                    if (x - 1 >=  0 && rawMap.at(y).at(x - 1) == FREE_SPACE) {
                        // If it's available then add the new beam
                        beamXCoordinates.push_back(x - 1);
                        rawMap.at(y).at(x - 1) = BEAM__CHAR;
                    }
                    // Is there a beam to the right of the splitter?
                    if (x + 1 < MAX_X && rawMap.at(y).at(x + 1) == FREE_SPACE) {
                        // If it's available then add the new beam
                        beamXCoordinates.push_back(x + 1);
                        rawMap.at(y).at(x + 1) = BEAM__CHAR;
                    }
                }
            }
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Tree construction took: " << elapsed.count() << " seconds" << std::endl;



    // for (int y = 1; y < rawMap.size(); y ++) {
    //     for (int x = 0; x < MAX_X; x++) {
    //         std::cout << rawMap.at(y).at(x);
    //     }
    //     std::cout << std::endl;
    // }

    start = std::chrono::high_resolution_clock::now();
    result = findPaths(rawMap, firstBeam, 1);
    end = std::chrono::high_resolution_clock::now();
    elapsed = end - start;
    std::cout << "Path calculations took: " << elapsed.count() << " seconds" << std::endl;

    std::cout << result << std::endl;
    return 0;
}
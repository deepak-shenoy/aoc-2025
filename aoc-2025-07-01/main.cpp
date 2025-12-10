/*
* Advent of Code Day 07 Part 1
 *
 */
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#define FILENAME01 "../input.txt"
#define FILENAME02 "../test_data.txt"

#define BEAM__CHAR '|'
#define SPLIT_CHAR '^'
#define FREE_SPACE '.'

const std::string filename = FILENAME01;

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
    const int MAX_X = rawMap.at(0).size();
    for (; firstBeam < MAX_X && rawMap.at(0)[firstBeam] != 'S'; firstBeam++);
    beamXCoordinates.push_back(firstBeam);

    int result = 0;
    bool leftSideRay = false, rightSideRay  = false;

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
                        leftSideRay = true;
                    } else leftSideRay = false;
                    // Is there a beam to the right of the splitter?
                    if (x + 1 < MAX_X && rawMap.at(y).at(x + 1) == FREE_SPACE) {
                        // If it's available then add the new beam
                        beamXCoordinates.push_back(x + 1);
                        rawMap.at(y).at(x + 1) = BEAM__CHAR;
                        rightSideRay  = true;
                    } else rightSideRay  = false;
                    if (leftSideRay || rightSideRay) result ++;
                }
            }
        }
    }

    // for (int y = 1; y < rawMap.size(); y ++) {
    //     for (int x = 0; x < MAX_X; x++) {
    //         std::cout << rawMap.at(y).at(x);
    //     }
    //     std::cout << std::endl;
    // }

    std::cout << result << std::endl;
    return 0;
}
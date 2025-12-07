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
    const int tokenSize = token.size();
    for (int repeatSize = 1; repeatSize <= tokenSize/2; repeatSize++) {
        // Must be able to repeat that sequence
        if (tokenSize % repeatSize !=0) continue;
        bool repeat = true;
        for (int i = 0; i < tokenSize && repeat; i++) {
            if (repeat) {
                if ((i+(2 * repeatSize -1)) < tokenSize) {
                    for (int j=0; j < repeatSize && repeat; j++) {
                        if (token[i+j] != token[i+repeatSize+j]) {
                            repeat = false;
                            break;
                        }
                    }
                }
                if (repeat && ((i + repeatSize) == (tokenSize - repeatSize))) {
                    std::cout << stol(token) << " repeatsize=" << repeatSize << std::endl;
                    return stol(token);
                }
            }
        }
    }
    return 0;
    // bool repeatOfOne = tokenSize > 1;
    // bool repeatOfTwo = tokenSize > 3;
    // bool repeatOfThree = tokenSize > 5;
    //     if (repeatOfOne) {
    //         if ((i+1) < tokenSize) {
    //             if (token[i] == token[i+1]) {
    //                 if (repeatOfOne && i == tokenSize-1) {
    //                     std::cout << stol(token) << " one" << std::endl;
    //                     return stol(token);
    //                 }
    //             } else repeatOfOne = false;
    //         } else if (i == tokenSize-1) {
    //             std::cout << stol(token) << " one" << std::endl;
    //             return stol(token);
    //         }
    //     }
    //
    //     if (repeatOfTwo) {
    //         if ((i+3) < tokenSize) {
    //             if (tokenSize && token[i] == token[i+2] && token[i+1] == token[i+3]) {
    //                 if (repeatOfTwo && i == tokenSize-2) {
    //                     std::cout << stol(token) << " two" << std::endl;
    //                     return stol(token);
    //                 }
    //             } else repeatOfTwo = false;
    //         } else if (i == tokenSize-2) {
    //             std::cout << stol(token) << " two" << std::endl;
    //             return stol(token);
    //         }
    //     }
    //
    //     if (repeatOfThree) {
    //         if ((i+5) < tokenSize) {
    //             if (token[i] == token[i+3] && token[i+1] == token[i+4] && token[i+2] == token[i+5]) {
    //                 if (repeatOfTwo && i == tokenSize-2) {
    //                     std::cout << stol(token) << " three" << std::endl;
    //                     return stol(token);
    //                 }
    //             } else repeatOfThree = false;
    //         } else if (i == tokenSize-3) {
    //             std::cout << stol(token) << " three" << std::endl;
    //             return stol(token);
    //         }
    //     }
    // }

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
/*
* Advent of Code Day 05 Part 2
 *
 */
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#define FILENAME01 "../input.txt"
#define FILENAME02 "../test_data.txt"

const std::string filename = FILENAME01;

class Tuple {
public:
    long start;
    long end;

    bool operator<(const Tuple &otherTuple) const {
        return start < otherTuple.start;
    }
};

long validIngredient(std::string line, std::vector<Tuple> &ranges) {
    long ingredientNumber = std::stol(line);
    for (int i = 0; i < ranges.size(); i++) {
        if (ingredientNumber >= ranges.at(i).start && ingredientNumber <= ranges.at(i).end) {
            return 1;
        }
    }
    return 0;
}

void printRanges(std::vector<Tuple> &range) {
    for (Tuple t: range) {
        std::cout << t.start << "-" << t.end << std::endl;
    };
}

int main() {
    // Read in data
    std::fstream inputFile(filename);

    // Read in recipies
    std::vector<Tuple> ranges;
    std::string rawLine, fromRange, toRange;
    while (true) {
        std::getline(inputFile, rawLine);
        if (rawLine[0] == NULL || rawLine[0] == ' ' || rawLine[0] == '\n') break;
        std::stringstream line(rawLine);
        std::getline(line, fromRange, '-');
        std::getline(line, toRange, '-');
        Tuple tuple;
        tuple.start = std::stol(fromRange);
        tuple.end = std::stol(toRange);
        ranges.push_back(tuple);
    }

    // Sort list
    std::sort(ranges.begin(), ranges.end());

    //printRanges(ranges);

    int numberOfRanges = ranges.size();
    for (int i = 1; i < numberOfRanges;) {
        if (ranges.at(i).start == 33261692788699) {
            int abc=10;
        }
        if (ranges.at(i).start >= ranges.at(i-1).start && ranges.at(i).start <= ranges.at(i-1).end) {
            if (ranges.at(i).end >= ranges.at(i-1).end) {
                ranges.at(i-1).end = ranges.at(i).end;
                ranges.erase(ranges.begin() + i);
                numberOfRanges--;
            } else {
                ranges.erase(ranges.begin() + i);
                numberOfRanges--;
            }
        } else i++;
    }

    // numberOfRanges = ranges.size();
    // for (int i = 1; i < numberOfRanges;) {
    //     if (ranges.at(i-1).end + 1 == ranges.at(i).start) {
    //         ranges.at(i-1).end = ranges.at(i).end;
    //         ranges.erase(ranges.begin() + i);
    //         numberOfRanges--;
    //     } else i++;
    // }

    printRanges(ranges);
    std::cout <<std::endl;

    long results = 0;
    for (int i = 0; i < ranges.size(); i++) {
        results += (ranges.at(i).end - ranges.at(i).start) + 1;
    }

    std::cout << "Results: " << results << std::endl;
    return 0;
}

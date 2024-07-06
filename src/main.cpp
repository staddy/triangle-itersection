#include <fstream>
#include <iostream>
#include <sstream>

#include "geometry_utils.hpp"

void trim(std::string& inputString) {
    auto numberSignPosition = inputString.find('#');
    if (numberSignPosition != std::string::npos) {
        inputString = inputString.substr(0, numberSignPosition);
    }
    inputString.erase(
        inputString.begin(),
        std::find_if(inputString.begin(), inputString.end(),
                     [](unsigned char ch) { return !std::isspace(ch); }));
    inputString.erase(
        std::find_if(inputString.rbegin(), inputString.rend(),
                     [](unsigned char ch) { return !std::isspace(ch); })
            .base(),
        inputString.end());
}

template <typename T>
constexpr T ValuesCount;
template <>
constexpr size_t ValuesCount<Point2D> = 2;
template <>
constexpr size_t ValuesCount<Point3D> = 3;

std::vector<double> parseValues(const std::string& input, size_t count,
                                size_t line) {
    std::vector<double> parsed(count);
    std::istringstream stringStream(input);
    for (size_t i = 0; i < count; ++i) {
        stringStream >> parsed[i];
        if ((stringStream.rdstate() & std::ifstream::failbit) != 0) {
            throw std::exception((std::string("Line ") + std::to_string(line) +
                                  " has only " + std::to_string(i) +
                                  " values (" + std::to_string(count) +
                                  " expected)")
                                     .c_str());
        }
    }
    return parsed;
}

template <typename T>
bool runTest(const std::vector<std::string>& testCase, size_t number,
             size_t line) {
    auto valuesCount = ValuesCount<T> * 3;
    std::vector<double> vertices1 = parseValues(testCase[0], valuesCount, line);
    std::vector<double> vertices2 = parseValues(testCase[1], valuesCount, line);
    auto result = GeometryUtils::trianglesIntersect(Triangle<T>(vertices1),
                                                    Triangle<T>(vertices2));
    bool expectedResult;
    if (testCase[2] == "true") {
        expectedResult = true;
    } else if (testCase[2] == "false") {
        expectedResult = false;
    } else {
        throw std::exception((std::string("Line ") + std::to_string(line) +
                              " has unknown test result: " + testCase[2])
                                 .c_str());
    }
    if (result != expectedResult) {
        std::cout << "test " << number << ": expected " << testCase[2]
                  << ", got " << (result ? "true" : "false") << std::endl;
        return false;
    }
    return true;
}

void runTests(const std::string& fileName, bool is3D) {
    std::ifstream file(fileName);
    std::string line;
    unsigned int total_tests = 0;
    unsigned int failed_tests = 0;

    size_t testsDone = 0;
    size_t failed = 0;
    size_t counter = 0;
    size_t currentLine = 0;
    std::vector<std::string> testCase(3);
    while (std::getline(file, line)) {
        trim(line);
        if (line.empty()) {
            ++currentLine;
            continue;
        }
        testCase[counter % 3] = line;
        if (counter % 3 == 2) {
            auto result =
                is3D ? runTest<Point3D>(testCase, testsDone + 1, currentLine)
                     : runTest<Point2D>(testCase, testsDone + 1, currentLine);
            if (!result) ++failed;
            ++testsDone;
        }
        ++counter;
        ++currentLine;
    }

    std::cout << "Tests done " << testsDone << "; failed " << failed << "\n";
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " [2D|3D] <filename>\n";
        return 1;
    }
    std::string fileName;
    auto is3D = false;
    if (argc > 2) {
        is3D = std::string(argv[1]) == "3D";
        fileName = argv[2];
    } else {
        fileName = argv[1];
    }
    try {
        runTests(fileName, is3D);
    } catch (const std::exception& e) {
        std::cerr << e.what();
        return 2;
    }

    return 0;
}

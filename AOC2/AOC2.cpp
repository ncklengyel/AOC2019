#include <iostream>
#include <fstream>
#include <vector>
#include <string.h>
#include <stdexcept>
#include <boost/algorithm/string.hpp>
#include <utility>

enum CODE : int
{
    ADD = 1,
    MULTIPLY = 2,
    STOP = 99
};

void process(int code, int input1, int input2, int output, std::vector<int> &vect)
{
    int result = 0;

    switch (code)
    {
    case CODE::ADD:
        result = vect.at(input1) + vect.at(input2);
        break;

    case CODE::MULTIPLY:
        result = vect.at(input1) * vect.at(input2);
        break;

    default:
        std::cout << "Unsupported code !" << std::endl;
        break;
    }

    vect.at(output) = result;
}

void run(const std::vector<std::string> &&vect, std::vector<int> &outVect)
{
    std::vector<int> vectInt;
    for (auto num : vect)
    {
        vectInt.push_back(std::stoi(num));
    }

    vectInt.at(1) = 12;
    vectInt.at(2) = 2;

    int currentIndex = 0;
    while (vectInt.at(currentIndex) != CODE::STOP)
    {
        process(vectInt.at(currentIndex), vectInt.at(currentIndex + 1), vectInt.at(currentIndex + 2), vectInt.at(currentIndex + 3), vectInt);
        currentIndex += 4;
    }

    outVect = vectInt;
}

int main()
{
    std::ifstream file("./input.txt");
    std::string line;
    std::string data;
    const char delim = ',';

    while (std::getline(file, line))
    {
        data.append(line);
    }

    std::vector<std::string> vect;
    boost::split(vect, data, boost::is_any_of(","));

    std::vector<int> result;
    run(std::move(vect), result);

    std::cout << "Result: " << result.at(0) << std::endl;

    return 0;
}
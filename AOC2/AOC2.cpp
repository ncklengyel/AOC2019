#include <iostream>
#include <fstream>
#include <vector>
#include <boost/algorithm/string.hpp>

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

void run(const std::vector<int> &vect, std::vector<int> &outVect, int pNoun, int pVerb)
{
    outVect = vect;

    outVect.at(1) = pNoun;
    outVect.at(2) = pVerb;

    int currentIndex = 0;
    while (outVect.at(currentIndex) != CODE::STOP)
    {
        process(outVect.at(currentIndex), outVect.at(currentIndex + 1), outVect.at(currentIndex + 2), outVect.at(currentIndex + 3), outVect);
        currentIndex += 4;
    }
}

std::pair<int,int> run2(const std::vector<int>& vect, std::vector<int>& outVect, int pExpected)
{
    std::pair<int, int> result;

    for (int i = 0; i < 99; i++)
    {
        for (int j = 0; j < 99; j++)
        {
            std::vector<int> tempVect;
            run(vect, tempVect, i, j);

            if(tempVect.at(0) == pExpected)
            {
                outVect = tempVect;
                result.first = i;
                result.second = j;
                break;
            }
        }   
    }

    return result;
}

int main()
{
    std::ifstream file("./input.txt");
    std::string line;
    std::string data;

    while (std::getline(file, line))
    {
        data.append(line);
    }

    std::vector<std::string> vect;
    boost::split(vect, data, boost::is_any_of(","));

    std::vector<int> vectInt;
    for (auto num : vect)
    {
        vectInt.push_back(std::stoi(num));
    }

    std::vector<int> result;
    std::vector<int> result2;

    run(vectInt, result, 12, 2);
    auto nounVerb = run2(vectInt, result2, 19690720);

    std::cout << "Result1: " << result.at(0) << std::endl;
    
    int answer2 = 100 * nounVerb.first + nounVerb.second;

    std::cout << "Result2: noun= " << nounVerb.first << " verb= "<< nounVerb.second << " total= " << answer2 << std::endl;
    
    return 0;
}
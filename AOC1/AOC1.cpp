#include <iostream>
#include <math.h>
#include <fstream>

int calculateFuel(const int pMass)
{
    return std::floor(pMass / 3) - 2;
}

int calculateRequired(const int pMass)
{
    int currentFuel = pMass;
    int requiredFuel = 0;

    while (currentFuel > 0)
    {
        currentFuel = calculateFuel(currentFuel);
        if (currentFuel > 0)
        {
            requiredFuel += currentFuel;
        }
    }

    return requiredFuel;
}

int main()
{
    std::ifstream file("./input.txt");
    std::string line;

    int fuelSum = 0;
    int requiredFuelSum = 0;

    while (std::getline(file, line))
    {
        int lMass = std::stoi(line);
        int lFuel = calculateFuel(lMass);
        fuelSum += lFuel;
        requiredFuelSum += calculateRequired(lMass);
    }

    std::cout << "Fuel sum : " << fuelSum << std::endl;
    std::cout << "Required fuel sum : " << requiredFuelSum << std::endl;
    std::cout << "Total : " << fuelSum + requiredFuelSum << std::endl;

    return 0;
}
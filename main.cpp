#include "src/water_simulation.h"

int main()
{
    std::cout << "Enter the target water height (in meters from 0 to 9000): ";
    double targetWaterHeight = 0.0;

    std::cin >> targetWaterHeight;
    if (std::cin.fail())
    {
        std::cerr << "Invalid input";
        targetWaterHeight = 7500.0;
    }

    double resultWaterInputRate = water_simulation(targetWaterHeight);
    std::cout << "\n\n***********************************************" << std::endl;
    std::cout << "result is: " << resultWaterInputRate << " m^3/s" << std::endl;
}

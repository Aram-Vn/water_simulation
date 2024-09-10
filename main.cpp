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

    std::cout << "Enter the water input change per iteration: ";
    double waterInputChange = 0.0;

    std::cin >> waterInputChange;
    if (std::cin.fail())
    {
        std::cerr << "Invalid input";
        targetWaterHeight = 0.7;
    }

    double resultWaterInputRate = water_simulation(targetWaterHeight, waterInputChange);
    std::cout << "\n\n***********************************************" << std::endl;
    std::cout << "result is: " << resultWaterInputRate << " m^3/s" << std::endl;
}


#include "include/water_simulation.h"
#include <iostream>

int main()
{
    std::cout << "Enter the target water height (in meters from 0 to 900): ";
    double targetWaterHeight = 150.0;

    std::cin >> targetWaterHeight;
    if (std::cin.fail())
    {
        std::cerr << "Invalid input targetWaterHeight will be: " << targetWaterHeight;
        targetWaterHeight = 150.0;
    }

    double kp = 1.0;
    double ki = 0.1;
    double kd = 0.01;

    my::WaterSimulation* sim = my::WaterSimulation::getInstance(targetWaterHeight, kp, ki, kd);

    double finalRate = sim->runSimulation();

    std::cout << "final output rate: " << finalRate << std::endl;
}

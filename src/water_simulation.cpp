#include "water_simulation.h"

double water_simulation(const double inputTargetWaterHeight, const double waterInputChange)
{
    // Constants
    const double waterDensity        = 1000.0; // in kg/m^3
    const double gravityAcceleration = 9.81;   // in m/s^2
    const double maxPoolHeight       = 9000.0; // in meters
    const double outletArea          = 0.1;    // Cross-sectional area of the outlet in m^2
    const double initialWaterHeight  = 1000.0; // Initial water height
    const double timeStep            = 1.0;    // in seconds
    const double maxSimulationTime   = 2700.0; // in seconds
    const double heightTolerance     = 0.01;   // Tolerance for height stabilization
    const int    sleepInterval       = 100;    // Sleep every sleepInterval iterations

    double currentWaterHeight = initialWaterHeight;
    double simulationTime     = 0.0;
    double waterInputRate     = 0.7; // in m^3/s
    double waterOutputRate    = 0.0;
    int    iterationCount     = 0;

    double targetWaterHeight = inputTargetWaterHeight;

    // Check input
    if (targetWaterHeight < 0 || targetWaterHeight > maxPoolHeight)
    {
        std::cerr << "Invalid input. Using default target height of 7500 meters." << std::endl;
        targetWaterHeight = 7500.0;
    }

    std::cout << "targetWaterHeight: " << targetWaterHeight << std::endl;

    while (maxSimulationTime > simulationTime)
    {
        // Torricelli's law
        waterOutputRate = outletArea * std::sqrt(2 * gravityAcceleration * currentWaterHeight);

        // Adjust water input rate
        if (currentWaterHeight < targetWaterHeight)
        {
            waterInputRate += waterInputChange;
        }
        else if (currentWaterHeight > targetWaterHeight)
        {
            waterInputRate -= waterInputChange;
        }

        // prevent from negative
        if (waterInputRate < 0)
        {
            waterInputRate = 0;
        }

        currentWaterHeight += (waterInputRate - waterOutputRate) * timeStep;

        // Ensure the height does not exceed the max pool height or drop below zero
        if (currentWaterHeight > maxPoolHeight)
        {
            currentWaterHeight = maxPoolHeight;
        }

        if (currentWaterHeight < 0)
        {
            currentWaterHeight = 0;
        }

        std::cout << "Current time: " << simulationTime << " seconds, Water height: " << currentWaterHeight
                  << " meters, Water input rate: " << waterInputRate << " m^3/s" << std::endl;

        if (++iterationCount % sleepInterval == 0)
        {
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }

        // Check if the height has stabilized near the target height
        if (std::abs(currentWaterHeight - targetWaterHeight) < heightTolerance)
        {
            std::cout << "Stable water height achieved at: " << currentWaterHeight
                      << " meters with water input rate: " << waterInputRate << " m^3/s" << std::endl;
            break;
        }

        simulationTime += timeStep;
    }

    if (simulationTime >= maxSimulationTime)
    {
        std::cout << "Max simulation time reached. Final water height: " << currentWaterHeight
                  << " meters with water input rate: " << waterInputRate << " m^3/s" << std::endl;
        return waterInputRate;
    }

    std::cout << "Final required water input rate to maintain " << targetWaterHeight
              << " meters height: " << waterInputRate << " m^3/s" << std::endl;
    return waterInputRate;
}

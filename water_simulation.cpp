#include <chrono>
#include <cmath>
#include <iostream>
#include <thread>

int main()
{
    // Constants
    const double waterDensity        = 1000.0;   // in kg/m^3
    const double gravityAcceleration = 9.81;     // in m/s^2
    const double targetWaterHeight   = 7500.0;   // in meters
    const double maxPoolHeight       = 9000.0;   // in meters
    const double outletConstant      = 0.000001; // Outlet constant (adjusted for simulation)
    const double initialWaterHeight  = 1000.0;   // Initial water height
    const double timeStep            = 1.0;      // in seconds
    const double maxSimulationTime   = 25000.0;  // in seconds
    const double heightTolerance     = 0.01;     // Tolerance for height stabilization
    const int    sleepInterval       = 100;      // Sleep every sleepInterval iterations

    double currentWaterHeight = initialWaterHeight; // Start from a non-zero initial height
    double simulationTime     = 0.0;
    double waterInputRate     = 1.0; // in m^3/s
    double waterOutputRate    = 0.0;
    int    iterationCount     = 0;

    std::cout << "targetWaterHeight: " << targetWaterHeight << std::endl;

    while (maxSimulationTime > simulationTime)
    {
        // Calculate the water output rate based on the current height
        waterOutputRate = outletConstant * waterDensity * gravityAcceleration * currentWaterHeight;

        // Adjust water input rate to maintain the target height
        if (currentWaterHeight < targetWaterHeight)
        {
            waterInputRate += 1.0; // Increase input if height is below target
        }
        else if (currentWaterHeight > targetWaterHeight)
        {
            waterInputRate -= 1.0; // Decrease input if height is above target
        }

        // Ensure water input rate does not become negative
        if (waterInputRate < 0)
        {
            waterInputRate = 0;
        }

        // Update the current water height based on input and output rates
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
    }
    else
    {
        std::cout << "Final required water input rate to maintain 5000 meters height: " << waterInputRate << " m^3/s"
                  << std::endl;
    }

    return 0;
}

#include "../include/water_simulation.h"

#include <chrono>
#include <cmath>
#include <iostream>
#include <thread>

namespace my {
    WaterSimulation* WaterSimulation::instance = nullptr;

    WaterSimulation::WaterSimulation(double inputTargetWaterHeight)
        : m_currentWaterHeight(Constants::InitialWaterHeight),
          m_simulationTime(0.0),
          m_waterInputRate(0.7),
          m_waterOutputRate(0.0),
          m_targetWaterHeight(inputTargetWaterHeight),
          pid(1.0, 0.1, 0.01, 0.0, computeMaxInputRate())
    {
        if (m_targetWaterHeight < 0 || m_targetWaterHeight > Constants::MaxPoolHeight)
        {
            std::cerr << "Invalid input. Using default target height of 7500 meters." << std::endl;
            m_targetWaterHeight = 7500.0;
        }
    }

    WaterSimulation* WaterSimulation::getInstance(double inputTargetWaterHeight)
    {
        if (instance == nullptr)
        {
            instance = new WaterSimulation(inputTargetWaterHeight);
        }
        return instance;
    }

    void WaterSimulation::runSimulation()
    {
        std::cout << "m_targetWaterHeight: " << m_targetWaterHeight << std::endl;

        while (Constants::MaxSimulationTime > m_simulationTime)
        {
            m_waterOutputRate  = computeWaterOutputRate();
            m_waterInputRate = pid.compute(m_targetWaterHeight, m_currentWaterHeight, Constants::TimeStep);

            if (m_waterInputRate < 0)
            {
                m_waterInputRate = 0;
            }

            m_currentWaterHeight += (m_waterInputRate - m_waterOutputRate) * Constants::TimeStep;

            if (m_currentWaterHeight > Constants::MaxPoolHeight)
            {
                m_currentWaterHeight = Constants::MaxPoolHeight;
            }

            if (m_currentWaterHeight < 0)
            {
                m_currentWaterHeight = 0;
            }

            std::cout << "Current time: " << m_simulationTime << " seconds, Water height: " << m_currentWaterHeight
                      << " meters, Water input rate: " << m_waterInputRate << " m^3/s" << std::endl;

            std::this_thread::sleep_for(std::chrono::milliseconds(1));

            m_simulationTime += Constants::TimeStep;
        }

        std::cout << "Max simulation time reached. Final water height: " << m_currentWaterHeight
                  << " meters with water input rate: " << m_waterInputRate << " m^3/s" << std::endl;
    }

} // namespace my
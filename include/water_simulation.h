#ifndef WATER_SIMULATION_H
#define WATER_SIMULATION_H

#include "PIDController.h"
#include <chrono>
#include <cmath>
#include <iostream>
#include <thread>

namespace my {

    namespace Constants {
        inline constexpr double GravityAcceleration = 9.81;
        inline constexpr double MaxPoolHeight       = 900.0;
        inline constexpr double OutletArea          = 0.001;
        inline constexpr double InitialWaterHeight  = 100.0;
        inline constexpr double TimeStep            = 1.0;
        inline constexpr double MaxSimulationTime   = 9700.0;
    } // namespace Constants

    class WaterSimulation
    {
    private:
        WaterSimulation(double inputTargetWaterHeight, double inputKp, double inputKi, double inputKd);

    private:
        inline double computeMaxInputRate()
        {
            return (Constants::OutletArea * std::sqrt(2 * Constants::GravityAcceleration * Constants::MaxPoolHeight)) *
                   12.50;
        }

        inline double computeWaterOutputRate()
        {
            return Constants::OutletArea * std::sqrt(2 * Constants::GravityAcceleration * m_currentWaterHeight);
        }

        static WaterSimulation* instance;

    public:
        WaterSimulation(const WaterSimulation&)            = delete;
        WaterSimulation& operator=(const WaterSimulation&) = delete;

    public:
        static WaterSimulation* getInstance(double TargetWaterHeight, double inputKp = 1.0, double inputKi = 0.1,
                                            double inputKd = 0.01);
        double                  runSimulation();

    private:
        const double Kp_;
        const double Ki_;
        const double Kd_;

        double m_currentWaterHeight;
        double m_simulationTime;
        double m_waterInputRate;
        double m_waterOutputRate;
        double m_targetWaterHeight;

        my::PIDController pid;
    };
} // namespace my

#endif // WATER_SIMULATION_H

#include "../include/PIDController.h"

#include <algorithm>
#include <chrono>
#include <cmath>
#include <iostream>
#include <thread>

namespace my {
    PIDController::PIDController(double kp, double ki, double kd, double minInputRate, double maxInputRate)
        : m_kp{ kp },
          m_ki{ ki },
          m_kd{ kd },
          m_previousError{},
          m_integral{},
          m_minInputRate{ minInputRate },
          m_maxInputRate{ maxInputRate }

    {
    }

    double PIDController::compute(double setpoint, double measured, double dt)
    {
        double error = setpoint - measured;

        m_integral += error * dt * m_ki;

        m_integral = std::clamp(m_integral, m_minInputRate, m_maxInputRate);

        double derivative = (error - m_previousError) / dt;

        double output = error * m_kp + m_integral + derivative * m_kd;

        m_previousError = error;

        output = std::clamp(output, m_minInputRate, m_maxInputRate);

        return output;
    }
} // namespace my

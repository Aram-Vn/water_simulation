
#ifndef WATER_SIMULATION2_PIDCONTROLLER_H
#define WATER_SIMULATION2_PIDCONTROLLER_H

#include <algorithm>

namespace my {
    class PIDController
    {
    public:
        PIDController(double kp, double ki, double kd, double minInputRate, double maxInputRate);
        double compute(double input, double setpoint, double dt);

    private:
        double m_kp;
        double m_ki;
        double m_kd;

        double m_previousError;
        double m_integral;

        double m_minInputRate;
        double m_maxInputRate;
    };
} // namespace my

#endif // WATER_SIMULATION2_PIDCONTROLLER_H

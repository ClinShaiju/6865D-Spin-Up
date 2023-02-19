#pragma once

#include "flywheel/emaFilter.hpp"
#include "main.h"

class velPID {
    private:
        double m_kP = 0;
        double m_kd = 0;
        double m_kF = 0;
        double m_kI = 0;

        double m_Error = 0;
        double m_lastError = 0;;
        double m_derivative = 0;
        double m_integral = 0;

        emaFilter m_dFilter;

    public:
        velPID(double, double, double, double, double);
        double calculate(double, double);
        void setGains(double, double, double, double);
        double getError();
};

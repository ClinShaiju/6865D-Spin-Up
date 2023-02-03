#include "flywheelPID.hpp"
#include "main.h"
#include "math/utils.hpp"

velPID::velPID(double kP, double kD, double kF, double kI, double emaAlpha) 
: m_dFilter(emaAlpha) {
    m_kP = kP;
    m_kd = kD;
    m_kF = kF;
    m_kI = kI;
}

double velPID::calculate(double wantedRPM, double currentRPM) {
    m_Error = wantedRPM - currentRPM;

    m_derivative = (m_Error - m_lastError);
    m_lastError = m_Error;
    if(m_derivative < 0) m_derivative;
    m_derivative = m_dFilter.filter(m_derivative);

    if (std::abs(m_Error) < wantedRPM * .05) m_integral += m_Error;
    else m_integral = 0;
    if (m_integral > 12000) m_integral = 12000;

    double finalPower = (m_Error * m_kP) + (m_derivative * m_kd) + (wantedRPM * m_kF) + (m_integral * m_kI);

    if (std::abs(finalPower) > 12000) finalPower = squiggles::sgn(finalPower) * finalPower;

    return finalPower;
}

void velPID::setGains(double kP, double kD, double kF, double emaAlpha) {
    m_kP = kP;
    m_kd = kD;
    m_kF = kF;

    m_dFilter.setGains(emaAlpha);
}

double velPID::getError() {
    return m_Error;
}
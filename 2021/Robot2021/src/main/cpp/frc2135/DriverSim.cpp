#include "frc2135/DriverSim.h"

namespace frc2135
{
    DriverSim::DriverSim(volt_t kS, kv_t kV, ka_t kA)
    {
        m_kS = kS;
        m_kV = kV;
        m_kA = kA;

        m_Timer.Start();
    }

    DriverSim::~DriverSim() {}

    void DriverSim::Update(volt_t leftVoltage, volt_t rightVoltage)
    {
        // Get the elapsed time
        second_t elapsedTime = m_Timer.Get() * 1.0_s;

        // Use the motor model to calculate left and right accelerations
        feet_per_second_squared_t leftAcceleration =
            (leftVoltage - m_kS * sgn(m_currentVelocityLeft) - m_kV * m_currentVelocityLeft) / m_kA;
        feet_per_second_squared_t rightAcceleration =
            (rightVoltage - m_kS * sgn(m_currentVelocityRight) - m_kV * m_currentVelocityRight) / m_kA;

        // Use accelerations to calculate left and right velocities
        m_currentVelocityLeft = m_currentVelocityLeft + (leftAcceleration * elapsedTime);
        m_currentVelocityRight = m_currentVelocityRight + (rightAcceleration * elapsedTime);

        // Use velocities to calculate left and right displacements
        m_currentDisplacementLeft = m_currentDisplacementLeft + (m_currentVelocityLeft * elapsedTime);
        m_currentDisplacementRight = m_currentDisplacementRight + (m_currentVelocityRight * elapsedTime);

        // Reset the timer
        m_Timer.Reset();
    }

    foot_t DriverSim::getRightDisplacement()
    {
        return m_currentDisplacementRight;
    }

    foot_t DriverSim::getLeftDisplacement()
    {
        return m_currentDisplacementLeft;
    }

} // namespace frc2135

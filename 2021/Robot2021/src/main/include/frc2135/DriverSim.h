#pragma once

#include <units/acceleration.h>
#include <units/length.h>
#include <units/time.h>
#include <frc/Timer.h>
#include <units/velocity.h>
#include <units/voltage.h>

using namespace units;
using namespace units::acceleration;
using namespace units::length;
using namespace units::time;
using namespace units::velocity;
using namespace units::voltage;

// Create types for the units of kA and kV
using ka_t = unit_t<compound_unit<volts, inverse<feet_per_second_squared>>>;
using kv_t = unit_t<compound_unit<volts, inverse<feet_per_second>>>;


namespace frc2135
{

// TODO: add explanation for how signum function works
template<typename T>
int sgn(T val)
{
    return (T(0) < val) - (T(0) > val);
}

class DriverSim
{

private: 

    feet_per_second_t m_currentVelocityLeft;     // Velocity of the left side of the drivetrain
    feet_per_second_t m_currentVelocityRight;    // Velocity of the right side of the drivetrain
    foot_t m_currentDisplacementLeft;            // Acceleration of the left side of the drivetrain
    foot_t m_currentDisplacementRight;           // Acceleration of the right side of the drivetrain
    frc::Timer m_Timer;                          // Timer for the update function
    
    // TODO: describe these constants as well
    volt_t m_kS;                                 //
    kv_t m_kV;                                   // 
    ka_t m_kA;                                   //

public: 
    DriverSim(volt_t kS, kv_t kV, ka_t kA);
    ~DriverSim();

    void Update(volt_t leftVoltage, volt_t rightVoltage);
    foot_t getRightDisplacement();
    foot_t getLeftDisplacement();

};

}

/* TODO: add implementation of DriverSim class into Drivetrain

DriverSim sim(1, 1, 1);

in SimulationPeriodic
    left_voltage = m_motorL1.GetPercentOutput() * 12 volts;

    sim.Update(left_voltage, right_voltage);

*/
#include "frc2135/Math.h"

#include <chrono>
#include <ctre/Phoenix.h>
#include <frc/DriverStation.h>
#include <units/acceleration.h>
#include <units/velocity.h>
#include <units/voltage.h>

using namespace units;
using namespace units::acceleration;
using namespace units::velocity;
using namespace units::voltage;

namespace frc2135
{
    struct SimulationState
    {
        std::chrono::steady_clock::time_point last_update = std::chrono::steady_clock::now();
        unit_t<feet> displacement = 0_ft;
        unit_t<feet_per_second> velocity = 0_fps;
    };

    [[nodiscard]] constexpr auto make_simple_motor_model(
        const unit_t<volts> kS,
        const unit_t<compound_unit<volts, inverse<feet_per_second>>> kV,
        const unit_t<compound_unit<volts, inverse<feet_per_second_squared>>> kA)
    {
        return [=](unit_t<volts> voltage, const SimulationState state) -> SimulationState {
            auto now = std::chrono::steady_clock::now();
            auto period = std::chrono::duration<unit_t<seconds>>(now - state.last_update).count();
            auto acceleration = (voltage - kS * sgn(state.velocity) - kV * state.velocity) / kA;
            auto velocity = state.velocity + acceleration * period;
            return {
                std::chrono::steady_clock::now(),
                state.displacement + velocity * period,
                velocity,
            };
        };
    }

} // namespace frc2135
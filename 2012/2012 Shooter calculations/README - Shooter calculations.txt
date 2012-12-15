This LabView project is an analysis of Victor motor controllers and two different algorithms
that could be used to linearize their output response.

Victor motor controllers are known to have a non-linear response. More specifically, at low
input powerlevels, the PWM output to the motor (and the motor speed) increases more quickly than
a 1:1 relationship and then levels off with less than 1:1 for the remaining input power levels.
Empirical data from ChiefDelphi.com is built into the simulation.

Bellarmine Team 254 has created an inverse transform to linearize this response in an effort to
provide better low speed control and response for PID implementations. This transform is the
result of averaging a 7th and 5th order polynomial and results in a more linear response. The
Bellarmine transform was published in November 2011 with their code release on ChiefDelphi.com.

Also on ChiefDelphi.com is an analysis for a slightly simpler and more linear transform that
is the result of dividing a 4th and 2nd order polynomial. This transform has been implemented in
the Presentation 2012 Drive system to make the robot more responsive at low speeds.
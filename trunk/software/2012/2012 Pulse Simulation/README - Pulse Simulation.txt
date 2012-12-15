This LabView project is a simulation of a Pulse Timer VI which can run within Teleop.

This VI will monitor a boolean signal (like a button) and start a millisecond timer that
converts this event "edge" into a pulse of a specified duration. The VI does not block
and therefore must be called periodically such as in Teleop (driver station packets
cause this to occur) to keep checking the timeout value against the current time.
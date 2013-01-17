#ifndef JOYSTICKMAP_H
#define JOYSTICKMAP_H


/**
 * The RobotMap is a mapping from the ports sensors and actuators are wired into
 * to a variable name. This provides flexibility changing wiring, makes checking
 * the wiring easier and significantly reduces the number of magic numbers
 * floating around.
 */
 
// For example to map the left and right motors, you could define the
// following variables to use with your drivetrain subsystem.
// #define LEFTMOTOR 1
// #define RIGHTMOTOR 2

// If you are using multiple modules, make sure to define both the port
// number and the module. For example you with a rangefinder:
// #define RANGE_FINDER_PORT 1
// #define RANGE_FINDER_MODULE 1

//	Joystick definitions for USB ports
#define LA3_TRIGGER 			1
#define LA3_TOPBACK 			2
#define LA3_TOPFORWARD 			3
#define LA3_TOPLEFT 			4
#define LA3_TOPRIGHT 			5
#define LA3_BASEFORWARDLEFT 	6
#define LA3_BASEBACKLEFT 		7
#define LA3_BASEFRONTLEFT		8
#define LA3_BASEFRONTRIGHT		9
#define LA3_BASEBACKRIGHT 		10
#define LA3_BASEFORWARDRIGHT 	11
#define LA3_X_AXIS 				1
#define LA3_Y_AXIS 				2
#define LA3_THROTTLE_AXIS 		3

#define LX3D_TRIGGER 			1
#define LX3D_THUMB 				2
#define LX3D_TOPBACKLEFT 		3
#define LX3D_TOPBACKRIGHT 		4
#define LX3D_TOPFORWARDLEFT 	5
#define LX3D_TOPFORWARDRIGHT 	6
#define LX3D_BASEFORWARDLEFT 	7
#define LX3D_BASEFORWARDRIGHT 	8
#define LX3D_BASEMIDLEFT 		9
#define LX3D_BASEMIDRIGHT 		10
#define LX3D_BASEBACKLEFT 		11
#define LX3D_BASEBACKRIGHT 		12
#define LX3D_X_AXIS 			1
#define LX3D_Y_AXIS 			2
#define LX3D_THROTTLE_AXIS 		3

#endif

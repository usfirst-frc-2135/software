///////////////////////////////////////////////////////////////////////////////
//
//	RobotMap.h
//
//	Header file base for wiring diagram constants.
//
#ifndef ROBOTMAP_H
#define ROBOTMAP_H

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
#define DRIVER_JOYSTICK_PORT		1
#define OPERATOR_JOYSTICK_PORT		2

//	cRIO Analog Module NI 9201 Definitions

//	Analog Channels
#define ANALOG_UNUSED1				1
#define ANALOG_UNUSED2				2
#define ANALOG_UNUSED3				3
#define ANALOG_UNUSED4				4
#define ANALOG_UNUSED5				5
#define ANALOG_UNUSED6				6
#define ANALOG_UNUSED7				7
#define ANALOG_UNUSED8				8

//	cRIO Digital Module NI 9403 Definitions (Digital Side Car)

//	PWM Channels
#define PWM_LEFT_DRIVE_MOTOR		1
#define PWM_RIGHT_DRIVE_MOTOR		2
#define PWM_UNUSED3					3
#define PWM_UNUSED4					4
#define PWM_UNUSED5					5
#define PWM_SHOOTER_INTAKE_MOTOR	6
#define PWM_SHOOTER_EXIT_MOTOR		7
#define PWM_UNUSED8					8
#define PWM_UNUSED9					9
#define PWM_UNUSED10				10

//	Relay Channels
#define RELAY_UNUSED1				1
#define RELAY_UNUSED2				2
#define RELAY_UNUSED3				3
#define RELAY_UNUSED4				4
#define RELAY_UNUSED5				5
#define RELAY_UNUSED6				6
#define RELAY_UNUSED7				7
#define RELAY_UNUSED8				8

//	Digital I/O Channels
#define DIO_UNUSED1				1
#define DIO_UNUSED2				2
#define DIO_UNUSED3				3
#define DIO_UNUSED4				4
#define DIO_UNUSED5				5
#define DIO_UNUSED6				6
#define DIO_UNUSED7				7
#define DIO_UNUSED8				8
#define DIO_UNUSED9				9
#define DIO_UNUSED10			10
#define DIO_UNUSED11			11
#define DIO_UNUSED12			12
#define DIO_UNUSED13			13
#define DIO_UNUSED14			14

//	cRIO 24V Solenoid Module NI 9472 Definitions
#define SOLENOID_UNUSED1		1
#define SOLENOID_UNUSED2		2
#define SOLENOID_UNUSED3		3
#define SOLENOID_UNUSED4		4
#define SOLENOID_UNUSED5		5
#define SOLENOID_UNUSED6		6
#define SOLENOID_UNUSED7		7
#define SOLENOID_UNUSED8		8

#endif

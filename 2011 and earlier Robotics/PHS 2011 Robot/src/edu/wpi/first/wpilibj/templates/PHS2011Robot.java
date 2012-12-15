/*----------------------------------------------------------------------------*/
/* Copyright (c) FIRST 2008. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/
package edu.wpi.first.wpilibj.templates;

import edu.wpi.first.wpilibj.SimpleRobot;
import edu.wpi.first.wpilibj.RobotDrive;
import edu.wpi.first.wpilibj.Joystick;
import edu.wpi.first.wpilibj.Gyro;
import edu.wpi.first.wpilibj.Jaguar;
import edu.wpi.first.wpilibj.DigitalInput;
import edu.wpi.first.wpilibj.DriverStation;
import edu.wpi.first.wpilibj.Timer;

/**
 * The VM is configured to automatically run this class, and to call the
 * functions corresponding to each mode, as described in the SimpleRobot
 * documentation. If you change the name of this class or the package after
 * creating this project, you must also update the manifest file in the resource
 * directory.
 */
public class PHS2011Robot extends SimpleRobot {

    /**
     * This function is called once each time the robot enters autonomous mode.
     */
    RobotDrive drive; // robot drive base object
    Jaguar leftjag = new Jaguar(1);
    Jaguar rightjag = new Jaguar(2);
    private Joystick leftJoystick = new Joystick(1); // Joystick on USB1
    private Joystick rightJoystick = new Joystick(2); // Joystick on USB2
    DigitalInput left; // digital inputs for line tracking sensors
    DigitalInput middle;
    DigitalInput right;
    DriverStation ds; // driver station object for getting selections
    double defaultSteeringGain = 0.70; // default value for the steering gain
    Gyro gyro = new Gyro(1);
    LineTracker tracker = new LineTracker();
    //Arm arm = new Arm();
    Grabber grabber = new Grabber();

    public void autonomous() {

        tracker.run();
        //arm.set(arm.HIGH);
        grabber.out();
        // TODO - add code to turn robot around and move toward center of field
    }

    /**
     * This function is called once each time the robot enters operator control.
     */
    public void operatorControl() {
        double leftInput = 0.0;  // Left Joystick Y value
        double rightInput = 0.0; // Right Joystick Y value
        double throttle = 1.0;

        getWatchdog().setEnabled(true); // Watchdog control is active
        System.out.println("\nTele-operated Control ON\n");
        gyro.reset();
        // Main teleop operations loop
        while (isEnabled() && isOperatorControl()) {
            getWatchdog().feed(); // Keep watchdog alive
            System.out.println("Heading: " + gyro.getAngle() + "\n");
            // TANK DRIVE - Get both joystick Y Axis values and send data to
            // left/right speed controllers through RobotDrive object
            if (leftJoystick.getRawButton(5)) {
                throttle = -1.0;
            } else {
                throttle = -0.5;
            }
            leftInput = leftJoystick.getY();
            //rightInput = leftJoystick.getThrottle(); // Using Logitech Gamepad
            rightInput = leftJoystick.getX();
            //drive.tankDrive(leftInput * throttle, rightInput*throttle);
            drive.arcadeDrive(leftInput * throttle, rightInput);
            // NOTE: Tank Drive only uses Y Axis (forward/back)
            // Axis values range from 1.0 to -1.0
            Timer.delay(0.005);  // Wait 1/2 millisecond
        }

        // If we get here then robot is disabled or match is over
        drive.tankDrive(0.0, 0.0); // Full stop
        System.out.println("ROBOT SHUTDOWN\n");
        getWatchdog().setEnabled(false); // Watchdog control is off

    }
}

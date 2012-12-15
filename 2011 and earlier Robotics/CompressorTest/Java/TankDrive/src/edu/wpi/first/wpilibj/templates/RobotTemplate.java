/*----------------------------------------------------------------------------*/
/* Copyright (c) FIRST 2008. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/
package edu.wpi.first.wpilibj.templates;

import edu.wpi.first.wpilibj.SimpleRobot;
import edu.wpi.first.wpilibj.Jaguar;
import edu.wpi.first.wpilibj.RobotDrive;
import edu.wpi.first.wpilibj.Joystick;
import edu.wpi.first.wpilibj.Timer;

/**
 * The VM is configured to automatically run this class, and to call the
 * functions corresponding to each mode, as described in the SimpleRobot
 * documentation. If you change the name of this class or the package after
 * creating this project, you must also update the manifest file in the resource
 * directory.
 */
public class RobotTemplate extends SimpleRobot {
    /*
     * Class methods and fields
     */

    Jaguar leftjag = new Jaguar(2); // Left Jaguar on PWM channel 1
    Jaguar rightjag = new Jaguar(1); // Right Jaguar on PWM channel 2
    RobotDrive drive = new RobotDrive(leftjag, rightjag);
    Joystick leftJoystick = new Joystick(1); // Left joystick on USB1
    Joystick rightJoystick = new Joystick(2); // Right joystick on USB2

    /*
     * Class Constructor- called once when first instantiated
     */
    RobotTemplate() {
        System.out.println("ROBOT BOOT\n");
    }

    /**
     * This function is called once each time the robot enters autonomous mode.
     */
    public void autonomous() {
    }

    /**
     * This function is called once each time the robot enters operator control.
     */
    public void operatorControl() {
        double leftInput = 0.0;  // Left Joystick Y value
        double rightInput = 0.0; // Right Joystick Y value
        double throttle = 1.0; // Throttle value
        double oldInputs = 0.0; // Old sum of all inputs

        getWatchdog().setEnabled(true); // Watchdog control is active
        System.out.println("\nTele-operated Control ON\n");

        // Main teleop operations loop
        while (isEnabled() && isOperatorControl()) {
            getWatchdog().feed(); // Keep watchdog alive
            // TANK DRIVE - Get both joystick Y Axis values and send data to
            // left/right speed controllers through RobotDrive object
            leftInput = leftJoystick.getY();
            //rightInput = rightJoystick.getY()*-1.0;
            rightInput = leftJoystick.getThrottle();
            throttle = rightJoystick.getThrottle();
            if ((rightInput + leftInput + throttle ) != oldInputs) {
            System.out.println("INPUT " + leftInput + " : " + rightInput + " : " +
                    throttle + "\n");
            }
            oldInputs = rightInput + leftInput + throttle;
            drive.tankDrive(leftInput, rightInput);
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

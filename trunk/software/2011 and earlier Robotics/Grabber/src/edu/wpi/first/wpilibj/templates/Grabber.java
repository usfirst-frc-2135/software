/*----------------------------------------------------------------------------*/
/* Copyright (c) FIRST 2008. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/
package edu.wpi.first.wpilibj.templates;

import edu.wpi.first.wpilibj.SimpleRobot;
import edu.wpi.first.wpilibj.Victor;
import edu.wpi.first.wpilibj.Joystick;
import edu.wpi.first.wpilibj.Timer;

/**
 * The VM is configured to automatically run this class, and to call the
 * functions corresponding to each mode, as described in the SimpleRobot
 * documentation. If you change the name of this class or the package after
 * creating this project, you must also update the manifest file in the resource
 * directory.
 */
public class Grabber extends SimpleRobot {

    /**
     * This function is called once each time the robot enters autonomous mode.
     */
    Joystick bob = new Joystick(1);
    Victor top = new Victor(3);
    Victor bottom = new Victor(4);

    public void RobotTemplate() {
    }

    public void autonomous() {
    }

    /**
     * This function is called once each time the robot enters operator control.
     */
    public void operatorControl() {
        Timer grabtime = new Timer();
        getWatchdog().setEnabled(true); // Watchdog control is active
        System.out.println("\nTele-operated Control ON\n");

        // Main teleop operations loop
        while (isEnabled() && isOperatorControl()) {
            getWatchdog().feed(); // Keep watchdog alive
            if (bob.getRawButton(1)) {
                top.set(-1.0);
                bottom.set(1.0);
                grabtime.reset();
                grabtime.start();
            }
            if (bob.getRawButton(2)) {
                top.set(1.0);
                bottom.set(1.0);
                 grabtime.reset();
                grabtime.start();
            }
            if (bob.getRawButton(3)) {
                top.set(1.0);
                bottom.set(-1.0);
                 grabtime.reset();
                grabtime.start();
            }
            if (grabtime.get() > 1.0) { // Stop after 1 second runtime
                top.set(0.0);
                bottom.set(0.0);
                grabtime.stop();
                grabtime.reset();
            }
            Timer.delay(0.005);  // Wait 1/2 millisecond

        }

    }
}

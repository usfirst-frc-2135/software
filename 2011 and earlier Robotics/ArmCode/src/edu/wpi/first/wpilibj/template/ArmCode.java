/*----------------------------------------------------------------------------*/
/* Copyright (c) FIRST 2008. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/
package edu.wpi.first.wpilibj.template;

import edu.wpi.first.wpilibj.SimpleRobot;
import edu.wpi.first.wpilibj.Victor;
import edu.wpi.first.wpilibj.Joystick;
import edu.wpi.first.wpilibj.Timer;
import edu.wpi.first.wpilibj.DigitalInput;
import edu.wpi.first.wpilibj.PIDController;
import edu.wpi.first.wpilibj.Encoder;

/**
 * The VM is configured to automatically run this class, and to call the
 * functions corresponding to each mode, as described in the SimpleRobot
 * documentation. If you change the name of this class or the package after
 * creating this project, you must also update the manifest file in the resource
 * directory.
 */
public class ArmCode extends SimpleRobot {

    /**
     * This function is called once each time the robot enters autonomous mode.
     */
    Joystick bob = new Joystick(1);
    Victor rotate = new Victor(5);
    Victor extend = new Victor(6);
    DigitalInput min = new DigitalInput(12);
    DigitalInput max = new DigitalInput(13);
    DigitalInput out = new DigitalInput(11);
    DigitalInput in = new DigitalInput(10);
    Encoder arm = new Encoder(8,9);
    PIDController pid;

    public void RobotTemplate() {
    }

    public void autonomous() {
    }

    /**
     * This function is called once each time the robot enters operator control.
     */
    public void operatorControl() {

        getWatchdog().setEnabled(true); // Watchdog control is active
        System.out.println("\nTele-operated Control ON\n");
        pid = new PIDController(0.0,0.0,0.0,arm,extend);
        pid.enable();
        // Main teleop operations loop
        while (isEnabled() && isOperatorControl()) {
            getWatchdog().feed(); // Keep watchdog alive
            if (bob.getRawButton(6)) {
                if (!max.get()) {
                    rotate.set(0.75);
                } else {
                    rotate.set(0.0);
                }
            }
            if (bob.getRawButton(8)) {
                if (!min.get()) {
                    rotate.set(-0.75);
                } else {
                    rotate.set(0.0);
                }
            }
            if (bob.getRawButton(1)) {
                if (!out.get()) {
                    extend.set(0.75);
                } else {
                    extend.set(0.0);
                }
            }
            if (bob.getRawButton(2)) {
                if (!in.get()) {
                    extend.set(-0.75);
                } else {
                    extend.set(0.0);
                }
            }

            Timer.delay(0.005);  // Wait 1/2 millisecond


        }
    }
}

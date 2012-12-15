/*----------------------------------------------------------------------------*/
/* Copyright (c) FIRST 2008. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/
package edu.wpi.first.wpilibj.templates;

import edu.wpi.first.wpilibj.SimpleRobot;
import edu.wpi.first.wpilibj.Compressor;
import edu.wpi.first.wpilibj.Joystick;
import edu.wpi.first.wpilibj.Solenoid;
import edu.wpi.first.wpilibj.Timer;

/**
 * The VM is configured to automatically run this class, and to call the
 * functions corresponding to each mode, as described in the SimpleRobot
 * documentation. If you change the name of this class or the package after
 * creating this project, you must also update the manifest file in the resource
 * directory.
 */
public class RobotTemplate extends SimpleRobot {

    /**
     * This function is called once each time the robot enters autonomous mode.
     */
    Compressor thad = new Compressor(14, 1);
    Joystick bob = new Joystick(1);
    Solenoid out = new Solenoid(1);
    Solenoid in = new Solenoid(2);

    public void RobotTemplate() {
        thad.start();
    }

    public void autonomous() {
    }

    /**
     * This function is called once each time the robot enters operator control.
     */
    public void operatorControl() {
        boolean high = false;
        boolean low = true;
        boolean shift = false;
        boolean shiftbutton = false;

        Timer shifttimer = new Timer();
        shifttimer.start();
        shifttimer.reset();

        thad.start();
        getWatchdog().setEnabled(true); // Watchdog control is active
        System.out.println("\nTele-operated Control ON\n");

        // Main teleop operations loop
        while (isEnabled() && isOperatorControl()) {
            getWatchdog().feed(); // Keep watchdog alive

            // When the button is pressed the piston change state
            // Only read the button after 1000 milliseconds (i.e. 1 second)
            // since startup or since the last time the state was changed
            // to prevent shifting faster than the piston can respond
            shift = bob.getRawButton(2);
            if (shifttimer.get() > 1.0) {
                shiftbutton = shift;

            } 
            if (shiftbutton && high == true) {
                System.out.println("Down shift\n");
                high = false;
                low = true;
                shifttimer.reset(); // Reset timer to 0 to begin next shift wait
            } else {
                if (shiftbutton && low == true) {
                    System.out.println("Up shift\n");
                    low = false;
                    high = true;
                    shifttimer.reset(); // Reset timer to 0 to begin next shift wait
                }

            }
            shiftbutton = false; // Force button to false to stop multi-shift
            out.set(low);
            in.set(high);
            Timer.delay(0.005);  // Wait 1/2 millisecond

        }
        thad.stop();
    }
}

/*----------------------------------------------------------------------------*/
/* Copyright (c) FIRST 2008. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/
package edu.wpi.first.wpilibj.templates;

import edu.wpi.first.wpilibj.SimpleRobot;
import edu.wpi.first.wpilibj.Joystick;
import edu.wpi.first.wpilibj.Servo;
import edu.wpi.first.wpilibj.Timer;

/**
 * The VM is configured to automatically run this class, and to call the
 * functions corresponding to each mode, as described in the SimpleRobot
 * documentation. If you change the name of this class or the package after
 * creating this project, you must also update the manifest file in the resource
 * directory.
 */
public class CameraRotate extends SimpleRobot {

    Joystick bob = new Joystick(1);
    Servo camera = new Servo(5);

    /**
     * This function is called once each time the robot enters autonomous mode.
     */
    public void autonomous() {
    }

    /**
     * This function is called once each time the robot enters operator control.
     */
   public void operatorControl() {
        double camerangle = 0.0;
        Timer servoTimer = new Timer();
        getWatchdog().setEnabled(true); // Watchdog control is active
        System.out.println("\nTele-operated Control ON\n");

        servoTimer.start();
        // Main teleop operations loop
        while (isEnabled() && isOperatorControl()) {
            getWatchdog().feed(); // Keep watchdog alive

            if (bob.getRawButton(10) && (servoTimer.get() > 1.0)) {
                camerangle = camera.getAngle();
               System.out.println("Camera angle: "+camerangle);
               if (camerangle == 0.0) {
                   camera.setAngle(180.0);
               } else {
                   camera.setAngle(0.0);
               }
               servoTimer.reset();
            }

            Timer.delay(0.005);  // Wait 1/2 millisecond

        }

    }
}


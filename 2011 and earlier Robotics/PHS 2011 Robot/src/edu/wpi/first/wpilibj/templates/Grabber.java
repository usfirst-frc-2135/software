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
import edu.wpi.first.wpilibj.DigitalInput;

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
    Timer grabtime = new Timer();
    DigitalInput grabberlimitswitch = new DigitalInput(4);

    public void out() {
        grabtime.reset();
        grabtime.start();
        while (grabtime.get() < 1.0) {
            top.set(1.0);
            bottom.set(-1.0);
        }
        stop();
    }

    public void in() {
        grabtime.reset();
        grabtime.start();
        boolean gotpiece = false;

        while ((grabtime.get() < 1.0) && (!gotpiece)) {
            gotpiece = grabberlimitswitch.get();
            top.set(-1.0);
            bottom.set(1.0);
        }
        stop();
    }

    public void stop() {
        top.set(0.0);
        bottom.set(0.0);
    }
}


/*----------------------------------------------------------------------------*/
/* Copyright (c) FIRST 2008. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/
package edu.wpi.first.wpilibj.templates;

import edu.wpi.first.wpilibj.SimpleRobot;
import edu.wpi.first.wpilibj.DigitalModule;
import edu.wpi.first.wpilibj.DigitalInput;
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
    public void autonomous() {
    }

    /**
     * This function is called once each time the robot enters operator control.
     */
    public void operatorControl() {
        getWatchdog().setEnabled(false);
        double timeStart = 0.0;
        double timeEnd = 0.0;
        double timeDelta = 0.0;
        double avgPulseTime = 0.0;
        int pulseCounter = 0;
        double positionDegree = 0.0;
        Timer tim1 = new Timer();
        DigitalModule dm = DigitalModule.getInstance(4);

	dm.allocateDIO(1, true);
        System.out.println("Robot Start\n");
        while (isOperatorControl()) {
            if (dm.getDIO(1) == true) {
                System.out.println("Got signal\n");
                //start the timer and get the time
                tim1.start();
                timeStart = tim1.get();

                while (dm.getDIO(1) == true) //repeat until there is a falling edge
                {
                    Timer.delay(.000001);  //Pause for 1usec
                }
                System.out.println("Lost signal\n");
                timeEnd = tim1.get();
                tim1.stop(); //stop the timer
                timeDelta = timeEnd - timeStart;
                if ((0 < timeDelta) && (timeDelta < .000578)) //filter out noise
                {
                    avgPulseTime += (timeEnd - timeStart); //sum up all of the pulses
                    pulseCounter++;
                }
            }
            //looking to average 10 pulses together
            if (pulseCounter == 10) {
                avgPulseTime /= pulseCounter;
                avgPulseTime *= 1000000;
                positionDegree = avgPulseTime * 360 / 578;
                pulseCounter = 0;
                //display on the screen
                System.out.println("Degree: "+positionDegree+"\n");
                tim1.reset();
                avgPulseTime = 0.0;
            }
            Timer.delay(.0000005);
        }
    }
}

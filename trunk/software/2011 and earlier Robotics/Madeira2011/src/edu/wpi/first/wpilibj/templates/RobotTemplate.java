
/*----------------------------------------------------------------------------*/
/* Copyright (c) FIRST 2008. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/
package edu.wpi.first.wpilibj.templates;

import edu.wpi.first.wpilibj.AnalogModule;
import edu.wpi.first.wpilibj.Dashboard;
import edu.wpi.first.wpilibj.DigitalModule;
import edu.wpi.first.wpilibj.DigitalInput;
import edu.wpi.first.wpilibj.DriverStation;
import edu.wpi.first.wpilibj.RobotDrive;
import edu.wpi.first.wpilibj.SimpleRobot;
import edu.wpi.first.wpilibj.Timer;
import edu.wpi.first.wpilibj.Jaguar;
import edu.wpi.first.wpilibj.Joystick;
import edu.wpi.first.wpilibj.Gyro;
import edu.wpi.first.wpilibj.Ultrasonic;
import edu.wpi.first.wpilibj.Compressor;
import edu.wpi.first.wpilibj.Solenoid;
import edu.wpi.first.wpilibj.Victor;
import edu.wpi.first.wpilibj.PIDController;
import edu.wpi.first.wpilibj.PIDOutput;
import edu.wpi.first.wpilibj.Encoder;
import edu.wpi.first.wpilibj.camera.AxisCamera;
import edu.wpi.first.wpilibj.camera.AxisCameraException;
import edu.wpi.first.wpilibj.image.ColorImage;
import edu.wpi.first.wpilibj.image.NIVisionException;
import edu.wpi.first.wpilibj.Relay;

/**
 * Sample line tracking class for FIRST 2011 Competition
 * Jumpers on driver station digital I/O pins select the operating mode:
 * The Driver Station digital input 1 is used to pick the straight
 * line or the forked line. Driver station digital input 2 selects whether the
 * code takes the left or right fork. You can set these inputs using jumpers on
 * the USB I/O module or in the driver station I/O Configuration pane (if there
 * is no Digital I/O module installed.
 *
 * Since there is the fork to contend with, the code tracks the edge of the line
 * using a technique similar to that used with a single-sensor Lego robot.
 *
 * This code worked on a simple bot built from the 2011 kit chassis and weighted
 * to behave similarly to complete robot complete with scoring mechanisms. Your
 * own robot will likely be geared differently, the CG will be different, the
 * wheels may be different - so expect to tune the program for your own robot
 * configuration. The two places to do tuning are:
 *
 * defaultSteeringGain - this is the amount of turning correction applied
 * forkProfile & straightProfile - these are power profiles applied at various
 * times (one power setting / second of travel) as the robot moves towards
 * the wall.
 *
 * In addition: this program uses dead reckoning - that is it drives at various
 * power settings so it will slow down and stop at the end of the line. This is
 * highly dependent on robot weight, wheel choice, and battery voltage. It will
 * behave differently on a fully charged vs. partially charged battery.
 *
 * To overcome these limitations, you should investigate the use of feedback to
 * have power/wheel independent control of the program. Examples of feedback
 * include using wheel encoders to measure the distance traveled or some kind of
 * rangefinder to determine the distance to the wall. With these sensors
 * your program can know precisely how far from the wall it is, and set speed
 * accordingly.
 *
 */
public class RobotTemplate extends SimpleRobot {

    RobotDrive drive; // robot drive base object
    Jaguar leftjag = new Jaguar(1);
    Jaguar rightjag = new Jaguar(2);
    Relay spike1 = new Relay(2);
    Relay spike2 = new Relay(3);
    private Joystick driveJoystick = new Joystick(1); // Joystick on USB1
    private Joystick armJoystick = new Joystick(2); // Joystick on USB2
    DigitalInput left; // digital inputs for line tracking sensors
    DigitalInput middle;
    DigitalInput right;
    DriverStation ds; // driver station object for getting selections
    double defaultSteeringGain = 0.70; // default value for the steering gain
    Gyro gyro = new Gyro(1); // Gyro rate compass returns heading
    Ultrasonic sonar = new Ultrasonic(4, 5); // Measures distance from front
    Compressor comp = new Compressor(14, 1);
    Solenoid upshifter = new Solenoid(1);
    Solenoid downshifter = new Solenoid(2);
    Solenoid mouthopen = new Solenoid(7);
    Solenoid mouthclose = new Solenoid(8);
    Solenoid deploy = new Solenoid(6);
    Victor shoulderMotor = new Victor(5); // Shoulder pivot
    Victor armMotor = new Victor(6); // Arm extension
    Victor gripMotor = new Victor(7); //Gripper control
    DigitalInput minShouldersafe = new DigitalInput(13); // lower pivot limit
    DigitalInput maxShouldersafe = new DigitalInput(12); // upper pivot limit
    DigitalInput minArmsafe = new DigitalInput(10); // lower arm limit switch
    DigitalInput maxArmsafe = new DigitalInput(11); // upper arm limit switch
    Encoder shoulderEncoder = new Encoder(6, 7); // Encoder to measure arm extension
    Encoder armEncoder = new Encoder(8, 9);
    PIDController arm; // Shoulder automatic control
    PIDController shoulder;

    public RobotTemplate() {
        // Create robot drive with two speed controllers (left and right)
        drive = new RobotDrive(leftjag, rightjag);

        // set the MotorSafety expiration timer
        getWatchdog().setEnabled(false); // Watchdog control is off

        // create the digital input objects to read from the sensors
        left = new DigitalInput(1);
        middle = new DigitalInput(2);
        right = new DigitalInput(3);

        // Set encoder parameters
        armEncoder.setDistancePerPulse(0.010); // Each pulse is 0.01 inch
        armEncoder.setReverseDirection(true);

        // get the driver station instance to read the digital I/O pins
        ds = DriverStation.getInstance();

        // Start Compressor
        comp.start();
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
        // supply your own teleop code here
        double leftInput = 0.0;  // Left Joystick Y value
        double rightInput = 0.0; // Right Joystick Y value
        double throttle = 1.0;
        double armSetPoint = 0.0;
        int counter = 0;
        boolean armState;
        boolean open = false;
        boolean closed = true;
        boolean gripbutton = false;
        double shoulderMotorDelta;
        double armMotorDelta;
        gripMotor.set(0.0); // Make sure gripper is off
        Timer gripTimer = new Timer();


        //ColorImage image = null;
        gripTimer.start();

        // armEncoder.setPIDSourceParameter(Encoder.PIDSourceParameter.kDistance);

        //getWatchdog().feed(); // Keep watchdog alive
        System.out.println("\nTele-operated Control ON\n");
        //gyro.reset();
        // sonar.setEnabled(true);
        //sonar.setAutomaticMode(true);
        // armEncoder.start();
        //armEncoder.reset();
        if (!comp.enabled()) {
            comp.start();
        }
        getWatchdog().setEnabled(true); // Watchdog control is active
        // Main teleop operations loop
        while (isEnabled() && isOperatorControl()) {
            getWatchdog().feed(); // Keep watchdog alive

            // Gripper


            gripbutton = armJoystick.getRawButton(1);


            if (gripbutton) {
                System.out.println("Gripper open\n");
                closed = false;
                open = true;
                //gripTimer.reset(); // Reset timer to 0 to begin next shift wait
                mouthopen.set(true);
                mouthclose.set(false);
            } else {
                mouthclose.set(true);
                mouthopen.set(false);
            }


            // End Gripper

            // Shoulder
            shoulderMotor.set(0.0); // Stop pivot from moving
            shoulderMotorDelta = armJoystick.getY();
            if (shoulderMotorDelta < -0.15) {
                System.out.println("Shoulder moving up\n");
                if (maxShouldersafe.get()) {
                    shoulderMotor.set(-1 * shoulderMotorDelta);
                } else {
                    shoulderMotor.set(-1 * shoulderMotorDelta);
                    System.out.println("Maxshoulder failsafe\n");
                }

            }
            if (shoulderMotorDelta > 0.15) {
                System.out.println("Shoulder moving down\n");
                if (minShouldersafe.get()) {
                    shoulderMotor.set(1 * shoulderMotorDelta);
                } else {
                    shoulderMotor.set(1 * shoulderMotorDelta);
                    System.out.println("Minshoulder failsafe\n");
                }
            }

            // Arm
            armMotor.set(0.0); // Stop arm from moving
            armMotorDelta = armJoystick.getX();
            if (armMotorDelta < -0.15) {
                System.out.println("Arm moving out\n");
                if (maxArmsafe.get()) {
                    armMotor.set(-1 * armMotorDelta);
                } else {
                    armMotor.set(-1 * armMotorDelta);
                    System.out.println("Maxarm failsafe\n");
                }

            }
            if (armMotorDelta > 0.15) {
                System.out.println("Arm moving in\n");
                if (minArmsafe.get()) {
                    armMotor.set(1 * armMotorDelta);
                } else {
                    armMotor.set(1 * armMotorDelta);
                    System.out.println("Minarm failsafe\n");
                }
            }

            // Old arm code
            /*
            armMotor.set(0.0); // Stop arm from moving
            armMotorDelta = 0.0;
            if (armJoystick.getRawButton(3)) {
            armMotorDelta = -0.75
            System.out.println("Arm moving in\n");
            }
            if (armJoystick.getRawButton(2)) {
            armMotorDelta = 0.75;
            System.out.println("Arm moving out\n");
            }
            if (armMotorDelta < -0.15) {
            if (maxArmsafe.get()) {
            armMotor.set(armMotorDelta);
            } else {
            System.out.println("Maxarm failsafe\n");
            }

            }
            if (armMotorDelta > 0.15) {
            if (minArmsafe.get()) {
            armMotor.set(armMotorDelta);
            } else {
            System.out.println("Minarm failsafe\n");
            }
            }
             */

            // Minibot deploy
            if (driveJoystick.getRawButton(2)) {
                System.out.println("Minibot deployed\n");
                deploy.set(true);
            } else {
                deploy.set(false);
            }

            // Gripper Code
            gripMotor.set(0.0);
            if (armJoystick.getRawButton(3)) {
                // Pull piece in
                gripMotor.set(1.0);
                System.out.println("Piece in\n)");

            } 
            if (armJoystick.getRawButton(2)) {
                // Push piece out
                gripMotor.set(-1.0);
                System.out.println("Piece out\n");

            }





            // Drive
            leftInput = driveJoystick.getY() * -1.0;
            //rightInput = leftJoystick.getThrottle(); // Using Logitech Gamepad
            rightInput = driveJoystick.getX() * -1.0;

            //drive.tankDrive(leftInput * throttle, rightInput*throttle);
            //System.out.println("Joystick: "+leftInput+" "+rightInput);
            // NOTE: arcade Drive uses only one joystick
            drive.arcadeDrive(leftInput, rightInput);
            // NOTE: Tank Drive only uses Y Axis (forward/back)
            // Axis values range from 1.0 to -1.0
            //drive.tankDrive(leftInput, rightInput);
            updateDashboard(); // Send current status to dashboard
            Timer.delay(0.005);  // Wait 1/2 millisecond
        }

        // If we get here then robot is disabled or match is over
        drive.tankDrive(0.0, 0.0); // Full stop
        comp.stop();

        System.out.println(
                "ROBOT SHUTDOWN\n");
        getWatchdog().setEnabled(false); // Watchdog control is off
    }

    void updateDashboard() {
        Dashboard lowDashData = DriverStation.getInstance().getDashboardPackerLow();
        lowDashData.addCluster();




        {
            lowDashData.addCluster();




            { //analog modules
                lowDashData.addCluster();




                {
                    for (int i = 1; i <= 8; i++) {
                        lowDashData.addFloat((float) AnalogModule.getInstance(1).getAverageVoltage(i));




                    }
                }
                lowDashData.finalizeCluster();
                lowDashData.addCluster();




                {
                    for (int i = 1; i <= 8; i++) {
                        lowDashData.addFloat((float) AnalogModule.getInstance(2).getAverageVoltage(i));




                    }
                }
                lowDashData.finalizeCluster();




            }
            lowDashData.finalizeCluster();

            lowDashData.addCluster();




            { //digital modules
                lowDashData.addCluster();




                {
                    lowDashData.addCluster();




                    {
                        int module = 4;
                        lowDashData.addByte(DigitalModule.getInstance(module).getRelayForward());
                        lowDashData.addByte(DigitalModule.getInstance(module).getRelayForward());
                        lowDashData.addShort(DigitalModule.getInstance(module).getAllDIO());
                        lowDashData.addShort(DigitalModule.getInstance(module).getDIODirection());
                        lowDashData.addCluster();




                        {
                            for (int i = 1; i <= 10; i++) {
                                lowDashData.addByte((byte) DigitalModule.getInstance(module).getPWM(i));




                            }
                        }
                        lowDashData.finalizeCluster();




                    }
                    lowDashData.finalizeCluster();




                }
                lowDashData.finalizeCluster();

                lowDashData.addCluster();




                {
                    lowDashData.addCluster();




                    {
                        int module = 6;
                        lowDashData.addByte(DigitalModule.getInstance(module).getRelayForward());
                        lowDashData.addByte(DigitalModule.getInstance(module).getRelayReverse());
                        lowDashData.addShort(DigitalModule.getInstance(module).getAllDIO());
                        lowDashData.addShort(DigitalModule.getInstance(module).getDIODirection());
                        lowDashData.addCluster();




                        {
                            for (int i = 1; i <= 10; i++) {
                                lowDashData.addByte((byte) DigitalModule.getInstance(module).getPWM(i));




                            }
                        }
                        lowDashData.finalizeCluster();




                    }
                    lowDashData.finalizeCluster();




                }
                lowDashData.finalizeCluster();






            }
            lowDashData.finalizeCluster();

            lowDashData.addByte(Solenoid.getAllFromDefaultModule());




        }
        lowDashData.finalizeCluster();
        lowDashData.commit();



    }
}

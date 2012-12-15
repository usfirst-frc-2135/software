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
    private Joystick leftJoystick = new Joystick(1); // Joystick on USB1
    //private Joystick rightJoystick = new Joystick(2); // Joystick on USB2
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
    Victor shoulderMotor = new Victor(5); // Shoulder pivot
    Victor armMotor = new Victor(6); // Arm extension
    DigitalInput minShouldersafe = new DigitalInput(13); // lower pivot limit 
    DigitalInput maxShouldersafe = new DigitalInput(12); // upper pivot limit 
    DigitalInput minArmsafe = new DigitalInput(10); // lower arm limit switch
    DigitalInput maxArmsafe = new DigitalInput(11); // upper arm limit switch
    Encoder armEncoder = new Encoder(6, 7); // Encoder to measure arm extension
    PIDController arm; // Shoulder automatic control

    public RobotTemplate() {
        // create the robot drive and correct for the wheel direction. Our robot
        // was geared such that the motor speeds needed to be inverted for
        // positive speeds to go forward. You may not need these.
        //drive = new RobotDrive(1, 2);
        //drive.setInvertedMotor(RobotDrive.MotorType.kRearLeft, true);
        //drive.setInvertedMotor(RobotDrive.MotorType.kFrontLeft, true);
        //drive.setInvertedMotor(RobotDrive.MotorType.kFrontRight, true);
        //drive.setInvertedMotor(RobotDrive.MotorType.kRearRight, true);
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

        int binaryValue; // a single binary value of the three line tracking
        // sensors
        int previousValue = 0; // the binary value from the previous loop
        double steeringGain; // the amount of steering correction to apply

        // the power profiles for the straight and forked robot path. They are
        // different to let the robot drive more slowly as the robot approaches
        // the fork on the forked line case.


        double forkProfile[] = {0.55, 0.55, 0.55, 0.55, 0.55, 0.55, 0.55, 0.5};
        double straightProfile[] = {0.2, 0.2, 0.1, 0.1, 0.1, 0.1, 0.1, 0.0};

        double powerProfile[];   // the selected power profile

        // set the straightLine and left-right variables depending on path
        boolean straightLine = !ds.getDigitalIn(1);
        powerProfile = (straightLine) ? straightProfile : forkProfile;
        //double stopTime = (straightLine) ? 2.0 : 4.0; // Time to reach end
        double stopTime = 1.0;
        //boolean goLeft = !ds.getDigitalIn(2) && !straightLine;
        boolean goLeft = !straightLine;
        System.out.println("StraightLine: " + straightLine);
        System.out.println("GoingLeft: " + goLeft);


        boolean atCross = false; // if robot has arrived at end

        // time the path over the line
        Timer timer = new Timer();
        timer.start();
        timer.reset();

        //int oldTimeInSeconds = -1;
        double time;
        double speed, turn;

        gyro.reset();
        sonar.setEnabled(true);
        sonar.setAutomaticMode(true);
        getWatchdog().setEnabled(true); // Watchdog control is active
        // loop until robot reaches "T" at end or 8 seconds has past
        while ((time = timer.get()) < 8.0 && !atCross) {
            getWatchdog().feed(); // Keep watchdog alive
            int timeInSeconds = (int) time;
            // read the sensors
            int leftValue = left.get() ? 1 : 0;
            int middleValue = middle.get() ? 1 : 0;
            int rightValue = right.get() ? 1 : 0;
            // compute the single value from the 3 sensors. Notice that the bits
            // for the outside sensors are flipped depending on left or right
            // fork. Sign of the steering direction is different for left/right.
            if (goLeft) {
                binaryValue = leftValue * 4 + middleValue * 2 + rightValue;
                steeringGain = -defaultSteeringGain;
            } else {
                binaryValue = rightValue * 4 + middleValue * 2 + leftValue;
                steeringGain = defaultSteeringGain;
            }

            // get the default speed and turn rate at this time
            speed = powerProfile[timeInSeconds];
            turn = 0;

            // different cases for different line tracking sensor readings
            switch (binaryValue) {
                case 1:  // drifting right
                    turn = -steeringGain; // turn left
                    break;
                case 2: // on line
                    turn = 0;
                    break;
                case 4: // drifting left
                    turn = steeringGain; // turn right
                    break;
                case 5: // Reached branch
                    turn = steeringGain;
                    break;
                case 7:  // all sensors on (maybe at cross)
                    if (time > stopTime) {
                        atCross = true;
                        speed = 0; // At end, stop
                    } else {
                        // TODO: Turn towards wall
                    }
                    break;
                case 0:  // all sensors off - search for line
                    if (previousValue == 0 || previousValue == 1) {
                        turn = -steeringGain; // Line last seen on right
                    } else {
                        turn = steeringGain; // Line last seen on left or center
                    }
                    break;
                default:  // all other cases
                    turn = -steeringGain;
            }
            // print current status for debugging
            if (binaryValue != previousValue) {
                System.out.println("Time: " + time + " Sensor: " + binaryValue
                        + " speed: " + speed + " turn: " + turn + " atCross: "
                        + atCross);
            }

            // set the robot speed and direction
            drive.arcadeDrive(speed, turn);

            if (binaryValue != 0) {
                previousValue = binaryValue;
            }
            //oldTimeInSeconds = timeInSeconds;

            Timer.delay(0.005); // Wait 1/2 millisecond
        }
        // Done with loop - stop the robot. Robot should be at the end of line
        drive.arcadeDrive(0, 0);
        getWatchdog().setEnabled(false); // Watchdog control is off
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
        arm = new PIDController(0.1, 0.0, 0.00, armEncoder, new PIDOutput() {

            public void pidWrite(double output) {
                armMotor.set(output);
            }
        }, 0.005);
        arm.setSetpoint(0.0);
        arm.setContinuous(true);
        arm.setInputRange(-1.0, 36.0);
        arm.setTolerance(0.1);
        armEncoder.setPIDSourceParameter(Encoder.PIDSourceParameter.kDistance);
        arm.enable();

        System.out.println("\nTele-operated Control ON\n");
        gyro.reset();
        sonar.setEnabled(true);
        sonar.setAutomaticMode(true);
        armEncoder.start();
        armEncoder.reset();
        System.out.println("Arm is at " + armEncoder.getDistance() + " Setpoint: " + arm.getSetpoint() + "\n");
        if (!comp.enabled()) {
            comp.start();
        }
        getWatchdog().setEnabled(true); // Watchdog control is active
        // Main teleop operations loop
        while (isEnabled() && isOperatorControl()) {
            getWatchdog().feed(); // Keep watchdog alive
            System.out.println("Arm is at " + armEncoder.getDistance() + " Setpoint: " + arm.getSetpoint() + "\n");

            //System.out.println("Heading: "+gyro.getAngle()+"\n");
            //System.out.println("Range: " + (sonar.getRangeInches() / 12) +
            // " feet\n");
            // TANK DRIVE - Get both joystick Y Axis values and send data to
            // left/right speed controllers through RobotDrive object
            if (leftJoystick.getRawButton(5)) {
                // If button 5 (upper left trigger) then shift to high gear
                upshifter.set(true);
                downshifter.set(false);
            } else {
                upshifter.set(false);
                downshifter.set(true);
            }
            // Shoulder
            shoulderMotor.set(0.0); // Stop pivot from moving
            if (leftJoystick.getRawButton(6)) {
                if (maxShouldersafe.get()) {
                    // Haven't hit upper limit switch
                    shoulderMotor.set(1.0); // Pivot arm up
                } else {
                    // At upper limit, prohibit further upward motion
                    shoulderMotor.set(0.0); // Stop arm
                }
            } else {
                if (leftJoystick.getRawButton(8)) {
                    if (minShouldersafe.get()) {
                        // Haven't hit lower limit switch
                        shoulderMotor.set(-1.0); // Pivot arm down
                    } else {
                        // At lowest limit, prohibit further down motion
                        shoulderMotor.set(0.0); // Stop arm
                    }
                }
            }

            // Arm
            //armMotor.set(0.0); // Stop pivot from moving
            /*
            if (leftJoystick.getRawButton(1)) {
            if (!maxArmsafe.get()) {
            // Haven't hit upper limit switch
            armMotor.set(1.0); // push arm out
            } else {
            // At upper limit, prohibit further forward motion
            armMotor.set(1.0); // Stop arm
            System.out.println("Arm stopped due to MAX extension.\n");
            }
            System.out.println("Arm is at " + armEncoder.getDistance() +
            " inches\n");
            } else {
            if (leftJoystick.getRawButton(3)) {
            if (!minArmsafe.get()) {
            // Haven't hit lower limit switch
            armMotor.set(-1.0); // pull arm in
            } else {
            // At lowest limit, prohibit further reverse motion
            armMotor.set(-1.0); // Stop arm
            System.out.println("Arm stopped due to MIN extension.\n");
            }
            System.out.println("Arm is at " + armEncoder.getDistance() +
            " inches\n");
            }
            }
             */
            if (!minArmsafe.get()) {
                arm.disable();
                System.out.println("Minimum Arm length FAILSAFE - arm disabled at " + armEncoder.getDistance() + "\n");
            }
            if (!maxArmsafe.get()) {
                arm.disable();
                System.out.println("Maximum Arm length FAILSAFE - arm disabled at " + armEncoder.getDistance() + "\n");
            }
            if (leftJoystick.getRawButton(6)) {
                armMotor.set(0.5);  // Set arm to 5 inches
                armSetPoint = 0.0;
                armEncoder.reset();
            }
            if (leftJoystick.getRawButton(8)) {
                armMotor.set(-0.5);
                armSetPoint = 0.0;
                armEncoder.reset();
            }
            if (leftJoystick.getRawButton(1)) {
                armSetPoint = 5.0;  // Set arm to 5 inches


            }
            if (leftJoystick.getRawButton(2)) {
                armSetPoint = 0.0; // Test ONLY
            }
            if (leftJoystick.getRawButton(4)) {
                armSetPoint = 10.0;  // Set arm to 10 inches


            }
            if (leftJoystick.getRawButton(3)) {
                armSetPoint = 15.0;  // Set arm to 15 inches

            }
            arm.setSetpoint(armSetPoint);


            // Drive
            leftInput = leftJoystick.getY() * -1.0;
            //rightInput = leftJoystick.getThrottle(); // Using Logitech Gamepad
            rightInput = leftJoystick.getX() * -1.0;
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
        arm.setSetpoint(0.0); // Return arm to start position
        //arm.disable();
        System.out.println("ROBOT SHUTDOWN\n");
        getWatchdog().setEnabled(false); // Watchdog control is off
    }

    void updateDashboard() {
        Dashboard lowDashData = DriverStation.getInstance().getDashboardPackerLow();
        lowDashData.addCluster();
        {
            lowDashData.addCluster();
            {     //analog modules
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

################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Commands/AutoCommand.cpp \
../src/Commands/AutoContainerSet.cpp \
../src/Commands/AutoRecyclingBin.cpp \
../src/Commands/AutoStackTote.cpp \
../src/Commands/AutoToteSet.cpp \
../src/Commands/CompressorOff.cpp \
../src/Commands/CompressorOn.cpp \
../src/Commands/DriveDistance.cpp \
../src/Commands/DriveDistanceTimed.cpp \
../src/Commands/DriveHWheel.cpp \
../src/Commands/DriveReverseDirection.cpp \
../src/Commands/DriveSlow.cpp \
../src/Commands/DriveSpinLeft.cpp \
../src/Commands/DriveSpinRight.cpp \
../src/Commands/DriveStop.cpp \
../src/Commands/DriveTeleop.cpp \
../src/Commands/DriveTurn.cpp \
../src/Commands/ElevatorDisablePID.cpp \
../src/Commands/ElevatorDown.cpp \
../src/Commands/ElevatorEnablePID.cpp \
../src/Commands/ElevatorIdle.cpp \
../src/Commands/ElevatorMoveToPosition.cpp \
../src/Commands/ElevatorMoveToPosition1.cpp \
../src/Commands/ElevatorMoveToPosition2.cpp \
../src/Commands/ElevatorMoveToPosition3.cpp \
../src/Commands/ElevatorMoveToPosition4.cpp \
../src/Commands/ElevatorUp.cpp \
../src/Commands/GripperHold.cpp \
../src/Commands/GripperRelease.cpp \
../src/Commands/IntakeAcquireBoth.cpp \
../src/Commands/IntakeAcquireL.cpp \
../src/Commands/IntakeAcquireR.cpp \
../src/Commands/IntakeExpelBoth.cpp \
../src/Commands/IntakeExpelL.cpp \
../src/Commands/IntakeExpelR.cpp \
../src/Commands/IntakeIdleBoth.cpp \
../src/Commands/IntakeIdleL.cpp \
../src/Commands/IntakeIdleR.cpp \
../src/Commands/IntakeSpinL.cpp \
../src/Commands/IntakeSpinR.cpp 

OBJS += \
./src/Commands/AutoCommand.o \
./src/Commands/AutoContainerSet.o \
./src/Commands/AutoRecyclingBin.o \
./src/Commands/AutoStackTote.o \
./src/Commands/AutoToteSet.o \
./src/Commands/CompressorOff.o \
./src/Commands/CompressorOn.o \
./src/Commands/DriveDistance.o \
./src/Commands/DriveDistanceTimed.o \
./src/Commands/DriveHWheel.o \
./src/Commands/DriveReverseDirection.o \
./src/Commands/DriveSlow.o \
./src/Commands/DriveSpinLeft.o \
./src/Commands/DriveSpinRight.o \
./src/Commands/DriveStop.o \
./src/Commands/DriveTeleop.o \
./src/Commands/DriveTurn.o \
./src/Commands/ElevatorDisablePID.o \
./src/Commands/ElevatorDown.o \
./src/Commands/ElevatorEnablePID.o \
./src/Commands/ElevatorIdle.o \
./src/Commands/ElevatorMoveToPosition.o \
./src/Commands/ElevatorMoveToPosition1.o \
./src/Commands/ElevatorMoveToPosition2.o \
./src/Commands/ElevatorMoveToPosition3.o \
./src/Commands/ElevatorMoveToPosition4.o \
./src/Commands/ElevatorUp.o \
./src/Commands/GripperHold.o \
./src/Commands/GripperRelease.o \
./src/Commands/IntakeAcquireBoth.o \
./src/Commands/IntakeAcquireL.o \
./src/Commands/IntakeAcquireR.o \
./src/Commands/IntakeExpelBoth.o \
./src/Commands/IntakeExpelL.o \
./src/Commands/IntakeExpelR.o \
./src/Commands/IntakeIdleBoth.o \
./src/Commands/IntakeIdleL.o \
./src/Commands/IntakeIdleR.o \
./src/Commands/IntakeSpinL.o \
./src/Commands/IntakeSpinR.o 

CPP_DEPS += \
./src/Commands/AutoCommand.d \
./src/Commands/AutoContainerSet.d \
./src/Commands/AutoRecyclingBin.d \
./src/Commands/AutoStackTote.d \
./src/Commands/AutoToteSet.d \
./src/Commands/CompressorOff.d \
./src/Commands/CompressorOn.d \
./src/Commands/DriveDistance.d \
./src/Commands/DriveDistanceTimed.d \
./src/Commands/DriveHWheel.d \
./src/Commands/DriveReverseDirection.d \
./src/Commands/DriveSlow.d \
./src/Commands/DriveSpinLeft.d \
./src/Commands/DriveSpinRight.d \
./src/Commands/DriveStop.d \
./src/Commands/DriveTeleop.d \
./src/Commands/DriveTurn.d \
./src/Commands/ElevatorDisablePID.d \
./src/Commands/ElevatorDown.d \
./src/Commands/ElevatorEnablePID.d \
./src/Commands/ElevatorIdle.d \
./src/Commands/ElevatorMoveToPosition.d \
./src/Commands/ElevatorMoveToPosition1.d \
./src/Commands/ElevatorMoveToPosition2.d \
./src/Commands/ElevatorMoveToPosition3.d \
./src/Commands/ElevatorMoveToPosition4.d \
./src/Commands/ElevatorUp.d \
./src/Commands/GripperHold.d \
./src/Commands/GripperRelease.d \
./src/Commands/IntakeAcquireBoth.d \
./src/Commands/IntakeAcquireL.d \
./src/Commands/IntakeAcquireR.d \
./src/Commands/IntakeExpelBoth.d \
./src/Commands/IntakeExpelL.d \
./src/Commands/IntakeExpelR.d \
./src/Commands/IntakeIdleBoth.d \
./src/Commands/IntakeIdleL.d \
./src/Commands/IntakeIdleR.d \
./src/Commands/IntakeSpinL.d \
./src/Commands/IntakeSpinR.d 


# Each subdirectory must supply rules for building sources it contributes
src/Commands/%.o: ../src/Commands/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"\$\{workspace_loc:/Robot2015}/src" -IC:\Users\PHS-User/wpilib/cpp/current/sim/include -I/usr/include -I/usr/include/gazebo-3.1 -I/usr/include/sdformat-2.2 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



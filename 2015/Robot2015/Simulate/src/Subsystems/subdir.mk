################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Subsystems/Chassis.cpp \
../src/Subsystems/Elevator.cpp \
../src/Subsystems/Gripper.cpp \
../src/Subsystems/Intake.cpp \
../src/Subsystems/Pneumatics.cpp 

OBJS += \
./src/Subsystems/Chassis.o \
./src/Subsystems/Elevator.o \
./src/Subsystems/Gripper.o \
./src/Subsystems/Intake.o \
./src/Subsystems/Pneumatics.o 

CPP_DEPS += \
./src/Subsystems/Chassis.d \
./src/Subsystems/Elevator.d \
./src/Subsystems/Gripper.d \
./src/Subsystems/Intake.d \
./src/Subsystems/Pneumatics.d 


# Each subdirectory must supply rules for building sources it contributes
src/Subsystems/%.o: ../src/Subsystems/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"\$\{workspace_loc:/Robot2015}/src" -IC:\Users\PHS-User/wpilib/cpp/current/sim/include -I/usr/include -I/usr/include/gazebo-3.1 -I/usr/include/sdformat-2.2 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



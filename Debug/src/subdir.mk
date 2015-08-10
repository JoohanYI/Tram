################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/bluetooth.cpp \
../src/bluetooth_switch.cpp \
../src/iBeaconInfo.cpp \
../src/main.cpp \
../src/motorControl.cpp 

OBJS += \
./src/bluetooth.o \
./src/bluetooth_switch.o \
./src/iBeaconInfo.o \
./src/main.o \
./src/motorControl.o 

CPP_DEPS += \
./src/bluetooth.d \
./src/bluetooth_switch.d \
./src/iBeaconInfo.d \
./src/main.d \
./src/motorControl.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/include/opencv2 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



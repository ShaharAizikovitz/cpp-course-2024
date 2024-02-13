################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Curr_Time.cpp \
../Date_Only.cpp \
../Mock_Clock.cpp \
../stdafx.cpp 

OBJS += \
./Curr_Time.o \
./Date_Only.o \
./Mock_Clock.o \
./stdafx.o 

CPP_DEPS += \
./Curr_Time.d \
./Date_Only.d \
./Mock_Clock.d \
./stdafx.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -std=c++1y -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Curr_Time.cpp \
../Mock_Clock.cpp \
../Test_Multithreading.cpp 

OBJS += \
./Curr_Time.o \
./Mock_Clock.o \
./Test_Multithreading.o 

CPP_DEPS += \
./Curr_Time.d \
./Mock_Clock.d \
./Test_Multithreading.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -std=c++1y -I"/home/qa/workspace/QAMRCPPD_Labs/Ch14_Multithreading/Time_Library" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



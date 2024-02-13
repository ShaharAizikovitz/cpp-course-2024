################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Curr_Time.cpp \
../Date_Only.cpp \
../Test_Volatile_Variables.cpp 

OBJS += \
./Curr_Time.o \
./Date_Only.o \
./Test_Volatile_Variables.o 

CPP_DEPS += \
./Curr_Time.d \
./Date_Only.d \
./Test_Volatile_Variables.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



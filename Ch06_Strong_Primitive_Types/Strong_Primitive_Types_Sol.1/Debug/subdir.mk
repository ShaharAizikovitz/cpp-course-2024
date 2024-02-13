################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Test_Strong_Primitive_Types.cpp 

OBJS += \
./Test_Strong_Primitive_Types.o 

CPP_DEPS += \
./Test_Strong_Primitive_Types.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



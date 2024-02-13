################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../accimpl.cpp \
../accproxy.cpp \
../bank.cpp \
../test_SmartPtr.cpp 

OBJS += \
./accimpl.o \
./accproxy.o \
./bank.o \
./test_SmartPtr.o 

CPP_DEPS += \
./accimpl.d \
./accproxy.d \
./bank.d \
./test_SmartPtr.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -std=c++1y -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



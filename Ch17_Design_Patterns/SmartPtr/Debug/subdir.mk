################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Test_SmartPtr.cpp \
../accimpl.cpp \
../accproxy.cpp \
../bank.cpp 

OBJS += \
./Test_SmartPtr.o \
./accimpl.o \
./accproxy.o \
./bank.o 

CPP_DEPS += \
./Test_SmartPtr.d \
./accimpl.d \
./accproxy.d \
./bank.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -std=c++1y -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



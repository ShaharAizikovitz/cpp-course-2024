################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: Containers_Sol.4

dependents:
	-cd /home/qa/workspace/QAMRCPPD_Labs/Ch19_Containers/Time_Library/Debug && $(MAKE) all

# Tool invocations
Containers_Sol.4: $(OBJS) $(USER_OBJS) /home/qa/workspace/QAMRCPPD_Labs/Ch19_Containers/Time_Library/Debug/lib19_Time_Library.a
	@echo 'Building target: $@'
	@echo 'Invoking: Cross G++ Linker'
	g++ -L"/home/qa/workspace/QAMRCPPD_Labs/Ch19_Containers/Time_Library/Debug" -o "Containers_Sol.4" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(C++_DEPS)$(OBJS)$(C_DEPS)$(CC_DEPS)$(CPP_DEPS)$(EXECUTABLES)$(CXX_DEPS)$(C_UPPER_DEPS) Containers_Sol.4
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:
/home/qa/workspace/QAMRCPPD_Labs/Ch19_Containers/Time_Library/Debug/lib19_Time_Library.a:

-include ../makefile.targets

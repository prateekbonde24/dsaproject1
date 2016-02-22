################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../parfor.cc \
../private.cc \
../reduction.cc \
../schedule.cc 

OBJS += \
./parfor.o \
./private.o \
./reduction.o \
./schedule.o 

CC_DEPS += \
./parfor.d \
./private.d \
./reduction.d \
./schedule.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



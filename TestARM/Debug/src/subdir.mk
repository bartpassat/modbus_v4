################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/Modbus.c \
../src/Modbus_Circutor_CVM_1D_Registers.c \
../src/Serial.c \
../src/TestARM.c 

C_DEPS += \
./src/Modbus.d \
./src/Modbus_Circutor_CVM_1D_Registers.d \
./src/Serial.d \
./src/TestARM.d 

OBJS += \
./src/Modbus.o \
./src/Modbus_Circutor_CVM_1D_Registers.o \
./src/Serial.o \
./src/TestARM.o 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	arm-linux-gnueabihf-gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src

clean-src:
	-$(RM) ./src/Modbus.d ./src/Modbus.o ./src/Modbus_Circutor_CVM_1D_Registers.d ./src/Modbus_Circutor_CVM_1D_Registers.o ./src/Serial.d ./src/Serial.o ./src/TestARM.d ./src/TestARM.o

.PHONY: clean-src


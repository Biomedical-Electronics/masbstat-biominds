################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/components/PMU.c \
../Core/Src/components/ad5280_driver.c \
../Core/Src/components/adc.c \
../Core/Src/components/chronoamperometry.c \
../Core/Src/components/cobs.c \
../Core/Src/components/cyclic_voltammetry.c \
../Core/Src/components/formulas.c \
../Core/Src/components/i2c_lib.c \
../Core/Src/components/masb_comm_s.c \
../Core/Src/components/mcp4725_driver.c \
../Core/Src/components/rele.c \
../Core/Src/components/stm32main.c \
../Core/Src/components/timers.c 

OBJS += \
./Core/Src/components/PMU.o \
./Core/Src/components/ad5280_driver.o \
./Core/Src/components/adc.o \
./Core/Src/components/chronoamperometry.o \
./Core/Src/components/cobs.o \
./Core/Src/components/cyclic_voltammetry.o \
./Core/Src/components/formulas.o \
./Core/Src/components/i2c_lib.o \
./Core/Src/components/masb_comm_s.o \
./Core/Src/components/mcp4725_driver.o \
./Core/Src/components/rele.o \
./Core/Src/components/stm32main.o \
./Core/Src/components/timers.o 

C_DEPS += \
./Core/Src/components/PMU.d \
./Core/Src/components/ad5280_driver.d \
./Core/Src/components/adc.d \
./Core/Src/components/chronoamperometry.d \
./Core/Src/components/cobs.d \
./Core/Src/components/cyclic_voltammetry.d \
./Core/Src/components/formulas.d \
./Core/Src/components/i2c_lib.d \
./Core/Src/components/masb_comm_s.d \
./Core/Src/components/mcp4725_driver.d \
./Core/Src/components/rele.d \
./Core/Src/components/stm32main.d \
./Core/Src/components/timers.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/components/%.o Core/Src/components/%.su: ../Core/Src/components/%.c Core/Src/components/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DUSE_HAL_DRIVER -DSTM32F401xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-components

clean-Core-2f-Src-2f-components:
	-$(RM) ./Core/Src/components/PMU.d ./Core/Src/components/PMU.o ./Core/Src/components/PMU.su ./Core/Src/components/ad5280_driver.d ./Core/Src/components/ad5280_driver.o ./Core/Src/components/ad5280_driver.su ./Core/Src/components/adc.d ./Core/Src/components/adc.o ./Core/Src/components/adc.su ./Core/Src/components/chronoamperometry.d ./Core/Src/components/chronoamperometry.o ./Core/Src/components/chronoamperometry.su ./Core/Src/components/cobs.d ./Core/Src/components/cobs.o ./Core/Src/components/cobs.su ./Core/Src/components/cyclic_voltammetry.d ./Core/Src/components/cyclic_voltammetry.o ./Core/Src/components/cyclic_voltammetry.su ./Core/Src/components/formulas.d ./Core/Src/components/formulas.o ./Core/Src/components/formulas.su ./Core/Src/components/i2c_lib.d ./Core/Src/components/i2c_lib.o ./Core/Src/components/i2c_lib.su ./Core/Src/components/masb_comm_s.d ./Core/Src/components/masb_comm_s.o ./Core/Src/components/masb_comm_s.su ./Core/Src/components/mcp4725_driver.d ./Core/Src/components/mcp4725_driver.o ./Core/Src/components/mcp4725_driver.su ./Core/Src/components/rele.d ./Core/Src/components/rele.o ./Core/Src/components/rele.su ./Core/Src/components/stm32main.d ./Core/Src/components/stm32main.o ./Core/Src/components/stm32main.su ./Core/Src/components/timers.d ./Core/Src/components/timers.o ./Core/Src/components/timers.su

.PHONY: clean-Core-2f-Src-2f-components


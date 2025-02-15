################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middleware/STemWin/OS/GUI_X.c 

OBJS += \
./Middleware/STemWin/OS/GUI_X.o 

C_DEPS += \
./Middleware/STemWin/OS/GUI_X.d 


# Each subdirectory must supply rules for building sources it contributes
Middleware/STemWin/OS/%.o: ../Middleware/STemWin/OS/%.c Middleware/STemWin/OS/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DARM_MATH_CM7 -DSTM32F746xx -DDEBUG -c -I../Drivers/CMSIS/Include -I../Drivers/BSP/STM32746G-Discovery/ -I../Middleware/STemWin/Config/ -I../Middleware/STemWin/inc/ -I../Drivers/CMSIS/Core/Include/ -I../Drivers/CMSIS/DSP/Include/ -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Middleware/emWinWrapper -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middleware-2f-STemWin-2f-OS

clean-Middleware-2f-STemWin-2f-OS:
	-$(RM) ./Middleware/STemWin/OS/GUI_X.d ./Middleware/STemWin/OS/GUI_X.o

.PHONY: clean-Middleware-2f-STemWin-2f-OS


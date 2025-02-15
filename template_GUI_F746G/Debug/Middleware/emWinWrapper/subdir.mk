################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middleware/emWinWrapper/emWinWrapper.c \
../Middleware/emWinWrapper/mtouch.c \
../Middleware/emWinWrapper/wfm_graph.c 

OBJS += \
./Middleware/emWinWrapper/emWinWrapper.o \
./Middleware/emWinWrapper/mtouch.o \
./Middleware/emWinWrapper/wfm_graph.o 

C_DEPS += \
./Middleware/emWinWrapper/emWinWrapper.d \
./Middleware/emWinWrapper/mtouch.d \
./Middleware/emWinWrapper/wfm_graph.d 


# Each subdirectory must supply rules for building sources it contributes
Middleware/emWinWrapper/%.o: ../Middleware/emWinWrapper/%.c Middleware/emWinWrapper/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DARM_MATH_CM7 -DSTM32F746xx -DDEBUG -c -I../Drivers/CMSIS/Include -I../Drivers/BSP/STM32746G-Discovery/ -I../Middleware/STemWin/Config/ -I../Middleware/STemWin/inc/ -I../Drivers/CMSIS/Core/Include/ -I../Drivers/CMSIS/DSP/Include/ -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Middleware/emWinWrapper -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middleware-2f-emWinWrapper

clean-Middleware-2f-emWinWrapper:
	-$(RM) ./Middleware/emWinWrapper/emWinWrapper.d ./Middleware/emWinWrapper/emWinWrapper.o ./Middleware/emWinWrapper/mtouch.d ./Middleware/emWinWrapper/mtouch.o ./Middleware/emWinWrapper/wfm_graph.d ./Middleware/emWinWrapper/wfm_graph.o

.PHONY: clean-Middleware-2f-emWinWrapper


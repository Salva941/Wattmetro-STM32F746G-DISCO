################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/CMSIS/DSP/Source/SupportFunctions/arm_copy_f32.c \
../Drivers/CMSIS/DSP/Source/SupportFunctions/arm_copy_q15.c \
../Drivers/CMSIS/DSP/Source/SupportFunctions/arm_copy_q31.c \
../Drivers/CMSIS/DSP/Source/SupportFunctions/arm_copy_q7.c \
../Drivers/CMSIS/DSP/Source/SupportFunctions/arm_fill_f32.c \
../Drivers/CMSIS/DSP/Source/SupportFunctions/arm_fill_q15.c \
../Drivers/CMSIS/DSP/Source/SupportFunctions/arm_fill_q31.c \
../Drivers/CMSIS/DSP/Source/SupportFunctions/arm_fill_q7.c \
../Drivers/CMSIS/DSP/Source/SupportFunctions/arm_float_to_q15.c \
../Drivers/CMSIS/DSP/Source/SupportFunctions/arm_float_to_q31.c \
../Drivers/CMSIS/DSP/Source/SupportFunctions/arm_float_to_q7.c \
../Drivers/CMSIS/DSP/Source/SupportFunctions/arm_q15_to_float.c \
../Drivers/CMSIS/DSP/Source/SupportFunctions/arm_q15_to_q31.c \
../Drivers/CMSIS/DSP/Source/SupportFunctions/arm_q15_to_q7.c \
../Drivers/CMSIS/DSP/Source/SupportFunctions/arm_q31_to_float.c \
../Drivers/CMSIS/DSP/Source/SupportFunctions/arm_q31_to_q15.c \
../Drivers/CMSIS/DSP/Source/SupportFunctions/arm_q31_to_q7.c \
../Drivers/CMSIS/DSP/Source/SupportFunctions/arm_q7_to_float.c \
../Drivers/CMSIS/DSP/Source/SupportFunctions/arm_q7_to_q15.c \
../Drivers/CMSIS/DSP/Source/SupportFunctions/arm_q7_to_q31.c 

OBJS += \
./Drivers/CMSIS/DSP/Source/SupportFunctions/arm_copy_f32.o \
./Drivers/CMSIS/DSP/Source/SupportFunctions/arm_copy_q15.o \
./Drivers/CMSIS/DSP/Source/SupportFunctions/arm_copy_q31.o \
./Drivers/CMSIS/DSP/Source/SupportFunctions/arm_copy_q7.o \
./Drivers/CMSIS/DSP/Source/SupportFunctions/arm_fill_f32.o \
./Drivers/CMSIS/DSP/Source/SupportFunctions/arm_fill_q15.o \
./Drivers/CMSIS/DSP/Source/SupportFunctions/arm_fill_q31.o \
./Drivers/CMSIS/DSP/Source/SupportFunctions/arm_fill_q7.o \
./Drivers/CMSIS/DSP/Source/SupportFunctions/arm_float_to_q15.o \
./Drivers/CMSIS/DSP/Source/SupportFunctions/arm_float_to_q31.o \
./Drivers/CMSIS/DSP/Source/SupportFunctions/arm_float_to_q7.o \
./Drivers/CMSIS/DSP/Source/SupportFunctions/arm_q15_to_float.o \
./Drivers/CMSIS/DSP/Source/SupportFunctions/arm_q15_to_q31.o \
./Drivers/CMSIS/DSP/Source/SupportFunctions/arm_q15_to_q7.o \
./Drivers/CMSIS/DSP/Source/SupportFunctions/arm_q31_to_float.o \
./Drivers/CMSIS/DSP/Source/SupportFunctions/arm_q31_to_q15.o \
./Drivers/CMSIS/DSP/Source/SupportFunctions/arm_q31_to_q7.o \
./Drivers/CMSIS/DSP/Source/SupportFunctions/arm_q7_to_float.o \
./Drivers/CMSIS/DSP/Source/SupportFunctions/arm_q7_to_q15.o \
./Drivers/CMSIS/DSP/Source/SupportFunctions/arm_q7_to_q31.o 

C_DEPS += \
./Drivers/CMSIS/DSP/Source/SupportFunctions/arm_copy_f32.d \
./Drivers/CMSIS/DSP/Source/SupportFunctions/arm_copy_q15.d \
./Drivers/CMSIS/DSP/Source/SupportFunctions/arm_copy_q31.d \
./Drivers/CMSIS/DSP/Source/SupportFunctions/arm_copy_q7.d \
./Drivers/CMSIS/DSP/Source/SupportFunctions/arm_fill_f32.d \
./Drivers/CMSIS/DSP/Source/SupportFunctions/arm_fill_q15.d \
./Drivers/CMSIS/DSP/Source/SupportFunctions/arm_fill_q31.d \
./Drivers/CMSIS/DSP/Source/SupportFunctions/arm_fill_q7.d \
./Drivers/CMSIS/DSP/Source/SupportFunctions/arm_float_to_q15.d \
./Drivers/CMSIS/DSP/Source/SupportFunctions/arm_float_to_q31.d \
./Drivers/CMSIS/DSP/Source/SupportFunctions/arm_float_to_q7.d \
./Drivers/CMSIS/DSP/Source/SupportFunctions/arm_q15_to_float.d \
./Drivers/CMSIS/DSP/Source/SupportFunctions/arm_q15_to_q31.d \
./Drivers/CMSIS/DSP/Source/SupportFunctions/arm_q15_to_q7.d \
./Drivers/CMSIS/DSP/Source/SupportFunctions/arm_q31_to_float.d \
./Drivers/CMSIS/DSP/Source/SupportFunctions/arm_q31_to_q15.d \
./Drivers/CMSIS/DSP/Source/SupportFunctions/arm_q31_to_q7.d \
./Drivers/CMSIS/DSP/Source/SupportFunctions/arm_q7_to_float.d \
./Drivers/CMSIS/DSP/Source/SupportFunctions/arm_q7_to_q15.d \
./Drivers/CMSIS/DSP/Source/SupportFunctions/arm_q7_to_q31.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/CMSIS/DSP/Source/SupportFunctions/%.o: ../Drivers/CMSIS/DSP/Source/SupportFunctions/%.c Drivers/CMSIS/DSP/Source/SupportFunctions/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DARM_MATH_CM7 -DSTM32F746xx -DDEBUG -c -I../Drivers/CMSIS/Include -I../Drivers/BSP/STM32746G-Discovery/ -I../Middleware/STemWin/Config/ -I../Middleware/STemWin/inc/ -I../Drivers/CMSIS/Core/Include/ -I../Drivers/CMSIS/DSP/Include/ -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Middleware/emWinWrapper -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-CMSIS-2f-DSP-2f-Source-2f-SupportFunctions

clean-Drivers-2f-CMSIS-2f-DSP-2f-Source-2f-SupportFunctions:
	-$(RM) ./Drivers/CMSIS/DSP/Source/SupportFunctions/arm_copy_f32.d ./Drivers/CMSIS/DSP/Source/SupportFunctions/arm_copy_f32.o ./Drivers/CMSIS/DSP/Source/SupportFunctions/arm_copy_q15.d ./Drivers/CMSIS/DSP/Source/SupportFunctions/arm_copy_q15.o ./Drivers/CMSIS/DSP/Source/SupportFunctions/arm_copy_q31.d ./Drivers/CMSIS/DSP/Source/SupportFunctions/arm_copy_q31.o ./Drivers/CMSIS/DSP/Source/SupportFunctions/arm_copy_q7.d ./Drivers/CMSIS/DSP/Source/SupportFunctions/arm_copy_q7.o ./Drivers/CMSIS/DSP/Source/SupportFunctions/arm_fill_f32.d ./Drivers/CMSIS/DSP/Source/SupportFunctions/arm_fill_f32.o ./Drivers/CMSIS/DSP/Source/SupportFunctions/arm_fill_q15.d ./Drivers/CMSIS/DSP/Source/SupportFunctions/arm_fill_q15.o ./Drivers/CMSIS/DSP/Source/SupportFunctions/arm_fill_q31.d ./Drivers/CMSIS/DSP/Source/SupportFunctions/arm_fill_q31.o ./Drivers/CMSIS/DSP/Source/SupportFunctions/arm_fill_q7.d ./Drivers/CMSIS/DSP/Source/SupportFunctions/arm_fill_q7.o ./Drivers/CMSIS/DSP/Source/SupportFunctions/arm_float_to_q15.d ./Drivers/CMSIS/DSP/Source/SupportFunctions/arm_float_to_q15.o ./Drivers/CMSIS/DSP/Source/SupportFunctions/arm_float_to_q31.d ./Drivers/CMSIS/DSP/Source/SupportFunctions/arm_float_to_q31.o ./Drivers/CMSIS/DSP/Source/SupportFunctions/arm_float_to_q7.d ./Drivers/CMSIS/DSP/Source/SupportFunctions/arm_float_to_q7.o ./Drivers/CMSIS/DSP/Source/SupportFunctions/arm_q15_to_float.d ./Drivers/CMSIS/DSP/Source/SupportFunctions/arm_q15_to_float.o ./Drivers/CMSIS/DSP/Source/SupportFunctions/arm_q15_to_q31.d ./Drivers/CMSIS/DSP/Source/SupportFunctions/arm_q15_to_q31.o ./Drivers/CMSIS/DSP/Source/SupportFunctions/arm_q15_to_q7.d ./Drivers/CMSIS/DSP/Source/SupportFunctions/arm_q15_to_q7.o ./Drivers/CMSIS/DSP/Source/SupportFunctions/arm_q31_to_float.d ./Drivers/CMSIS/DSP/Source/SupportFunctions/arm_q31_to_float.o ./Drivers/CMSIS/DSP/Source/SupportFunctions/arm_q31_to_q15.d ./Drivers/CMSIS/DSP/Source/SupportFunctions/arm_q31_to_q15.o ./Drivers/CMSIS/DSP/Source/SupportFunctions/arm_q31_to_q7.d ./Drivers/CMSIS/DSP/Source/SupportFunctions/arm_q31_to_q7.o ./Drivers/CMSIS/DSP/Source/SupportFunctions/arm_q7_to_float.d ./Drivers/CMSIS/DSP/Source/SupportFunctions/arm_q7_to_float.o ./Drivers/CMSIS/DSP/Source/SupportFunctions/arm_q7_to_q15.d ./Drivers/CMSIS/DSP/Source/SupportFunctions/arm_q7_to_q15.o ./Drivers/CMSIS/DSP/Source/SupportFunctions/arm_q7_to_q31.d ./Drivers/CMSIS/DSP/Source/SupportFunctions/arm_q7_to_q31.o

.PHONY: clean-Drivers-2f-CMSIS-2f-DSP-2f-Source-2f-SupportFunctions


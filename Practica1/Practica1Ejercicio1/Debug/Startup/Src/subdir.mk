################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Startup/Src/main.c 

OBJS += \
./Startup/Src/main.o 

C_DEPS += \
./Startup/Src/main.d 


# Each subdirectory must supply rules for building sources it contributes
Startup/Src/%.o Startup/Src/%.su: ../Startup/Src/%.c Startup/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F429ZITx -DSTM32F4 -DNUCLEO_F429ZI -DUSE_HAL_DRIVER -DSTM32F429xx -c -I../Inc -I"/home/felix/Tp_patricio_cese/PdM_workspace/Practica1/Practica1Ejercicio1/Drivers/STM32F4xx_HAL_Driver/Inc" -I"/home/felix/Tp_patricio_cese/PdM_workspace/Practica1/Practica1Ejercicio1/Drivers/CMSIS/Include" -I"/home/felix/Tp_patricio_cese/PdM_workspace/Practica1/Practica1Ejercicio1/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"/home/felix/Tp_patricio_cese/PdM_workspace/Practica1/Practica1Ejercicio1/Drivers/BSP/STM32F4xx_Nucleo_144" -I"/home/felix/Tp_patricio_cese/PdM_workspace/Practica1/Practica1Ejercicio1/Drivers/Core/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Startup-2f-Src

clean-Startup-2f-Src:
	-$(RM) ./Startup/Src/main.d ./Startup/Src/main.o ./Startup/Src/main.su

.PHONY: clean-Startup-2f-Src


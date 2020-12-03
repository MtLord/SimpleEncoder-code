################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Core/Inc/MPU9250/MPU9250.cpp 

OBJS += \
./Core/Inc/MPU9250/MPU9250.o 

CPP_DEPS += \
./Core/Inc/MPU9250/MPU9250.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Inc/MPU9250/MPU9250.o: ../Core/Inc/MPU9250/MPU9250.cpp
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++11 -g3 -DUSE_HAL_DRIVER -DSTM32F446xx -DDEBUG -c -I../Drivers/CMSIS/Include -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Core/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-threadsafe-statics -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"Core/Inc/MPU9250/MPU9250.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"


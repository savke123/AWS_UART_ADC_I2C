################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/MPPT.c \
../Src/MQTTInterface.c \
../Src/RTC.c \
../Src/adc.c \
../Src/ethernetif.c \
../Src/freertos.c \
../Src/gpio.c \
../Src/hardware_rng.c \
../Src/i2c.c \
../Src/lwip.c \
../Src/main.c \
../Src/mbedtls.c \
../Src/mqtt_task.c \
../Src/net_sockets.c \
../Src/rng.c \
../Src/stm32f4xx_hal_msp.c \
../Src/stm32f4xx_hal_timebase_tim.c \
../Src/stm32f4xx_it.c \
../Src/syscalls.c \
../Src/sysmem.c \
../Src/system_stm32f4xx.c \
../Src/usart.c 

OBJS += \
./Src/MPPT.o \
./Src/MQTTInterface.o \
./Src/RTC.o \
./Src/adc.o \
./Src/ethernetif.o \
./Src/freertos.o \
./Src/gpio.o \
./Src/hardware_rng.o \
./Src/i2c.o \
./Src/lwip.o \
./Src/main.o \
./Src/mbedtls.o \
./Src/mqtt_task.o \
./Src/net_sockets.o \
./Src/rng.o \
./Src/stm32f4xx_hal_msp.o \
./Src/stm32f4xx_hal_timebase_tim.o \
./Src/stm32f4xx_it.o \
./Src/syscalls.o \
./Src/sysmem.o \
./Src/system_stm32f4xx.o \
./Src/usart.o 

C_DEPS += \
./Src/MPPT.d \
./Src/MQTTInterface.d \
./Src/RTC.d \
./Src/adc.d \
./Src/ethernetif.d \
./Src/freertos.d \
./Src/gpio.d \
./Src/hardware_rng.d \
./Src/i2c.d \
./Src/lwip.d \
./Src/main.d \
./Src/mbedtls.d \
./Src/mqtt_task.d \
./Src/net_sockets.d \
./Src/rng.d \
./Src/stm32f4xx_hal_msp.d \
./Src/stm32f4xx_hal_timebase_tim.d \
./Src/stm32f4xx_it.d \
./Src/syscalls.d \
./Src/sysmem.d \
./Src/system_stm32f4xx.d \
./Src/usart.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o: ../Src/%.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 '-DMBEDTLS_CONFIG_FILE="mbedtls_config.h"' -DUSE_HAL_DRIVER -DDEBUG -DSTM32F429xx -c -I../Middlewares/Third_Party/LwIP/src/include/netif/ppp -I../Middlewares/Third_Party/MQTT -I../Middlewares/Third_Party/LwIP/src/include/compat/stdc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Middlewares/Third_Party/MQTT/MQTTPacket -I../Middlewares/Third_Party/LwIP/system/arch -I../Middlewares/Third_Party/LwIP/src/include -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Middlewares/Third_Party/LwIP/src/include/compat/posix -I../Middlewares/Third_Party/LwIP/src/include/lwip -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/Third_Party/LwIP/src/include/compat/posix/arpa -I../Middlewares/Third_Party/LwIP/system -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/LwIP/src/include/lwip/priv -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Middlewares/Third_Party/LwIP/src/include/lwip/prot -I../Middlewares/Third_Party/LwIP/src/include/lwip/apps -I../Middlewares/Third_Party/LwIP/src/include/compat/posix/sys -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/mbedTLS/include/mbedtls -I../Inc -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/LwIP/src/include/compat/posix/net -I../Middlewares/Third_Party/mbedTLS/include -I../Middlewares/Third_Party/LwIP/src/include/netif -O1 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"


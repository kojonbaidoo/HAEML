################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/Phase_1.c \
../source/mtb.c \
../source/semihost_hardfault.c 

C_DEPS += \
./source/Phase_1.d \
./source/mtb.d \
./source/semihost_hardfault.d 

OBJS += \
./source/Phase_1.o \
./source/mtb.o \
./source/semihost_hardfault.o 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.c source/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DCPU_MKL25Z128VLK4 -DCPU_MKL25Z128VLK4_cm0plus -DFSL_RTOS_BM -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=0 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"C:\Users\Kojo\OneDrive\Ashesi\Capstone\Implementation\Phase_1\Phase_1\board" -I"C:\Users\Kojo\OneDrive\Ashesi\Capstone\Implementation\Phase_1\Phase_1\source" -I"C:\Users\Kojo\OneDrive\Ashesi\Capstone\Implementation\Phase_1\Phase_1" -I"C:\Users\Kojo\OneDrive\Ashesi\Capstone\Implementation\Phase_1\Phase_1\drivers" -I"C:\Users\Kojo\OneDrive\Ashesi\Capstone\Implementation\Phase_1\Phase_1\CMSIS" -I"C:\Users\Kojo\OneDrive\Ashesi\Capstone\Implementation\Phase_1\Phase_1\utilities" -I"C:\Users\Kojo\OneDrive\Ashesi\Capstone\Implementation\Phase_1\Phase_1\startup" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-source

clean-source:
	-$(RM) ./source/Phase_1.d ./source/Phase_1.o ./source/mtb.d ./source/mtb.o ./source/semihost_hardfault.d ./source/semihost_hardfault.o

.PHONY: clean-source


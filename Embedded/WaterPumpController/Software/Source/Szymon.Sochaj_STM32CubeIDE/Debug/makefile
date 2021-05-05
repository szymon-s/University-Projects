################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Drivers/STM32L4xx_HAL_Driver/Src/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
Szymon.Sochaj_projektSMiW.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
Szymon.Sochaj_projektSMiW.list \

OBJCOPY_BIN += \
Szymon.Sochaj_projektSMiW.bin \


# All Target
all: Szymon.Sochaj_projektSMiW.elf secondary-outputs

# Tool invocations
Szymon.Sochaj_projektSMiW.elf: $(OBJS) $(USER_OBJS) D:\STM32Cube\Szymon.Sochaj_projektSMiW\STM32L432KCUX_FLASH.ld
	arm-none-eabi-gcc -o "Szymon.Sochaj_projektSMiW.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m4 -T"D:\STM32Cube\Szymon.Sochaj_projektSMiW\STM32L432KCUX_FLASH.ld" --specs=nosys.specs -Wl,-Map="Szymon.Sochaj_projektSMiW.map" -Wl,--gc-sections -static --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -u _printf_float -u _scanf_float -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

Szymon.Sochaj_projektSMiW.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "Szymon.Sochaj_projektSMiW.list"
	@echo 'Finished building: $@'
	@echo ' '

Szymon.Sochaj_projektSMiW.bin: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "Szymon.Sochaj_projektSMiW.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_BIN)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

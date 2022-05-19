################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := C:/ti/ccs1110/ccs/tools/compiler/ti-cgt-arm_20.2.6.LTS

GEN_OPTS__FLAG := 
GEN_CMDS__FLAG := 

ORDERED_OBJS += \
"./com.obj" \
"./croutine.obj" \
"./event_groups.obj" \
"./heap_2.obj" \
"./i2c.obj" \
"./list.obj" \
"./main.obj" \
"./port.obj" \
"./portasm.obj" \
"./queue.obj" \
"./startup_frt.obj" \
"./status_led.obj" \
"./stream_buffer.obj" \
"./systick_frt.obj" \
"./tasks.obj" \
"./timers.obj" \
"./uart0.obj" \
"./driverlib/cpu.obj" \
"./driverlib/gpio.obj" \
"./driverlib/i2c.obj" \
"./driverlib/interrupt.obj" \
"./driverlib/sysctl.obj" \
"./driverlib/uart.obj" \
"./utils/uartstdio.obj" \
"../tm4c123gh6pm.cmd" \
$(GEN_CMDS__FLAG) \
-llibc.a \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include driverlib/subdir_vars.mk
-include utils/subdir_vars.mk
-include subdir_rules.mk
-include driverlib/subdir_rules.mk
-include utils/subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(SV7A_DEPS)),)
-include $(SV7A_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
Projektv1.out \

EXE_OUTPUTS__QUOTED += \
"Projektv1.out" \

BIN_OUTPUTS += \
Projektv1.hex \

BIN_OUTPUTS__QUOTED += \
"Projektv1.hex" \


# All Target
all: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@$(MAKE) --no-print-directory -Onone "Projektv1.out"

# Tool invocations
Projektv1.out: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@echo 'Building target: "$@"'
	@echo 'Invoking: Arm Linker'
	"C:/ti/ccs1110/ccs/tools/compiler/ti-cgt-arm_20.2.6.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --define=ccs="ccs" --define=PART_TM4C123GH6PM -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi -z -m"Projektv1.map" --heap_size=0 --stack_size=512 -i"C:/ti/ccs1110/ccs/tools/compiler/ti-cgt-arm_20.2.6.LTS/lib" -i"C:/ti/ccs1110/ccs/tools/compiler/ti-cgt-arm_20.2.6.LTS/include" --reread_libs --diag_wrap=off --display_error_number --warn_sections --xml_link_info="Projektv1_linkInfo.xml" --rom_model -o "Projektv1.out" $(ORDERED_OBJS)
	@echo 'Finished building target: "$@"'
	@echo ' '

Projektv1.hex: $(EXE_OUTPUTS)
	@echo 'Building secondary target: "$@"'
	@echo 'Invoking: Arm Hex Utility'
	"C:/ti/ccs1110/ccs/tools/compiler/ti-cgt-arm_20.2.6.LTS/bin/armhex" --diag_wrap=off -o "Projektv1.hex" $(EXE_OUTPUTS__QUOTED)
	@echo 'Finished building secondary target: "$@"'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(BIN_OUTPUTS__QUOTED)$(EXE_OUTPUTS__QUOTED)
	-$(RM) "com.obj" "croutine.obj" "event_groups.obj" "heap_2.obj" "i2c.obj" "list.obj" "main.obj" "port.obj" "portasm.obj" "queue.obj" "startup_frt.obj" "status_led.obj" "stream_buffer.obj" "systick_frt.obj" "tasks.obj" "timers.obj" "uart0.obj" "driverlib\cpu.obj" "driverlib\gpio.obj" "driverlib\i2c.obj" "driverlib\interrupt.obj" "driverlib\sysctl.obj" "driverlib\uart.obj" "utils\uartstdio.obj" 
	-$(RM) "com.d" "croutine.d" "event_groups.d" "heap_2.d" "i2c.d" "list.d" "main.d" "port.d" "queue.d" "startup_frt.d" "status_led.d" "stream_buffer.d" "systick_frt.d" "tasks.d" "timers.d" "uart0.d" "driverlib\cpu.d" "driverlib\gpio.d" "driverlib\i2c.d" "driverlib\interrupt.d" "driverlib\sysctl.d" "driverlib\uart.d" "utils\uartstdio.d" 
	-$(RM) "portasm.d" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets


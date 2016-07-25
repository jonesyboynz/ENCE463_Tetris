################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := c:/ti/ccsv6/tools/compiler/arm_5.1.6

ORDERED_OBJS += \
$(GEN_CMDS__FLAG) \
"./buttons.obj" \
"./display.obj" \
"./game_engine.obj" \
"./images.obj" \
"./list.obj" \
"./main.obj" \
"./queue.obj" \
"./rit128x96x4.obj" \
"./startup_ccs.obj" \
"./tasks.obj" \
"./tetris_background.obj" \
"./tetrominoe.obj" \
"./portable/heap_2.obj" \
"./portable/port.obj" \
"./portable/portasm.obj" \
"./demo_code/basic_io.obj" \
"../lm3s1968.cmd" \
-l"libc.a" \
-l"P:\My Documents\2015\courses\ENCE361\StellarisWare\driverlib\ccs-cm3\Debug\driverlib-cm3.lib" \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include portable/subdir_vars.mk
-include demo_code/subdir_vars.mk
-include subdir_rules.mk
-include portable/subdir_rules.mk
-include demo_code/subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
ENCE463-Tetris.out \

EXE_OUTPUTS__QUOTED += \
"ENCE463-Tetris.out" \

BIN_OUTPUTS += \
ENCE463-Tetris.hex \

BIN_OUTPUTS__QUOTED += \
"ENCE463-Tetris.hex" \


# All Target
all: ENCE463-Tetris.out

# Tool invocations
ENCE463-Tetris.out: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@echo 'Building target: $@'
	@echo 'Invoking: ARM Linker'
	"c:/ti/ccsv6/tools/compiler/arm_5.1.6/bin/armcl" -mv7M3 --code_state=16 --abi=eabi -me -g --gcc --define="ccs" --define=PART_LM3S1968 --display_error_number --diag_warning=225 --diag_wrap=off -z -m"ENCE463-Tetris.map" --heap_size=0x800 --stack_size=0x800 -i"P:/My Documents/2015/courses/ENCE361/StellarisWare/driverlib/ccs-cm3/Debug/driverlib-cm3.lib" -i"c:/ti/ccsv6/tools/compiler/arm_5.1.6/lib" -i"c:/ti/ccsv6/tools/compiler/arm_5.1.6/include" --reread_libs --warn_sections --display_error_number --diag_wrap=off --xml_link_info="ENCE463-Tetris_linkInfo.xml" --rom_model -o "ENCE463-Tetris.out" $(ORDERED_OBJS)
	@echo 'Finished building target: $@'
	@echo ' '

ENCE463-Tetris.hex: $(EXE_OUTPUTS)
	@echo 'Invoking: ARM Hex Utility'
	"c:/ti/ccsv6/tools/compiler/arm_5.1.6/bin/armhex"  -o "ENCE463-Tetris.hex" $(EXE_OUTPUTS__QUOTED)
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(EXE_OUTPUTS__QUOTED)$(BIN_OUTPUTS__QUOTED)
	-$(RM) "buttons.pp" "display.pp" "game_engine.pp" "images.pp" "list.pp" "main.pp" "queue.pp" "rit128x96x4.pp" "startup_ccs.pp" "tasks.pp" "tetris_background.pp" "tetrominoe.pp" "portable\heap_2.pp" "portable\port.pp" "demo_code\basic_io.pp" 
	-$(RM) "buttons.obj" "display.obj" "game_engine.obj" "images.obj" "list.obj" "main.obj" "queue.obj" "rit128x96x4.obj" "startup_ccs.obj" "tasks.obj" "tetris_background.obj" "tetrominoe.obj" "portable\heap_2.obj" "portable\port.obj" "portable\portasm.obj" "demo_code\basic_io.obj" 
	-$(RM) "portable\portasm.pp" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets


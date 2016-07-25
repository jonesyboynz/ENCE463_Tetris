################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
buttons.obj: ../buttons.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"c:/ti/ccsv6/tools/compiler/arm_5.1.6/bin/armcl" -mv7M3 --code_state=16 --abi=eabi -me --include_path="c:/ti/ccsv6/tools/compiler/arm_5.1.6/include" --include_path="P:/My Documents/2015/courses/ENCE361/StellarisWare/driverlib" --include_path="P:/My Documents/2015/courses/ENCE361/StellarisWare" --include_path="P:/My Documents/2015/courses/ENCE361/StellarisWare/utils" --include_path="P:/My Documents/2015/courses/ENCE361/StellarisWare/boards/ek-lm3s1968" -g --gcc --define="ccs" --define=PART_LM3S1968 --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="buttons.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

display.obj: ../display.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"c:/ti/ccsv6/tools/compiler/arm_5.1.6/bin/armcl" -mv7M3 --code_state=16 --abi=eabi -me --include_path="c:/ti/ccsv6/tools/compiler/arm_5.1.6/include" --include_path="P:/My Documents/2015/courses/ENCE361/StellarisWare/driverlib" --include_path="P:/My Documents/2015/courses/ENCE361/StellarisWare" --include_path="P:/My Documents/2015/courses/ENCE361/StellarisWare/utils" --include_path="P:/My Documents/2015/courses/ENCE361/StellarisWare/boards/ek-lm3s1968" -g --gcc --define="ccs" --define=PART_LM3S1968 --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="display.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

game_engine.obj: ../game_engine.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"c:/ti/ccsv6/tools/compiler/arm_5.1.6/bin/armcl" -mv7M3 --code_state=16 --abi=eabi -me --include_path="c:/ti/ccsv6/tools/compiler/arm_5.1.6/include" --include_path="P:/My Documents/2015/courses/ENCE361/StellarisWare/driverlib" --include_path="P:/My Documents/2015/courses/ENCE361/StellarisWare" --include_path="P:/My Documents/2015/courses/ENCE361/StellarisWare/utils" --include_path="P:/My Documents/2015/courses/ENCE361/StellarisWare/boards/ek-lm3s1968" -g --gcc --define="ccs" --define=PART_LM3S1968 --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="game_engine.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

images.obj: ../images.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"c:/ti/ccsv6/tools/compiler/arm_5.1.6/bin/armcl" -mv7M3 --code_state=16 --abi=eabi -me --include_path="c:/ti/ccsv6/tools/compiler/arm_5.1.6/include" --include_path="P:/My Documents/2015/courses/ENCE361/StellarisWare/driverlib" --include_path="P:/My Documents/2015/courses/ENCE361/StellarisWare" --include_path="P:/My Documents/2015/courses/ENCE361/StellarisWare/utils" --include_path="P:/My Documents/2015/courses/ENCE361/StellarisWare/boards/ek-lm3s1968" -g --gcc --define="ccs" --define=PART_LM3S1968 --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="images.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

list.obj: ../list.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"c:/ti/ccsv6/tools/compiler/arm_5.1.6/bin/armcl" -mv7M3 --code_state=16 --abi=eabi -me --include_path="c:/ti/ccsv6/tools/compiler/arm_5.1.6/include" --include_path="P:/My Documents/2015/courses/ENCE361/StellarisWare/driverlib" --include_path="P:/My Documents/2015/courses/ENCE361/StellarisWare" --include_path="P:/My Documents/2015/courses/ENCE361/StellarisWare/utils" --include_path="P:/My Documents/2015/courses/ENCE361/StellarisWare/boards/ek-lm3s1968" -g --gcc --define="ccs" --define=PART_LM3S1968 --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="list.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

main.obj: ../main.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"c:/ti/ccsv6/tools/compiler/arm_5.1.6/bin/armcl" -mv7M3 --code_state=16 --abi=eabi -me --include_path="c:/ti/ccsv6/tools/compiler/arm_5.1.6/include" --include_path="P:/My Documents/2015/courses/ENCE361/StellarisWare/driverlib" --include_path="P:/My Documents/2015/courses/ENCE361/StellarisWare" --include_path="P:/My Documents/2015/courses/ENCE361/StellarisWare/utils" --include_path="P:/My Documents/2015/courses/ENCE361/StellarisWare/boards/ek-lm3s1968" -g --gcc --define="ccs" --define=PART_LM3S1968 --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="main.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

queue.obj: ../queue.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"c:/ti/ccsv6/tools/compiler/arm_5.1.6/bin/armcl" -mv7M3 --code_state=16 --abi=eabi -me --include_path="c:/ti/ccsv6/tools/compiler/arm_5.1.6/include" --include_path="P:/My Documents/2015/courses/ENCE361/StellarisWare/driverlib" --include_path="P:/My Documents/2015/courses/ENCE361/StellarisWare" --include_path="P:/My Documents/2015/courses/ENCE361/StellarisWare/utils" --include_path="P:/My Documents/2015/courses/ENCE361/StellarisWare/boards/ek-lm3s1968" -g --gcc --define="ccs" --define=PART_LM3S1968 --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="queue.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

rit128x96x4.obj: ../rit128x96x4.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"c:/ti/ccsv6/tools/compiler/arm_5.1.6/bin/armcl" -mv7M3 --code_state=16 --abi=eabi -me --include_path="c:/ti/ccsv6/tools/compiler/arm_5.1.6/include" --include_path="P:/My Documents/2015/courses/ENCE361/StellarisWare/driverlib" --include_path="P:/My Documents/2015/courses/ENCE361/StellarisWare" --include_path="P:/My Documents/2015/courses/ENCE361/StellarisWare/utils" --include_path="P:/My Documents/2015/courses/ENCE361/StellarisWare/boards/ek-lm3s1968" -g --gcc --define="ccs" --define=PART_LM3S1968 --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="rit128x96x4.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

startup_ccs.obj: ../startup_ccs.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"c:/ti/ccsv6/tools/compiler/arm_5.1.6/bin/armcl" -mv7M3 --code_state=16 --abi=eabi -me --include_path="c:/ti/ccsv6/tools/compiler/arm_5.1.6/include" --include_path="P:/My Documents/2015/courses/ENCE361/StellarisWare/driverlib" --include_path="P:/My Documents/2015/courses/ENCE361/StellarisWare" --include_path="P:/My Documents/2015/courses/ENCE361/StellarisWare/utils" --include_path="P:/My Documents/2015/courses/ENCE361/StellarisWare/boards/ek-lm3s1968" -g --gcc --define="ccs" --define=PART_LM3S1968 --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="startup_ccs.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

tasks.obj: ../tasks.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"c:/ti/ccsv6/tools/compiler/arm_5.1.6/bin/armcl" -mv7M3 --code_state=16 --abi=eabi -me --include_path="c:/ti/ccsv6/tools/compiler/arm_5.1.6/include" --include_path="P:/My Documents/2015/courses/ENCE361/StellarisWare/driverlib" --include_path="P:/My Documents/2015/courses/ENCE361/StellarisWare" --include_path="P:/My Documents/2015/courses/ENCE361/StellarisWare/utils" --include_path="P:/My Documents/2015/courses/ENCE361/StellarisWare/boards/ek-lm3s1968" -g --gcc --define="ccs" --define=PART_LM3S1968 --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="tasks.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

tetris_background.obj: ../tetris_background.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"c:/ti/ccsv6/tools/compiler/arm_5.1.6/bin/armcl" -mv7M3 --code_state=16 --abi=eabi -me --include_path="c:/ti/ccsv6/tools/compiler/arm_5.1.6/include" --include_path="P:/My Documents/2015/courses/ENCE361/StellarisWare/driverlib" --include_path="P:/My Documents/2015/courses/ENCE361/StellarisWare" --include_path="P:/My Documents/2015/courses/ENCE361/StellarisWare/utils" --include_path="P:/My Documents/2015/courses/ENCE361/StellarisWare/boards/ek-lm3s1968" -g --gcc --define="ccs" --define=PART_LM3S1968 --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="tetris_background.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

tetrominoe.obj: ../tetrominoe.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"c:/ti/ccsv6/tools/compiler/arm_5.1.6/bin/armcl" -mv7M3 --code_state=16 --abi=eabi -me --include_path="c:/ti/ccsv6/tools/compiler/arm_5.1.6/include" --include_path="P:/My Documents/2015/courses/ENCE361/StellarisWare/driverlib" --include_path="P:/My Documents/2015/courses/ENCE361/StellarisWare" --include_path="P:/My Documents/2015/courses/ENCE361/StellarisWare/utils" --include_path="P:/My Documents/2015/courses/ENCE361/StellarisWare/boards/ek-lm3s1968" -g --gcc --define="ccs" --define=PART_LM3S1968 --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="tetrominoe.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '



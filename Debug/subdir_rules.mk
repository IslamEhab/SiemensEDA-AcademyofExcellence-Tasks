################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
%.obj: ../%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccs930/ccs/tools/compiler/ti-cgt-arm_18.12.7.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="D:/Engineering/SiemensEDA_AcademyOfExcellence/Projects/CSS/UART_Task2" --include_path="D:/Engineering/SiemensEDA_AcademyOfExcellence/Projects/CSS/UART_Task2/Drivers/STD_and_Math" --include_path="D:/Engineering/SiemensEDA_AcademyOfExcellence/Projects/CSS/UART_Task2/Drivers/UART" --include_path="C:/ti/ccs930/ccs/tools/compiler/ti-cgt-arm_18.12.7.LTS/include" --define=ccs="ccs" --define=PART_TM4C123GH6PM -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '



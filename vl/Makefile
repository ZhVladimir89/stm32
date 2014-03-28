######## STM32VL MAKEFILE ########
TCPREFIX = arm-none-eabi-

CC = $(TCPREFIX)gcc
AS = $(TCPREFIX)gcc
LD = $(TCPREFIX)gcc
CP = $(TCPREFIX)objcopy
OD = $(TCPREFIX)objdump
GDBTUI = $(TCPREFIX)gdb -tui

STM32FLASH = ./stm32_flash.pl

ASM_FILES := $(wildcard src/*.s)
CXX_FILES := $(wildcard src/*.c)
OBJ_FILES := $(addprefix obj/,$(notdir $(CXX_FILES:.c=.o)))
OBJ_FILES += $(addprefix obj/,$(notdir $(ASM_FILES:.s=.o)))
INC_DIRS := inc
INC_DIRS := $(addprefix -I,$(INC_DIRS))
OUT_FILE := out/main
LD_FILE := stm32f100.ld

CFLAGS  =  -I. $(INC_DIRS) -O0 -g -Wall
CFLAGS += -mcpu=cortex-m3 -mthumb -mlittle-endian 
#-mthumb-interwork
CLAGS  += -DSTM32F10X_MD_VL=1 USE_STDPERIPH_DRIVER=1
#CFLAGS += -ffreestanding #-nostdlib
CFLAGS += --specs=rdimon.specs -lc -lrdimon
LFLAGS  = $(CFLAGS) -T$(LD_FILE)
CPFLAGS = -Obinary
ODFLAGS = -S

################################################################
## Colordefinition
################################################################
NO_COLOR        = \x1b[0m
GREEN_COLOR     = \x1b[32;01m
YELLOW_COLOR    = \x1b[33;01m
RED_COLOR       = \x1b[31;01m
WHITE_COLOR     = \x1b[37;01m

all: $(OUT_FILE).bin
#run

clean:
	@echo -e "$(WHITE_COLOR)>>> CLEANING$(NO_COLOR)"
	-rm -f main.lst obj/*.o out/*.elf out/*.lst out/*.bin

flash: $(OUT_FILE).bin
	@echo -e "$(WHITE_COLOR)>>> FLASHING$(NO_COLOR)"
	$(STM32FLASH) $^

$(OUT_FILE).bin: $(OUT_FILE).elf
	@echo -e "$(WHITE_COLOR)>>> COPYING$(NO_COLOR)"
	$(CP) $(CPFLAGS) $(OUT_FILE).elf $(OUT_FILE).bin
	$(CP) $(CPFLAGS) $(OUT_FILE).elf -O srec --srec-len 19 $(OUT_FILE).s19
	$(CP) $(CPFLAGS) $(OUT_FILE).elf -O ihex $(OUT_FILE).hex
#the .lst is an assembly listing - just here for educational purposes
	$(OD) $(ODFLAGS) $(OUT_FILE).elf> $(OUT_FILE).lst

$(OUT_FILE).elf: $(OBJ_FILES)
	@echo -e "$(WHITE_COLOR)>>> LINKING$(NO_COLOR)"
	$(LD) $(LFLAGS) -o $@ $^ -Wl,-Map,$(OUT_FILE).map

obj/%.o: src/%.c
	@echo -e "$(WHITE_COLOR)>>> COMPILING [C] $^$(NO_COLOR)"
	$(CC) -c $(CFLAGS) $< -o $@

obj/%.o: src/%.s
	@echo -e "$(WHITE_COLOR)>>> COMPILING [ASM] $^$(NO_COLOR)"
	$(AS) -c $(CFLAGS) $< -o $@

debug: $(OUT_FILE).elf
	@echo -e "$(WHITE_COLOR)>>> STARTING GDB$(NO_COLOR)"
	$(GDBTUI) $^
#	-ex "set remote hardware-breakpoint-limit 6" \
#	-ex "set remote hardware-watchpoint-limit 4"  $^


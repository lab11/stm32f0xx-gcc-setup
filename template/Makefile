#You shouldn't need to edit this file unless something is wrong
#This file assumes that the standard peripheral library is installed
#currently tested on V1.5 with limited test code

START_CODE ?= startup_stm32f0xx.s
SYSTEM_FILE ?= system_stm32f0xx.c

LIBRARY_PATHS += $(LIBRARY_START_PATH)Libraries/CMSIS/Device/ST/STM32F0xx/Include
LIBRARY_PATHS += $(LIBRARY_START_PATH)Libraries/CMSIS/Include
LIBRARY_PATHS += $(LIBRARY_START_PATH)Libraries/STM32F0xx_StdPeriph_Driver/inc/
LIBRARY_PATHS += ./


SOURCE_PATHS += $(TEMPLATE_PATH) 
SOURCE_PATHS += $(LIBRARY_START_PATH)Libraries/STM32F0xx_StdPeriph_Driver/src/
SOURCE_PATHS += $(LIBRARY_START_PATH)Libraries/CMSIS/Device/ST/STM32F0xx/Source/Templates


#Setup toolchain
##############################################################################
TOOLCHAIN_PREFIX ?= arm-none-eabi
AS = $(TOOLCHAIN_PATH)$(TOOLCHAIN_PREFIX)-as
CC = $(TOOLCHAIN_PATH)$(TOOLCHAIN_PREFIX)-gcc
LD = $(TOOLCHAIN_PATH)$(TOOLCHAIN_PREFIX)-gcc
OBJCOPY = $(TOOLCHAIN_PATH)$(TOOLCHAIN_PREFIX)-objcopy
OBJDUMP = $(TOOLCHAIN_PATH)$(TOOLCHAIN_PREFIX)-objdump
SIZE = $(TOOLCHAIN_PATH)$(TOOLCHAIN_PREFIX)-size
GDB = $(TOOLCHAIN_PATH)$(TOOLCHAIN_PREFIX)-gdb
###############################################################################

print-% : ; @echo $* = $($*)

LINKER_SCRIPT ?= stm32f0.ld
LINKER_SCRIPT_INCLUDES = $(TEMPLATE_PATH)ld
OUTPUT_NAME ?= $(PROJECT_NAME)

LIBRARY_INCLUDES = $(addprefix -I,$(LIBRARY_PATHS))
FILE_INCLUDES += ./stm32f0xx_conf.h

VPATH = $(SOURCE_PATHS)

OUTPUT_PATH = _build/

CPUFLAGS = -mthumb -mcpu=cortex-m0 -march=armv6-m
CFLAGS += -std=gnu99 -c $(CPUFLAGS) -nostdlib -Wall -D$(DEVICE) $(LIBRARY_INCLUDES) -include $(FILE_INCLUDES) -MD
LDFLAGS += $(CPUFLAGS) -L $(TEMPLATE_PATH) -L$(LINKER_SCRIPT_INCLUDES) -T $(LINKER_SCRIPT) -Wl,--gc-sections -Wl,-Map=$(OUTPUT_PATH)$(OUTPUT_NAME).Map

HEX = $(OUTPUT_PATH)$(OUTPUT_NAME).hex
ELF = $(OUTPUT_PATH)$(OUTPUT_NAME).elf
BIN = $(OUTPUT_PATH)$(OUTPUT_NAME).bin

SRCS = $(SYSTEM_FILE) $(notdir $(APPLICATION_SRCS))
OBJS = $(addprefix $(OUTPUT_PATH), $(SRCS:.c=.o)) $(addprefix $(OUTPUT_PATH),$(APPLICATION_LIBS))
DEPS = $(addprefix $(OUTPUT_PATH), $(SRCS:.c=.d))
SRCS_AS = $(START_CODE)
OBJS_AS = $(addprefix $(OUTPUT_PATH), $(SRCS_AS:.s=.os))

JLINK_OPTIONS = -if swd -device $(DEVICE) -speed 1000

all: $(OBJS) $(OBJS_AS) $(HEX)

debug: CFLAGS += -g
debug: $(OBJS) $(OBJS_AS) $(HEX)
 
rebuild: clean all

ifeq ($(OS),Windows_NT)
include $(TEMPLATE_PATH)Makefile.windows
else
include $(TEMPLATE_PATH)Makefile.posix
endif

$(HEX): $(OBJS) $(OBJS_AS)
	$(LD) $(LDFLAGS) $(OBJS_AS) $(OBJS) -o $(ELF)
	$(OBJCOPY) -Oihex $(ELF) $(HEX)
	$(OBJCOPY) -Obinary $(ELF) $(BIN)
	$(SIZE) $(ELF)

size: $(ELF)
	$(SIZE) $(ELF)

$(OUTPUT_PATH)%.o: %.c
	$(MAKE_BUILD_FOLDER)
	$(CC) $(LDFLAGS) $(CFLAGS) $< -o $@ 

$(OUTPUT_PATH)%.os: %.s
	$(MAKE_BUILD_FOLDER)
	$(AS) $< -o $@

-include $(DEPS)

.PHONY: all clean rebuild size
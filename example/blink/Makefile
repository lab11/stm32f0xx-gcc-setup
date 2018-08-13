PROJECT_NAME = $(shell basename "$(realpath ./)")

#List all of the application source files that need to be compiled
#############################################
APPLICATION_SRCS = $(notdir $(wildcard ./*.c))
APPLICATION_SRCS += stm32f0xx_gpio.c
APPLICATION_SRCS += stm32f0xx_rcc.c
APPLICATION_SRCS += SEGGER_RTT.c

#The exact STM part number All CAPS
############################################
DEVICE = STM32F091CC
DEVICE_FAMILY = STM32F091

#The install locations of the STM Standard library
#################################################
LIBRARY_START_PATH ?= ../../../sdk/stm32f0xx-1.5.0/

#The location of the gcc setup template
################################################
TEMPLATE_PATH ?= ../../template/

#Any places that you put custom header files
###############################################
LIBRARY_PATHS += ../../include

#Any places that you put custom source files
##############################################
SOURCE_PATHS += ../../source

ifndef LIBRARY_START_PATH
$(error An LIBRARY_START_PATH must be defined. Edit Makefile to define a valid LIBRARY_PATH)
endif

CFLAGS = -Os
GDB_PORT_NUMBER = 2331

include $(TEMPLATE_PATH)Makefile

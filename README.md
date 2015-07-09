This is a template to get started with the STM32F0xx series of chips using
a pure GCC and Makefile setup.

This is made to compile projects with the STM Standard Peripheral Library
and flash them using the JLink Segger Programmer over SWD. 

The following commands are supported:

Make:
	Builds program

Make debug:
	Builds program with debugging

Make flash:
	Flashes program to the STM32F0

Make erase-all:
	Erases flash

Make startdebug:
	Starts a JLinkGDBServer debug session

Note that the example Makefile must be modified to point to the Library
and Template paths on your system.


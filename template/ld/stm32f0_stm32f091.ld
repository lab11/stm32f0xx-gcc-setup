/*
Linker subscript for STM32F051 definitions with 256K Flash and 32K RAM
*/

/* Memory Spaces Definitions */

ENTRY(Reset_Handler)

MEMORY
{
  FLASH (rx) : ORIGIN = 0x08000000, LENGTH = 256K
  RAM  (xrw) : ORIGIN = 0x20000000, LENGTH = 32K
}

/* highest address of the user mode stack */
_estack = 0x20008000;
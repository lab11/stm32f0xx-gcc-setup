#include "stm32f0xx_gpio.h"
#include "stm32f0xx_rcc.h"
#include "SEGGER_RTT.h"
#include "SEGGER_RTT_Conf.h"

GPIO_InitTypeDef  GPIO_InitStructure;

/// Spin delay
void delay(int count)
{
    // volatile so that the compiler doesn't optimise it out
    volatile int i;

    for (i = 0; i < count; i++)
    {
    }
}

/// Main function.  Called by the startup code.
int main(void)
{
    /* GPIOB Periph clock enable */
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    // Initialized RTT
    SEGGER_RTT_Init();
    debug_msg("Initialized RTT, ready for further debugging...\r\n");

    /* LEDS
       Red:   GPIO_Pin_3
       Blue:  GPIO_Pin_4
       Green: GPIO_Pin_5

       1: LED off
       0: LED on (pull-down)

       Usage: BSRR: Bit Set/Reset register -> least significant 16 bits set, most significant 16 bits clear pins
              BRR:  Bit     Reset register -> least significant 16 bits reset
    */

    // Init all LEDs as off
    GPIOB->BSRR = GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5;

    for (;;)
    {
      const int DELAY_CYCLES = 2400000;

      // Turn on all LEDs, resulting in white light
      GPIOB->BRR = GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5;

      // Around 1/4 of a second
      delay(DELAY_CYCLES);

      // Turn off Blue and Green, turning LED Red
      GPIOB->BSRR = GPIO_Pin_4 | GPIO_Pin_5;

      delay(DELAY_CYCLES);

      // Turn off the Red and On the Blue LED
      GPIOB->BSRR  = GPIO_Pin_3;
      GPIOB->BRR = GPIO_Pin_4;

      delay(DELAY_CYCLES);

      // Turn off the Blue and On the Green LED
      GPIOB->BSRR  = GPIO_Pin_4;
      GPIOB->BRR = GPIO_Pin_5;

      delay(DELAY_CYCLES);

      // Turn off all LEDs
      GPIOB->BSRR = GPIO_Pin_5;

      delay(DELAY_CYCLES);
    }
}

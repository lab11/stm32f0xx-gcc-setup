#include "stm32f0xx_gpio.h"
#include "stm32f0xx_rcc.h"

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


    for (;;)
    {
      // Turn on all LEDs
      GPIOB->BSRR = GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5;

      // Around 1/4 of a second
      delay(2400000);

      // Turn off Blue and Green, turning LED Red
      GPIOB->BRR = GPIO_Pin_4 | GPIO_Pin_5;

      delay(2400000);

      // Turn off the Red and On the Blue LED
      GPIOB->BRR  = GPIO_Pin_3;
      GPIOB->BSRR = GPIO_Pin_4;

      delay(2400000);

      // Turn off the Blue and On the Green LED
      GPIOB->BRR  = GPIO_Pin_4;
      GPIOB->BSRR = GPIO_Pin_5;

      delay(2400000);

      // Turn off all LEDs
      GPIOB->BRR = GPIO_Pin_5;

      delay(2400000);
    }
}

/* Includes */
#include <stdint.h>
#include "main.h"
#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"

static void delay(void);

/* main C entry point - should never return */
void main(void)
{
    /* Enable peripheral clocks */
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;

    /* Configure pins */
    GPIOD->MODER &= ~GPIO_MODER_MODER13_1;
    GPIOD->MODER |= GPIO_MODER_MODER13_0;
    /* Speed mode configuration */
    GPIOD->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR13;
    /* Output mode configuration */
    GPIOD->OTYPER &= ~GPIO_OTYPER_OT_13;
    /* Pull-up Pull down resistor configuration*/
    GPIOD->PUPDR &= ~GPIO_PUPDR_PUPDR13;

    while (1)
    {
        static uint8_t led_val = 0;

        /* toggle the led */
        GPIOD->ODR = GPIO_Pin_13;

        /* wait a bit */
        delay();
    }
}

static void delay(void)
{

}

#include "stdint.h"
#include "stdio.h"
#include "stdlib.h"
#include "pwm.h"
#include "led_demo.h"

#include "../../libopencm3/stm32/rcc.h"
#include "../../libopencm3/stm32/gpio.h"
#include "../../libopencm3/stm32/timer.h"

/* Defines */
#define EVER           (;;)

/* Prototypes */
void clock_init(void);
void gpio_init(void);
void delay(int d);

extern void initialise_monitor_handles(void);

int led_main(void)
{
    clock_init();
    gpio_init();
    servo_init();

    initialise_monitor_handles();


    for EVER
    {
        /*
        cycleLed(1,0,0);
        cycleLed(1,1,0);
        cycleLed(0,1,0);
        cycleLed(0,1,1);
        cycleLed(0,0,1);
        cycleLed(1,0,1);
        cycleLed(1,1,1);
        */

        cycleLedOn(1,0,0);
        cycleLedOn(0,1,0);
        cycleLedOn(0,0,1);
        cycleLedOff(1,0,0);
        cycleLedOff(0,1,0);
        cycleLedOff(0,0,1);

        cycleLedOn(0,1,0);
        cycleLedOn(0,0,1);
        cycleLedOn(1,0,0);
        cycleLedOff(0,1,0);
        cycleLedOff(0,0,1);
        cycleLedOff(1,0,0);

        cycleLedOn(0,0,1);
        cycleLedOn(1,0,0);
        cycleLedOn(0,1,0);
        cycleLedOff(0,0,1);
        cycleLedOff(1,0,0);
        cycleLedOff(0,1,0);
    }
  return 0;
}

int cycleLed(int OC2_ONOFF, int OC3_ONOFF, int OC4_ONOFF){
    int i = 0;

    for (i = 0; i < PWM_PERIOD; i++){
        delay(150);
        if (OC2_ONOFF)
            pwm_set_pulse_width(TIM2, TIM_OC2, i);
        if (OC3_ONOFF)
            pwm_set_pulse_width(TIM2, TIM_OC3, i);
        if (OC4_ONOFF)
            pwm_set_pulse_width(TIM2, TIM_OC4, i);
    }
    for (i = PWM_PERIOD; i > 0; i--){
        delay(150);
        if (OC2_ONOFF)
            pwm_set_pulse_width(TIM2, TIM_OC2, i);
        if (OC3_ONOFF)
            pwm_set_pulse_width(TIM2, TIM_OC3, i);
        if (OC4_ONOFF)
            pwm_set_pulse_width(TIM2, TIM_OC4, i);
    }
    return 0;
}

int cycleLedOn(int OC2_ON, int OC3_ON, int OC4_ON){
    int i = 0;
    for (i = 0; i < PWM_PERIOD; i++){
        delay(150);
        if (OC2_ON)
            pwm_set_pulse_width(TIM2, TIM_OC2, i);
        if (OC3_ON)
            pwm_set_pulse_width(TIM2, TIM_OC3, i);
        if (OC4_ON)
            pwm_set_pulse_width(TIM2, TIM_OC4, i);
    }
    return 0;
}

int cycleLedOff(int OC2_OFF, int OC3_OFF, int OC4_OFF){
    int i = 0;
    for (i = PWM_PERIOD; i > 0; i--){
        delay(150);
        if (OC2_OFF)
            pwm_set_pulse_width(TIM2, TIM_OC2, i);
        if (OC3_OFF)
            pwm_set_pulse_width(TIM2, TIM_OC3, i);
        if (OC4_OFF)
            pwm_set_pulse_width(TIM2, TIM_OC4, i);
    }
    return 0;
}

void clock_init(void)
{
    void rcc_clock_setup_in_hse_8mhz_out_24mhz(void);
}

/**
* Initialize the GPIO port for the LED at pin 12 on port C.
*/
void gpio_init(void)
{
    /* enable GPIOC clock */
    rcc_peripheral_enable_clock(&RCC_APB2ENR, RCC_APB2ENR_IOPCEN);

    /*
* set GPIO12 at PORTC (led) to 'output alternate function push-pull'.
*/
    gpio_set_mode(GPIOC, GPIO_MODE_OUTPUT_50_MHZ, GPIO_CNF_OUTPUT_PUSHPULL, GPIO12);
}

/**
* Delay by executing some "nop"s.
*
* @param[in] d number of "nop"s to performe.
*/
void delay(int d)
{
    int i;
    for(i = 0; i < d; i++) {
        __asm("nop");
    }
}

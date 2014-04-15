#include "main.h"
#include "stdint.h"
#include "stdio.h"
#include "stdlib.h"


#include "../../libopencm3/stm32/rcc.h"
#include "../../libopencm3/stm32/gpio.h"
#include "../../libopencm3/stm32/timer.h"

/* Defines */
#define EVER           (;;)
/**
* Prescale 72000000 Hz system clock by 72 = 1000000 Hz.
*/
#define PWM_PRESCALE (7)

/**
* We need a 50 Hz period (1000 / 20ms = 50), thus devide 100000 by 50 = 20000 (us).
*/
#define PWM_PERIOD (2000)

/**
* Max. pos. at 2050 us (2.00ms).
*/
#define SERVO_MAX (19000)

/**
* Min. pos. at 950 us (0.95ms).
*/
#define SERVO_MIN (10)

/**
* Middle pos. at 1580 us (1.58ms).
*/
#define SERVO_NULL (10000)

/**
* TIM2 channel for servo 1.
*
* Changing this also requires to change settings in {@link servo_init}!
*/
#define SERVO_CH1 TIM_OC2

/**
* TIM2 channel for servo 2.
*
* Changing this also requires to change settings in {@link servo_init}!
*/
#define SERVO_CH2 TIM_OC3

#define SERVO_CH3 TIM_OC4

/* Prototypes */
int main(void);
void clock_init(void);
void gpio_init(void);
void delay(int d);
void pwm_init_timer(volatile uint32_t *reg, uint32_t en, uint32_t timer_peripheral, uint32_t prescaler, uint32_t period);
void pwm_init_output_channel(uint32_t timer_peripheral, enum tim_oc_id oc_id,
                             volatile uint32_t *gpio_reg, uint32_t gpio_en, uint32_t gpio_port, uint16_t gpio_pin);
void pwm_set_pulse_width(uint32_t timer_peripheral, enum tim_oc_id oc_id, uint32_t pulse_width);
void pwm_start_timer(uint32_t timer_peripheral);
void servo_init(void);
void servo_set_position(enum tim_oc_id ch, uint32_t pos_us);

extern void initialise_monitor_handles(void);

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

}

extern void initialise_monitor_handles(void);

int main(void)
{
    int state = 0;
    int i = 0;
    int j = PWM_PERIOD;
    clock_init();
    gpio_init();
    servo_init();

    initialise_monitor_handles();

    printf("Hello World\n");

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
}


void __end__ (void){

}

//void _exit(void){}

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


void pwm_init_timer(volatile uint32_t *reg, uint32_t en, uint32_t timer_peripheral, uint32_t prescaler, uint32_t period)
{
    /* Enable timer clock. */
    rcc_peripheral_enable_clock(reg, en);

    /* Reset TIM1 peripheral */
    timer_reset(timer_peripheral);

    /* Set the timers global mode to:
* - use no divider
* - alignment edge
* - count direction up
*/
    timer_set_mode(timer_peripheral,
                   TIM_CR1_CKD_CK_INT,
                   TIM_CR1_CMS_EDGE,
                   TIM_CR1_DIR_UP);

    timer_set_prescaler(timer_peripheral, prescaler);
    timer_set_repetition_counter(timer_peripheral, 0);
    timer_enable_preload(timer_peripheral);
    timer_continuous_mode(timer_peripheral);
    timer_set_period(timer_peripheral, period);
}

void pwm_init_output_channel(uint32_t timer_peripheral, enum tim_oc_id oc_id, volatile uint32_t *gpio_reg, uint32_t gpio_en, uint32_t gpio_port, uint16_t gpio_pin)
{
    /* Enable GPIO clock. */
    rcc_peripheral_enable_clock(gpio_reg, gpio_en);

    /* Set timer channel to output */
    gpio_set_mode(gpio_port, GPIO_MODE_OUTPUT_50_MHZ,
                  GPIO_CNF_OUTPUT_ALTFN_PUSHPULL,
                  gpio_pin);

    timer_disable_oc_output(timer_peripheral, oc_id);
    timer_set_oc_mode(timer_peripheral, oc_id, TIM_OCM_PWM1);
    timer_set_oc_value(timer_peripheral, oc_id, 0);
    timer_enable_oc_output(timer_peripheral, oc_id);
}

void pwm_set_pulse_width(uint32_t timer_peripheral, enum tim_oc_id oc_id, uint32_t pulse_width)
{
    timer_set_oc_value(timer_peripheral, oc_id, pulse_width);
}

void pwm_start_timer(uint32_t timer_peripheral)
{
    timer_enable_counter(timer_peripheral);
}

void servo_init(void)
{
    /* init timer2 with a period of 20ms */
    pwm_init_timer(&RCC_APB1ENR, RCC_APB1ENR_TIM2EN, TIM2, PWM_PRESCALE, PWM_PERIOD);

    /* init output of channel2 of timer2 */
    pwm_init_output_channel(TIM2, SERVO_CH1, &RCC_APB2ENR, RCC_APB2ENR_IOPAEN, GPIOA, GPIO_TIM2_CH2);

    /* init output of channel3 of timer2 */
    pwm_init_output_channel(TIM2, SERVO_CH2, &RCC_APB2ENR, RCC_APB2ENR_IOPAEN, GPIOA, GPIO_TIM2_CH3);

    /* init output of channel 4 of timer2 */
    pwm_init_output_channel(TIM2, SERVO_CH3, &RCC_APB2ENR, RCC_APB2ENR_IOPAEN, GPIOA, GPIO_TIM2_CH4);

    pwm_set_pulse_width(TIM2, SERVO_CH1, 0);
    pwm_set_pulse_width(TIM2, SERVO_CH2, 0);
    pwm_set_pulse_width(TIM2, SERVO_CH3, 0);

    /* start timer1 */
    pwm_start_timer(TIM2);
}

void servo_set_position(enum tim_oc_id ch, uint32_t pos_us)
{
    pwm_set_pulse_width(TIM2, ch, pos_us);
}

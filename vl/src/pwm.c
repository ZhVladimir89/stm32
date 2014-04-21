/*
 *  pwm.c
 *
 *  Created on 16.4.2014
 *    Author: Michiel Jordens
 */

#include "pwm.h"
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


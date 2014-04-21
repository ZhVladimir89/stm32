/*
 *  pwm.h
 *
 *  Created on 16.4.2014
 *    Author: Michiel Jordens
 */
#ifndef PWM_H_
#define PWM_H_

#include "../../libopencm3/stm32/rcc.h"
#include "../../libopencm3/stm32/gpio.h"
#include "../../libopencm3/stm32/timer.h"
#include "stdint.h"
#include "stdio.h"
#include "stdlib.h"
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


void pwm_init_timer(volatile uint32_t *reg, uint32_t en, uint32_t timer_peripheral, uint32_t prescaler, uint32_t period);
void pwm_init_output_channel(uint32_t timer_peripheral, enum tim_oc_id oc_id,
                             volatile uint32_t *gpio_reg, uint32_t gpio_en, uint32_t gpio_port, uint16_t gpio_pin);
void pwm_set_pulse_width(uint32_t timer_peripheral, enum tim_oc_id oc_id, uint32_t pulse_width);
void pwm_start_timer(uint32_t timer_peripheral);
void servo_init(void);
void servo_set_position(enum tim_oc_id ch, uint32_t pos_us);


int cycleLed(int OC2_ONOFF, int OC3_ONOFF, int OC4_ONOFF);
int cycleLedOn(int OC2_ON, int OC3_ON, int OC4_ON);
int cycleLedOff(int OC2_OFF, int OC3_OFF, int OC4_OFF);
#endif

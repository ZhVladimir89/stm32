#include "led_demo.h"
#include "pwm.h"
#include "../../libopencm3/stm32/rcc.h"
#include "../../libopencm3/include/libopencm3/stm32/f1/gpio.h"
#include "../../libopencm3/stm32/timer.h"

void GPIO_setup(void);

int main(void)
{
    uint32_t time[50] = {0};

    uint16_t ir_val = 1;
    uint16_t prev_ir_val = 1;
    int i = 0;
    GPIO_setup();
    rcc_clock_setup_in_hse_12mhz_out_72mhz();
    /*rcc_clock_setup_in_hse_8mhz_out_24mhz();*/
    pwm_init_timer(&RCC_APB1ENR, RCC_APB1ENR_TIM2EN, TIM2, 1000, 10000000);
    pwm_start_timer(TIM2);

    while(1)
    {

        /* clear time array */
        printf("finished printing, now clearing\n");
        for (i = 0; i<50;i++)
        {
            time[i] = 0;
        }

        printf("finished cleared, now reading\n");
        i = 0;
        while ( i < 50 )
        {
           ir_val = gpio_get(GPIOC,GPIO12);
            if (ir_val != prev_ir_val)
            {
                if ( i == 0 )
                {
                    timer_set_counter(TIM2,0);
                }
                time[i]=timer_get_counter(TIM2);
                timer_set_counter(TIM2,0);
                i++;
            }
            prev_ir_val = ir_val;
        }

        printf("finished reading now printing\n");
        for (i = 0; i<50;i++)
        {
            printf("%d\n",time[i]);
        }

    }

    return 0;
}


void GPIO_setup(void)
{
    /* Enable clock for port C */
    rcc_peripheral_enable_clock(&RCC_APB2ENR, RCC_APB2ENR_IOPCEN);

    /* set GPIO12 at PORTC (led) to 'output alternate function push-pull' */
    gpio_set_mode(GPIOC, GPIO_MODE_INPUT, GPIO_CNF_INPUT_FLOAT, GPIO12);
}

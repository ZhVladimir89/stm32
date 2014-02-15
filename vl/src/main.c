#include "stm32f10x.h"
#include "main.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_tim.h"
#include "stm32f10x_rcc.h"

#define LEDG            GPIO_Pin_9
#define LEDB            GPIO_Pin_8
#define LEDPORT         GPIOC
#define LEDPORTCLK      RCC_APB2Periph_GPIOC
#define BUTTON          GPIO_Pin_0
#define BUTTONPORT      GPIOA
#define BUTTONPORTCLK   RCC_APB2Periph_GPIOA

/* Defines */
#define EVER        (;;)

/* Prototypes */
int main(void);


void TIM2_IRQHandler(void);
void INTTIM_Config(void);

/* main C entry point */
int main(void)
{
    //GPIO_InitTypeDef GPIO_InitStructure;
    int i=0;

    //RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;

    //TODO test
    /*-------------------------- GPIO Configuration ----------------------------*/
    /* GPIOD Configuration: Pins 12, 13, 14 and 15 in output push-pull          */
    //GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
    //GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    //GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    //GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    //GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    //GPIO_Init(GPIOD, &GPIO_InitStructure);

    //GPIO_ToggleBits(GPIOD, GPIO_Pin_13 | GPIO_Pin_15);

    //INTTIM_Config();

    // PC 8 en 9 zijn de leds

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    GPIO_InitTypeDef GPIO_INIT_C;
    GPIO_INIT_C.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
    GPIO_INIT_C.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_INIT_C.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(GPIOC,&GPIO_INIT_C);
    GPIO_SetBits(LEDPORT,LEDG | LEDB);





    for EVER
    {
        i++;
    }
}

//void TIM2_IRQHandler(void)
//{
//    if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
//    {
//        TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
//        GPIO_ToggleBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
//    }
//}

//void INTTIM_Config(void)
//{
//    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    
//    NVIC_InitTypeDef NVIC_InitStructure;
//    /* Enable the TIM2 global Interrupt */
//    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
//    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
//    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
//    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//    NVIC_Init(&NVIC_InitStructure);
     
//    /* TIM2 clock enable */
//    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
//    /* Time base configuration */
//    TIM_TimeBaseStructure.TIM_Period = 200 - 1;
//    TIM_TimeBaseStructure.TIM_Prescaler = 48000 - 1;
//    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
//    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
//    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
//    /* TIM IT enable */
//    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
//    /* TIM2 enable counter */
//    TIM_Cmd(TIM2, ENABLE);
//}


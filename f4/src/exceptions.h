
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _EXCEPTIONS_H_
#define _EXCEPTIONS_H_

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"

/* Exported functions ------------------------------------------------------- */
void NMI_Handler(void);
void HardFault_Handler(void);
void MemManage_Handler(void);
void BusFault_Handler(void);
void UsageFault_Handler(void);
void SVC_Handler(void);
void DebugMon_Handler(void);
void PendSV_Handler(void);
void SysTick_Handler(void);

uint32_t __stm32_tick;

#endif /* _EXCEPTIONS_H_ */


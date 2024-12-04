#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f1xx_hal.h"

void Error_Handler(void);
#define TRANSMIT_LED_Pin GPIO_PIN_2
#define TRANSMIT_LED_GPIO_Port GPIOA
#define LOCK_PIN_Pin GPIO_PIN_3
#define LOCK_PIN_GPIO_Port GPIOA

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */


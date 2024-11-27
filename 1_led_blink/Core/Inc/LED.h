/*
 * LED.h
 *
 *  Created on: Aug 18, 2023
 *      Author: sezai
 */

#ifndef INC_LED_H_
#define INC_LED_H_

#define LED1_PORT     GPIOD
#define LED1_PIN      GPIO_PIN_13

#define LED2_PORT     GPIOD
#define LED2_PIN      GPIO_PIN_12

#define LED3_PORT     GPIOD
#define LED3_PIN      GPIO_PIN_14

#define LED4_PORT     GPIOD
#define LED4_PIN      GPIO_PIN_15

#define LED1_ON       HAL_GPIO_WritePin(LED1_PORT, LED1_PIN, GPIO_PIN_SET)
#define LED2_ON       HAL_GPIO_WritePin(LED2_PORT, LED2_PIN, GPIO_PIN_SET)
#define LED3_ON       HAL_GPIO_WritePin(LED3_PORT, LED3_PIN, GPIO_PIN_SET)
#define LED4_ON       HAL_GPIO_WritePin(LED4_PORT, LED4_PIN, GPIO_PIN_SET)

#define LED1_OFF      HAL_GPIO_WritePin(LED1_PORT, LED1_PIN, GPIO_PIN_RESET)
#define LED2_OFF      HAL_GPIO_WritePin(LED2_PORT, LED2_PIN, GPIO_PIN_RESET)
#define LED3_OFF      HAL_GPIO_WritePin(LED3_PORT, LED3_PIN, GPIO_PIN_RESET)
#define LED4_OFF      HAL_GPIO_WritePin(LED4_PORT, LED4_PIN, GPIO_PIN_RESET)

#define LED1_TOGGLE   HAL_GPIO_TogglePin(LED1_PORT, LED1_PIN)
#define LED2_TOGGLE   HAL_GPIO_TogglePin(LED2_PORT, LED2_PIN)
#define LED3_TOGGLE   HAL_GPIO_TogglePin(LED3_PORT, LED3_PIN)
#define LED4_TOGGLE   HAL_GPIO_TogglePin(LED4_PORT, LED4_PIN)






#endif /* INC_LED_H_ */

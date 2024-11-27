/*
 * UART.h
 *
 *  Created on: Aug 24, 2023
 *      Author: sezai
 */

#ifndef UART_H_
#define UART_H_

#define led1	GPIO_PIN_12
#define led2	GPIO_PIN_13
#define led3	GPIO_PIN_14
#define led4	GPIO_PIN_15

#define port	GPIOD
#define SET		GPIO_PIN_SET
#define RESET	GPIO_PIN_RESET

#define led1_on		HAL_GPIO_WritePin(port, led1, SET);
#define leds_off1	HAL_GPIO_WritePin(port, led2 | led3  | led4, RESET);



#define led2_on		HAL_GPIO_WritePin(port, led2, SET);
#define leds_off2	HAL_GPIO_WritePin(port, led1 | led3  | led4, RESET);

#define led3_on		HAL_GPIO_WritePin(port, led3, SET);
#define leds_off3	HAL_GPIO_WritePin(port, led1 | led2  | led4, RESET);

#define led4_on		HAL_GPIO_WritePin(port, led4, SET);
#define leds_off4	HAL_GPIO_WritePin(port, led1 | led2  | led3, RESET);


#endif /* UART_H_ */

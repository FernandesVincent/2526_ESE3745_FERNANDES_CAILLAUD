__/*
 * motor.c
 *
 *  Created on: Nov 11, 2025
 *      Author: nicolas
 */

#include "motor_control/motor.h"
#include "stm32g4xx_hal_tim.h"
#include "stm32g4xx_hal_gpio.h"


void basic_PWM(void){
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);
	HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_1);
	HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_2);
}

int speed_init(){
	return shell_add(&hshell1, "speed", speed_control, "Control speed");
}

int speed_control(h_shell_t* h_shell, int argc, char** argv){
;
}

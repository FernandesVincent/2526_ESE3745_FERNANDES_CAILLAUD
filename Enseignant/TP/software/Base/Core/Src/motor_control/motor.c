/*
 * motor.c
 *
 *  Created on: Nov 11, 2025
 *      Author: nicolas
 */

#include "motor_control/motor.h"
#include "tim.h"
#include "stm32g4xx_hal_tim.h"
#include "user_interface/shell.h"

int MAX_PWM = 17000;

void PWM_init(void){
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);
	HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_1);
	HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_2);

	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 0.3*16998);
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 0.3*16998);

}

void SET_PWM(h_shell_t* h_shell, int argc, char** argv)
{
	int size;

	if(argc!=2){
			size = snprintf(h_shell->print_buffer, SHELL_PRINT_BUFFER_SIZE, "Need 2 arguments : motor value\r\n");
			h_shell->drv.transmit(h_shell->print_buffer, size);
			return HAL_ERROR;
		}
	if (atoi(argv[1]) > 100)
	{
		size = snprintf(h_shell->print_buffer, SHELL_PRINT_BUFFER_SIZE, "The PWM has to be between 0 and 100% \r\n");
		h_shell->drv.transmit(h_shell->print_buffer, size);
		return HAL_ERROR;
	}

	else
	{
		int PWM =(int) (atoi(argv[1]) * MAX_PWM / 100.0);
		if (PWM > MAX_PWM || PWM < 0)
			{
				while(1);
			}
		else
			{
				__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1,(int) PWM);
				__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2,(int) MAX_PWM - PWM);
				size = snprintf(h_shell->print_buffer, SHELL_PRINT_BUFFER_SIZE, "The PWM has been set at %d %\r\n",PWM);
				h_shell->drv.transmit(h_shell->print_buffer, size);
				return HAL_ERROR;
			}
	}
}

void ccr_init(){
	return shell_add(&hshell1, "SETCCR", SET_PWM, "SET PWM MOTOR");
}

void update_PWM_ramp(void){
    if(current_PWM < target_PWM){
        current_PWM += PWM_STEP;
        if(current_PWM > target_PWM) current_PWM = target_PWM;
    }
    else if(current_PWM > target_PWM){
        current_PWM -= PWM_STEP;
        if(current_PWM < target_PWM) current_PWM = target_PWM;
    }
    else{
        return; // rien à faire
    }

    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, current_PWM);
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, MAX_PWM - current_PWM);
}


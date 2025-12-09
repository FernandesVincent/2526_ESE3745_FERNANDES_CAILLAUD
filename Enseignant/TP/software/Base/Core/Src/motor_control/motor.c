/*
 * motor.c
 *
 *  Created on: Nov 11, 2025
 *      Author: nicolas
 */

#include "motor_control/motor.h"
#include "stm32g4xx_hal_tim.h"
#include "tim.h"
#include "user_interface/shell.h"

int MAX_PWM = 17000-2;

void PWM_init(void) {

	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);
	HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_1);
	HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_2);

	uint32_t pwm_value = (uint32_t)(0.5f * MAX_PWM);

	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, pwm_value);
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, MAX_PWM - pwm_value);
}

void PWM_stop(void){
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 0);
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 0);

	HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_1);
	HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_2);
	HAL_TIMEx_PWMN_Stop(&htim1, TIM_CHANNEL_1);
	HAL_TIMEx_PWMN_Stop(&htim1, TIM_CHANNEL_2);
}

static int old_PWM = 5800;

int SET_PWM(h_shell_t *h_shell, int argc, char **argv) {

	int size;

	if (argc != 2) {
			size = snprintf(h_shell->print_buffer, SHELL_PRINT_BUFFER_SIZE, "Need 2 arguments : motor value\r\n");
			h_shell->drv.transmit(h_shell->print_buffer, size);
			return 1;
	}

	int percent = atoi(argv[1]);
	if (percent < 0 || percent > 100) {
			size = snprintf(h_shell->print_buffer, SHELL_PRINT_BUFFER_SIZE,"The PWM has to be between 0 and 100\r\n");
			h_shell->drv.transmit(h_shell->print_buffer, size);
			return 1;
	}

	int PWM = (int)(percent * MAX_PWM / 100.0);

	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, PWM);
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, MAX_PWM - PWM);

	old_PWM = PWM;

	size = snprintf(h_shell->print_buffer, SHELL_PRINT_BUFFER_SIZE,"The PWM has been set to %d\r\n", PWM);
	h_shell->drv.transmit(h_shell->print_buffer, size);

	return 0;
}


int ccr_init() {
  return shell_add(&hshell1, "SETCCR", SET_PWM, "SET PWM MOTOR");
}

void update_PWM_ramp(int current_PWM, int target_PWM){

	const int PWM_STEP = MAX_PWM / 100; 
	const int DELAY_MS = 2;          

	while (current_PWM != target_PWM)
	{
			if (current_PWM < target_PWM)
					current_PWM = MIN(current_PWM + PWM_STEP, target_PWM);
			else
					current_PWM = MAX(current_PWM - PWM_STEP, target_PWM);

			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, current_PWM);
			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, MAX_PWM - current_PWM);

			HAL_Delay(DELAY_MS);
	}
}


int start(h_shell_t *h_shell, int argc, char **argv){

  int size;
  if (argc != 1) {
    size = snprintf(h_shell->print_buffer, SHELL_PRINT_BUFFER_SIZE,"Need 1 argument : start\r\n");
    h_shell->drv.transmit(h_shell->print_buffer, size);
    return HAL_ERROR;
  }

  else{
		PWM_init();
		size = snprintf(h_shell->print_buffer, SHELL_PRINT_BUFFER_SIZE,"All PWMs started with a duty cycle of 50 percent. \r\n");
		h_shell->drv.transmit(h_shell->print_buffer, size);
		return 0;
	}
}

int stop(h_shell_t *h_shell, int argc, char **argv){

  int size;
  if (argc != 1) {
    size = snprintf(h_shell->print_buffer, SHELL_PRINT_BUFFER_SIZE,"Need 1 argument : stop\r\n");
    h_shell->drv.transmit(h_shell->print_buffer, size);
    return HAL_ERROR;
  }

  else{
		PWM_stop();
		size = snprintf(h_shell->print_buffer, SHELL_PRINT_BUFFER_SIZE,"All PWMs stopped. \r\n");
		h_shell->drv.transmit(h_shell->print_buffer, size);
		return 0;
	}
}

int SET_speed(h_shell_t *h_shell, int argc, char **argv){
	int size;

	if (argc != 2) {
			size = snprintf(h_shell->print_buffer, SHELL_PRINT_BUFFER_SIZE,"Need 2 arguments : motor value\r\n");
			h_shell->drv.transmit(h_shell->print_buffer, size);
			return 1;
	}

	int percent = atoi(argv[1]);
	if (percent < 0 || percent > 100) {
			size = snprintf(h_shell->print_buffer, SHELL_PRINT_BUFFER_SIZE,"The PWM has to be between 0 and 100\r\n");
			h_shell->drv.transmit(h_shell->print_buffer, size);
			return 1;
	}

	int target_PWM = (int)(percent * MAX_PWM / 100.0);
	update_PWM_ramp(old_PWM, target_PWM);

	old_PWM = target_PWM;

	size = snprintf(h_shell->print_buffer, SHELL_PRINT_BUFFER_SIZE,"The PWM has been ramped to %d\r\n", target_PWM);
	h_shell->drv.transmit(h_shell->print_buffer, size);

	return 0;
}

int start_init() {
  return shell_add(&hshell1, "start", start, "Start all PWMs with a duty cycle of 50 percent");
}
int stop_init() {
  return shell_add(&hshell1, "stop", stop, "Stop all PWMs");
}
int set_speed_init() {
  return shell_add(&hshell1, "speed", SET_speed, "SET PWM MOTOR with a ramp");
}
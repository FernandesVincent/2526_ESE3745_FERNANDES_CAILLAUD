/*
 * motor.h
 *
 *  Created on: Nov 11, 2025
 *      Author: nicolas
 */

#ifndef INC_MOTOR_CONTROL_MOTOR_H_
#define INC_MOTOR_CONTROL_MOTOR_H_

#include "user_interface/shell.h"

void PWM_init(void);
void PWM_stop(void);
int SET_PWM(h_shell_t *h_shell, int argc, char **argv);
int ccr_init();
void update_PWM_ramp(int current_PWM, int target_PWM);
int start(h_shell_t *h_shell, int argc, char **argv);
int stop(h_shell_t *h_shell, int argc, char **argv);
int SET_speed(h_shell_t *h_shell, int argc, char **argv);
int start_init();
int stop_init();
int set_speed_init();

#endif /* INC_MOTOR_CONTROL_MOTOR_H_ */

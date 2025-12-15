/*
 * input_analog.h
 *
 *  Created on: Nov 11, 2025
 *      Author: nicolas
 */

#ifndef INC_INPUT_ANALOG_H_
#define INC_INPUT_ANALOG_H_

#include "user_interface/shell.h"

void input_analog_init(void);
void ADC_Process_DMA_Conversion(void);
static int sh_get_current(h_shell_t* h_shell, int argc, char** argv);
int init_Imes(void);

#endif /* INC_INPUT_ANALOG_H_ */

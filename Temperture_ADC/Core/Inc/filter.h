/*
 * filter.h
 *
 *  Created on: Feb 6, 2023
 *      Author: NPEDU001
 */

#ifndef INC_FILTER_H_
#define INC_FILTER_H_

#include "main.h"

uint16_t AvgFilter(uint16_t inData);
double kalman(double measurement);

#endif /* INC_FILTER_H_ */

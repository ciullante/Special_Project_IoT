/*
 * DS18B20.h
 *
 *  Created on: 11 mag 2023
 *      Author: aless
 */

#ifndef DS18B20_H_
#define DS18B20_H_

#include <stdio.h>
#include <stdlib.h>
#include "onewire.h"
#include "DS18B20.h"
#include "Ifx_Types.h"

void broadcastConvert(void);
float32 getTemperature(void);
int getTemperatureInt(void);
void printSingleAddress(void);


#endif /* DS18B20_H_ */

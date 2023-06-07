/*
 * onewire.h
 *
 *  Created on: 11 mag 2023
 *      Author: aless
 */

#ifndef ONEWIRE_H_
#define ONEWIRE_H_

#define _XTAL_FREQ 8000000

//onewirePin defines
#define onewirePin PORTAbits.RA6
#define onewirePinDirection TRISAbits.TRISA6 //0 = output, 1 = input

void onewireWriteBit(int b);
unsigned char onewireReadBit(void);
unsigned char onewireInit(void);
unsigned char onewireReadByte(void);
void onewireWriteByte(char data);
unsigned char onewireCRC(unsigned char* addr, unsigned char len);

int onewire_getPin(void);



#endif /* ONEWIRE_H_ */

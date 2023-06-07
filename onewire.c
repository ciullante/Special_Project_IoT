/*
 * sensor.c
 *
 *  Created on: 11 mag 2023
 *      Author: aless
 */
#include "IfxPort.h"
#include "onewire.h"
#include "Bsp.h"

#define PORT IfxPort_P33_10


void onewire_setPinModeOutput(){
    IfxPort_setPinModeOutput(&MODULE_P33, 10, IfxPort_Mode_outputOpenDrainGeneral, IfxPort_OutputIdx_general);
}

void onewire_setPinModeInput(){
    IfxPort_setPinModeInput(&MODULE_P33, 10, IfxPort_Mode_inputPullUp);
}

int onewire_getPin(void){
   return IfxPort_getPinState(&MODULE_P33, 10);
}

void onewire_setPinLow(){
    IfxPort_setPinLow(&MODULE_P33, 10);
}

void onewireWriteBit(int b) {
      b = b & 0x01;
      if (b) {
        // Write '1' bit
          onewire_setPinModeOutput();// onewirePinDirection = 0;
          onewire_setPinLow(); //onewirePin = 0;
          //__delay_us(5);
          waitTime(IfxStm_getTicksFromMicroseconds(BSP_DEFAULT_TIMER, 5));

          onewire_setPinModeInput();//onewirePinDirection = 1;
          //__delay_us(60);
          waitTime(IfxStm_getTicksFromMicroseconds(BSP_DEFAULT_TIMER, 60));
      } else {
        // Write '0' bit
          onewire_setPinModeOutput();//onewirePinDirection = 0;
          onewire_setPinLow(); //onewirePin = 0;
          //__delay_us(70);
          waitTime(IfxStm_getTicksFromMicroseconds(BSP_DEFAULT_TIMER, 70));
          onewire_setPinModeInput();//onewirePinDirection = 1;
          //__delay_us(2);
          waitTime(IfxStm_getTicksFromMicroseconds(BSP_DEFAULT_TIMER, 2));
      }
}

unsigned char onewireReadBit() {
      unsigned char result;

      onewire_setPinModeOutput();// onewirePinDirection = 0;
      onewire_setPinLow(); //onewirePin = 0;
      //__delay_us(1);
      waitTime(IfxStm_getTicksFromMicroseconds(BSP_DEFAULT_TIMER, 1));
      onewire_setPinModeInput();//onewirePinDirection = 1;
      //__delay_us(5);
      waitTime(IfxStm_getTicksFromMicroseconds(BSP_DEFAULT_TIMER, 5));
      result = (unsigned char) onewire_getPin(); //onewirePin;
      //__delay_us(55);
      waitTime(IfxStm_getTicksFromMicroseconds(BSP_DEFAULT_TIMER, 55));
      return result;

}

unsigned char onewireInit() {
    onewire_setPinModeOutput();//onewirePinDirection = 0;
    onewire_setPinLow(); //onewirePin = 0;
    //__delay_us(480);
    waitTime(IfxStm_getTicksFromMicroseconds(BSP_DEFAULT_TIMER, 480));
    onewire_setPinModeInput();//onewirePinDirection = 1;
    //__delay_us(60);
    waitTime(IfxStm_getTicksFromMicroseconds(BSP_DEFAULT_TIMER, 60));
    if ( /*onewirePin*/ onewire_getPin() == 0) {
       // __delay_us(100);
        waitTime(IfxStm_getTicksFromMicroseconds(BSP_DEFAULT_TIMER, 100));
        return 1;
    }
    return 0;
}

unsigned char onewireReadByte() {
  unsigned char result = 0;

  for (unsigned char loop = 0; loop < 8; loop++) {
    // shift the result to get it ready for the next bit
    result >>= 1;

    // if result is one, then set MS bit
    if (onewireReadBit())
      result |= 0x80;
  }
  return result;
}

void onewireWriteByte(char data) {
  // Loop to write each bit in the byte, LS-bit first
  for (unsigned char loop = 0; loop < 8; loop++) {
    onewireWriteBit(data & 0x01);

    // shift the data byte for the next bit
    data >>= 1;
  }
}

unsigned char onewireCRC(unsigned char* addr, unsigned char len) {
  unsigned char i, j;
  unsigned char crc = 0;

  for (i = 0; i < len; i++) {
    unsigned char inbyte = addr[i];
    for (j = 0; j < 8; j++) {
      unsigned char mix = (crc ^ inbyte) & 0x01;
      crc >>= 1;
      if (mix) crc ^= 0x8C;
      inbyte >>= 1;
    }
  }

  return crc;
}

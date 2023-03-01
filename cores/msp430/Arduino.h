#pragma once

#include "api/ArduinoAPI.h"
#include <msp430.h>


#ifdef __cplusplus
// Compatability function to allow "bool" or "int" to digitalWrite
void digitalWrite(pin_size_t pinNumber, int status);
#endif


// Defined in pins_arduino.h
const extern uintptr_t pin_inreg[];
const extern uintptr_t pin_outreg[];
const extern uintptr_t pin_sel0reg[];
const extern uintptr_t pin_sel1reg[];
const extern uintptr_t pin_dirreg[];
const extern uintptr_t pin_renreg[];
const extern uint8_t pin_bitmask[];


// Macros to use these arrays
#define PxIN(n)             (*((volatile uint8_t*)pin_inreg[n]))
#define PxOUT(n)            (*((volatile uint8_t*)pin_outreg[n]))
#define PxSEL0(n)           (*((volatile uint8_t*)pin_sel0reg[n]))
#define PxSEL1(n)           (*((volatile uint8_t*)pin_sel1reg[n]))
#define PxDIR(n)            (*((volatile uint8_t*)pin_dirreg[n]))
#define PxREN(n)            (*((volatile uint8_t*)pin_renreg[n]))
#define PxMASK(n)             ((uint8_t)pin_bitmask[n])


#include "pins_arduino.h"

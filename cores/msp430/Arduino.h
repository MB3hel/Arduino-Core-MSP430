#pragma once

#include "api/ArduinoAPI.h"
#include <msp430.h>


// Defined in pins_arduino.h
const extern uintptr_t pin_inreg[];
const extern uintptr_t pin_outreg[];
const extern uintptr_t pin_sel0reg[];
const extern uintptr_t pin_sel1reg[];
const extern uintptr_t pin_dirreg[];
const extern uintptr_t pin_renreg[];
const extern uint8_t pin_bitmask[];


// Macros to use these arrays
#define PINREG(x)           (*((volatile uint8_t*)pin_inreg[x]))
#define POUTREG(x)          (*((volatile uint8_t*)pin_outreg[x]))
#define PSEL1REG(x)         (*((volatile uint8_t*)pin_sel0reg[x]))
#define PSEL0REG(x)         (*((volatile uint8_t*)pin_sel1reg[x]))
#define PDIRREG(x)          (*((volatile uint8_t*)pin_dirreg[x]))
#define PRENREG(x)          (*((volatile uint8_t*)pin_renreg[x]))
#define PINMASK(x)          ((uint8_t)pin_bitmask[x])


#include "pins_arduino.h"

/**
 * @file Arduino.h
 * Derived from Energia MSP430 Energia.h and other energia MSP430 core files
 * 
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General
 * Public License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place, Suite 330,
 * Boston, MA  02111-1307  USA
 * 
 */

#pragma once

#include "api/ArduinoAPI.h"
#include <msp430.h>


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Digital IO
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Analog Inputs (ADC)
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#if defined(__MSP430_HAS_ADC10__)
// -----------------------------------------------------------------------------------------------------------------
// F2xx and G2xx family ADC10 module
// -----------------------------------------------------------------------------------------------------------------
#define DEFAULT             0
#define INTERNAL1V5         1
#define INTERNAL2V5         2
#define EXTERNAL            3
// -----------------------------------------------------------------------------------------------------------------
#elif defined(__MSP430_HAS_ADC12__)
// -----------------------------------------------------------------------------------------------------------------
// F2xx and G2xx family ADC12 module
// -----------------------------------------------------------------------------------------------------------------
#define DEFAULT             0
#define INTERNAL1V5         1
#define INTERNAL2V5         2
#define EXTERNAL            3
// -----------------------------------------------------------------------------------------------------------------
#elif defined(__MSP430_HAS_ADC10_B__)
// -----------------------------------------------------------------------------------------------------------------
// FR57xx family ADC10_B module
// -----------------------------------------------------------------------------------------------------------------
#define DEFAULT             0
#define INTERNAL1V5         1
#define INTERNAL2V0         2
#define INTERNAL2V5         3
#define EXTERNAL            4
// -----------------------------------------------------------------------------------------------------------------
#elif defined(__MSP430_HAS_ADC12_B__)
// -----------------------------------------------------------------------------------------------------------------
// FR58xx, FR59xx, FR6xx family ADC12_B module
// -----------------------------------------------------------------------------------------------------------------
#define DEFAULT             0
#define INTERNAL1V2         1
#define INTERNAL2V0         2
#define INTERNAL2V5         3
#define EXTERNAL            4
// -----------------------------------------------------------------------------------------------------------------
#elif defined(__MSP430_HAS_ADC__)
// -----------------------------------------------------------------------------------------------------------------
// FR4xx and FR2xx family ADC (multi resolution)
// -----------------------------------------------------------------------------------------------------------------
// 1.5V internal ref available on all, but 2.0 and 2.5 only on some
#define DEFAULT             0
#define INTERNAL1V5         1
#ifdef REFVSEL
#define INTERNAL2V0         2
#define INTERNAL2V5         3
#endif
#define EXTERNAL            4
// -----------------------------------------------------------------------------------------------------------------
#elif defined(__MSP430_HAS_ADC12_PLUS__)
// -----------------------------------------------------------------------------------------------------------------
// x5xx and x6xx family ADC12_A module
// -----------------------------------------------------------------------------------------------------------------
#define DEFAULT             0
#define INTERNAL1V5         1
#define INTERNAL2V0         2
#define INTERNAL2V5         3
#define EXTERNAL            4
// -----------------------------------------------------------------------------------------------------------------
#elif defined(__MSP430_HAS_ADC10_A__)
// -----------------------------------------------------------------------------------------------------------------
// x5xx and x6xx family ADC10_A module
// -----------------------------------------------------------------------------------------------------------------
#define DEFAULT             0
#define INTERNAL1V5         1
#define INTERNAL2V0         2     
#define INTERNAL2V5         3
#define EXTERNAL            4
// -----------------------------------------------------------------------------------------------------------------
#endif
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



#include "pins_arduino.h"

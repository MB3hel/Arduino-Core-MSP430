/**
 * @file wiring_analog.cpp
 * Derived from Energia MSP430 wiring_analog.c
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

#include <Arduino.h>


// Track current reference (one of defines in Arduino.h)
static uint8_t adc_ref = DEFAULT;



int analogRead(pin_size_t pinNumber){
#if defined(__MSP430_HAS_ADC10__)
    // -----------------------------------------------------------------------------------------------------------------
    // F2xx and G2xx family ADC10 module
    // -----------------------------------------------------------------------------------------------------------------
#ifndef ADC10ENC
#define ADC10ENC ENC
#endif
    ADC10CTL0 &= ADC10ENC;                      // Disable conversion
    ADC10CTL1 = ADC10SSEL_0 | ADC10DIV_4;       // ADC10OSC (5MHz) / 5
    // -----------------------------------------------------------------------------------------------------------------
#elif defined(__MSP430_HAS_ADC12__)
    // -----------------------------------------------------------------------------------------------------------------
    // F2xx and G2xx family ADC12 module
    // -----------------------------------------------------------------------------------------------------------------
    // TODO
    // -----------------------------------------------------------------------------------------------------------------
#elif defined(__MSP430_HAS_ADC10_B__)
    // -----------------------------------------------------------------------------------------------------------------
    // FR57xx family ADC10_B module
    // -----------------------------------------------------------------------------------------------------------------
    // TODO
    // -----------------------------------------------------------------------------------------------------------------
#elif defined(__MSP430_HAS_ADC12_B__)
    // -----------------------------------------------------------------------------------------------------------------
    // FR58xx, FR59xx, FR6xx family ADC12_B module
    // -----------------------------------------------------------------------------------------------------------------
    // TODO
    // -----------------------------------------------------------------------------------------------------------------
#elif defined(__MSP430_HAS_ADC__)
    // -----------------------------------------------------------------------------------------------------------------
    // FR4xx and FR2xx family ADC (multi resolution)
    // -----------------------------------------------------------------------------------------------------------------
    // TODO
    // -----------------------------------------------------------------------------------------------------------------
#elif defined(__MSP430_HAS_ADC12_PLUS__)
    // -----------------------------------------------------------------------------------------------------------------
    // x5xx and x6xx family ADC12_A module
    // -----------------------------------------------------------------------------------------------------------------
    // TODO
    // -----------------------------------------------------------------------------------------------------------------
#elif defined(__MSP430_HAS_ADC10_A__)
    // -----------------------------------------------------------------------------------------------------------------
    // x5xx and x6xx family ADC10_A module
    // -----------------------------------------------------------------------------------------------------------------
    // TODO
    // -----------------------------------------------------------------------------------------------------------------
#endif
}

void analogReference(uint8_t mode){
    adc_ref = mode;
}

void analogWrite(pin_size_t pinNumber, int value){
    // TODO: Implement PWM w/ timers
}

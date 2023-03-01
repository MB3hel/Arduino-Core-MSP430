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



#if defined(__MSP430_HAS_ADC10__) && !defined(ADC10ENC)
#define ADC10ENC ENC 
#endif
#if defined(__MSP430_HAS_ADC10__)
#define REFV_MAP(x) (x)
//#define REF_MAP(x)  (x & 0x31)
#define ADCxMEM0 ADC10MEM
#endif
#if defined(__MSP430_HAS_ADC10_A__)
#define REFV_MAP(x) (x)
//#define REF_MAP(x)  (x & 0x31)
#define ADCxMEM0 ADC10MEM 
#endif
#if defined(__MSP430_HAS_ADC10_B__)
#define REFV_MAP(x) ((x>>8) & 0x70)
#define REF_MAP(x)  (x & 0x31)
#define ADCxMEM0 ADC10MEM0 
#endif
#if defined(__MSP430_HAS_ADC12_PLUS__)
#define REFV_MAP(x) ((x>>8) & 0x70)
#define REF_MAP(x)  (x & 0xB1)
#define ADCxMEM0 ADC12MEM0 
#define DEFAULT_READ_RESOLUTION 12
#endif
#if defined(__MSP430_HAS_ADC12_B__)
#define REFV_MAP(x) (x & 0xF00)
#define REF_MAP(x)  (x & 0x31)
#define ADCxMEM0 ADC12MEM0 
#define DEFAULT_READ_RESOLUTION 12
#endif
#if defined(__MSP430_HAS_ADC__)
#define REFV_MAP(x) ((x>>8) & 0x70)
//#define REF_MAP(x)  (x & 0x31)
#define ADCxMEM0 ADCMEM0
#endif


int analogRead(pin_size_t pinNumber){
#if defined(__MSP430_HAS_ADC10__)
    ADC10CTL0 &= ~ADC10ENC;                         // Disable conversion

#elif defined(__MSP430_HAS_ADC12__)
    // TODO
#elif defined(__MSP430_HAS_ADC12_PLUS__)
    // TODO
#elif defined(__MSP430_HAS_ADC12_B__)
    // TODO
#elif defined(__MSP430_HAS_ADC10_B__)
    // TODO
#elif defined(__MSP430_HAS_ADC__)
    // TODO
#else
    // No (known) ADC
    return 0;
#endif
}

void analogReference(uint8_t mode){
    // TODO: Implement this
}

void analogWrite(pin_size_t pinNumber, int value){
    // TODO: Implement PWM w/ timers
}

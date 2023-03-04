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


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// ADC
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void analogReference(uint8_t mode){
#if defined(__MSP430_HAS_ADC10__)
    // -----------------------------------------------------------------------------------------------------------------
    // F2xx and G2xx family ADC10 module
    // -----------------------------------------------------------------------------------------------------------------
#ifndef ADC10ENC
#define ADC10ENC ENC
#endif
    ADC10CTL0 &= ~ADC10ENC;                     // Disable conversion
    ADC10CTL1 = ADC10SSEL_0 | ADC10DIV_4;       // ADC10OSC (~5MHz) / 5
    ADC10CTL0 &= ~SREF_7;                       // Clear reference selection
    switch(mode){
    case INTERNAL1V5:
        ADC10CTL0 |= SREF_1 | REFON;            // Internal 1.5V to GND
        ADC10CTL0 &= ~REF2_5V;
        break;
    case INTERNAL2V5:
        ADC10CTL0 |= SREF_1 | REFON | REF2_5V;  // Internal 2.5V to GND
        break;
    case EXTERNAL:
        ADC10CTL0 |= SREF_2;                    // External to GND
        ADC10CTL0 &= ~REFON;
        break;
    default:
        ADC10CTL0 |= SREF_0;                    // VCC to GND
        ADC10CTL0 &= ~REFON;
        break;
    }
    ADC10CTL0 &= ~ADC10SHT_3;                   // Clear sample hold time
    ADC10CTL0 |= ADC10SHT_3;                    // Sample and hold 64 cycles. 
    ADC10CTL0 |= ADC10IE;                       // Enable interrupt
    // -----------------------------------------------------------------------------------------------------------------
#elif defined(__MSP430_HAS_ADC12__)
    // -----------------------------------------------------------------------------------------------------------------
    // F2xx and G2xx family ADC12 module
    // -----------------------------------------------------------------------------------------------------------------
    // Note: Using mem0
#ifndef ADC12ENC
#define ADC12ENC ENC
#endif
    ADC12CTL0 &= ~ADC12ENC;                     // Disable conversion
    ADC12CTL1 = ADC12SSEL_0 | ADC12DIV_4;       // ADC12OSC (~5MHz) / 5
    switch(mode){
    case INTERNAL1V5:
        ADC12MCTL0 = SREF_1;                    // Internal 1.5V to GND
        ADC12CTL0 |= REFON;
        ADC12CTL0 &= ~REF2_5V;
        break;
    case INTERNAL2V5:
        ADC12MCTL0 = SREF1;                     // Internal 2.5V to GND
        ADC12CTL0 |= REFON | REF2_5V;
        break;
    case EXTERNAL:
        ADC12MCTL0 = SREF_2;                    // External to GND
        ADC12CTL0 &= ~REFON;
        break;
    default:
        ADC12MCTL0 = SREF_0;                    // VCC to GND
        ADC12CTL0 &= ~REFON;
        break;
    }
    ADC12CTL0 &= ~SHT0_15;                      // Clear sample hold time
    ADC12CTL0 |= SHT0_4;                        // 64 cycles sample and hold
    ADC12IE |= BIT0;                            // Enable interrupt for mem 0
    // -----------------------------------------------------------------------------------------------------------------
#elif defined(__MSP430_HAS_ADC10_B__)
    // -----------------------------------------------------------------------------------------------------------------
    // FR57xx family ADC10_B module
    // -----------------------------------------------------------------------------------------------------------------
    ADC10CTL0 &= ~ADC10ENC;                     // Disable Conversion
    ADC10CTL1 = ADC10SSEL_0 | ADC10DIV_4;       // ADC10OSC (~5MHz) / 5
    ADC10MCTL0 &= ~ADC10SREF_7;                 // Clear reference selection
    while(REFCTL0 & REFGENBUSY);                // Wait until ref gen not busy
    switch(mode){
    case INTERNAL1V5:
        REFCTL0 = REFON | REFVSEL_0;            // Internal reference on 1.5V
        ADC10MCTL0 |= ADC10SREF_1;              // Internal 1.5V to GND
        break;
    case INTERNAL2V0:
        REFCTL0 = REFON | REFVSEL_1;            // Internal reference on 2.0V
        ADC10MCTL0 |= ADC10SREF_1;              // Internal 2.0V to GND
        break;
    case INTERNAL2V5:
        REFCTL0 = REFON | REFVSEL_2;            // Internal reference on 2.5V
        ADC10MCTL0 |= ADC10SREF_1;              // Internal 2.5V to GND
        break;
    case EXTERNAL:
        REFCTL0 = ~REFON;                       // Internal reference off
        ADC10MCTL0 |= ADC10SREF_2;              // External to GND
        break;
    default:
        REFCTL0 = ~REFON;                       // Internal reference off
        ADC10MCTL0 |= ADC10SREF_0;              // VCC to GND
        break;
    }
    ADC10CTL0 &= ~ADC10SHT_15;                  // Clear sample hold time
    ADC10CTL0 |= ADC10SHT_4;                    // Sample and hold 64 cycles
    ADC10IE |= ADC10IE0;                        // Enable conversion complete interrupt
    // -----------------------------------------------------------------------------------------------------------------
#elif defined(__MSP430_HAS_ADC12_B__)
    // -----------------------------------------------------------------------------------------------------------------
    // FR58xx, FR59xx, FR6xx family ADC12_B module
    // -----------------------------------------------------------------------------------------------------------------
    // Note: Using mem0
    ADC12CTL0 &= ~ADC12ENC;                     // Disable Conversion
    ADC12CTL1 = ADC12SSEL_0 | ADC12DIV_4;       // ADC12OSC (~5MHz) / 5
    while(REFCTL0 & REFGENBUSY);                // Wait until ref gen not busy
    switch(mode){
    case INTERNAL1V2:
        REFCTL0 = REFON | REFVSEL_0;            // Internal reference on 1.2V
        ADC12MCTL0 = ADC12VRSEL_1;              // Internal 1.2V to GND
        break;
    case INTERNAL2V0:
        REFCTL0 = REFON | REFVSEL_1;            // Internal reference on 2.0V
        ADC12MCTL0 = ADC12VRSEL_1;              // Internal 2.0V to GND
        break;
    case INTERNAL2V5:
        REFCTL0 = REFON | REFVSEL_2;            // Internal reference on 2.5V
        ADC12MCTL0 = ADC12VRSEL_1;              // Internal 2.5V to GND
        break;
    case EXTERNAL:
        REFCTL0 = ~REFON;                       // Internal reference off
        ADC12MCTL0 = ADC12VRSEL_4;              // External to GND
        break;
    default:
        REFCTL0 = ~REFON;                       // Internal reference off
        ADC12MCTL0 = ADC12VRSEL_0;              // VCC to GND
        break;
    }
    ADC12CTL0 &= ~ADC12SHT0_15;                 // Clear sample hold time
    ADC12CTL0 |= ADC12SHT0_4;                   // Sample and hold 64 cycles
    ADC12IER0 |= ADC12IE0;                      // Enable conversion complete interrupt
    // -----------------------------------------------------------------------------------------------------------------
#elif defined(__MSP430_HAS_ADC__)
    // -----------------------------------------------------------------------------------------------------------------
    // FR4xx and FR2xx family ADC (multi resolution)
    // -----------------------------------------------------------------------------------------------------------------
    // Note: Uses mem0
    ADCCTL0 &= ~ADCENC;                         // Disable conversion
    ADCCTL1 = ADCSSEL_0 | ADCDIV_4;             // ADCOSC (~5MHz) / 5
    ADCCTL2 &= ~ADCRES_3;                       // Clear resolution selection
    ADCCTL2 |= ADCRES_2;                        // 12-bit
    PMMCTL0_H  = PMMPW_H;                       // Unlock PMM
    switch(mode){
#ifdef REFVSEL
    case INTERNAL1V5:
        PMMCTL2 |= INTREFEN;                    // Enable internal reference
        PMMCTL2 &= ~REFVSEL_3;                  // Clear reference vsel
        PMMCTL2 |= REFVSEL_0;                   // 1.5V reference
        ADCMCTL0 = ADCSREF_1;                   // 1.5V to GND
        break;
    case INTERNAL2V0:
        PMMCTL2 |= INTREFEN;                    // Enable internal reference
        PMMCTL2 &= ~REFVSEL_3;                  // Clear reference vsel
        PMMCTL2 |= REFVSEL_1;                   // 2.0V reference
        ADCMCTL0 = ADCSREF_1;                   // 2.0V to GND
        break;
    case INTERNAL2V5:
        PMMCTL2 |= INTREFEN;                    // Enable internal reference
        PMMCTL2 &= ~REFVSEL_3;                  // Clear reference vsel
        PMMCTL2 |= REFVSEL_2;                   // 2.5V reference
        ADCMCTL0 = ADCSREF_1;                   // 2.5V to GND
        break;
#else
    case INTERNAL1V5:
        PMMCTL2 |= INTREFEN;                    // Enable internal 1.5V ref
        ADCMCTL0 = ADCSREF_1;                   // 1.5V to GND
        break;
#endif
    case EXTERNAL:
        PMMCTL2 &= ~INTREFEN;                   // Disable internal reference
        ADCMCTL0 = ADCSREF_2;                   // External to GND
        break;
    default:
        PMMCTL2 &= ~INTREFEN;                   // Disable internal reference
        ADCMCTL0 = ADCSREF_0;                   // VCC to GND
        break;
    }
    PMMCTL0_H = 0;                              // Lock PMM
    ADCCTL0 &= ~ADCSHT_15;                      // Clear sample hold time
    ADCCTL0 |= ADCSHT_4;                        // Sample and hold 64 cycles
    ADCIE |= ADCIE0;                            // Enable conversion complete interrupt
    // -----------------------------------------------------------------------------------------------------------------
#elif defined(__MSP430_HAS_ADC12_PLUS__)
    // -----------------------------------------------------------------------------------------------------------------
    // x5xx and x6xx family ADC12_A module
    // -----------------------------------------------------------------------------------------------------------------
    // Note: Using mem0
    ADC12CTL0 &= ~ADC12ENC;                     // Disable Conversion
    ADC12CTL1 = ADC12SSEL_0 | ADC12DIV_4;       // ADC12OSC (~5MHz) / 5
    while(REFCTL0 & REFGENBUSY);                // Wait until ref gen not busy
    switch(mode){
    case INTERNAL1V5:
        REFCTL0 = REFON | REFVSEL_0;            // Internal reference on 1.2V
        ADC12MCTL0 = ADC12SREF_0;               // Internal 1.2V to GND
        break;
    case INTERNAL2V0:
        REFCTL0 = REFON | REFVSEL_1;            // Internal reference on 2.0V
        ADC12MCTL0 = ADC12SREF_1;               // Internal 2.0V to GND
        break;
    case INTERNAL2V5:
        REFCTL0 = REFON | REFVSEL_2;            // Internal reference on 2.5V
        ADC12MCTL0 = ADC12SREF_1;               // Internal 2.5V to GND
        break;
    case EXTERNAL:
        REFCTL0 = ~REFON;                       // Internal reference off
        ADC12MCTL0 = ADC12SREF_4;               // External to GND
        break;
    default:
        REFCTL0 = ~REFON;                       // Internal reference off
        ADC12MCTL0 = ADC12SREF_0;               // VCC to GND
        break;
    }
    ADC12CTL0 &= ~ADC12SHT0_15;                 // Clear sample hold time
    ADC12CTL0 |= ADC12SHT0_4;                   // Sample and hold 64 cycles
    ADC12IE |= ADC12IE0;                        // Enable conversion complete interrupt
    // -----------------------------------------------------------------------------------------------------------------
#elif defined(__MSP430_HAS_ADC10_A__)
    // -----------------------------------------------------------------------------------------------------------------
    // x5xx and x6xx family ADC10_A module
    // -----------------------------------------------------------------------------------------------------------------
    ADC10CTL0 &= ~ADC10ENC;                     // Disable Conversion
    ADC10CTL1 = ADC10SSEL_0 | ADC10DIV_4;       // ADC10OSC (~5MHz) / 5
    ADC10MCTL0 &= ~ADC10SREF_7;                 // Clear reference selection
    while(REFCTL0 & REFGENBUSY);                // Wait until ref gen not busy
    switch(mode){
    case INTERNAL1V5:
        REFCTL0 = REFON | REFVSEL_0;            // Internal reference on 1.5V
        ADC10MCTL0 |= ADC10SREF_1;              // Internal 1.5V to GND
        break;
    case INTERNAL2V0:
        REFCTL0 = REFON | REFVSEL_1;            // Internal reference on 2.0V
        ADC10MCTL0 |= ADC10SREF_1;              // Internal 2.0V to GND
        break;
    case INTERNAL2V5:
        REFCTL0 = REFON | REFVSEL_2;            // Internal reference on 2.5V
        ADC10MCTL0 |= ADC10SREF_1;              // Internal 2.5V to GND
        break;
    case EXTERNAL:
        REFCTL0 = ~REFON;                       // Internal reference off
        ADC10MCTL0 |= ADC10SREF_2;              // External to GND
        break;
    default:
        REFCTL0 = ~REFON;                       // Internal reference off
        ADC10MCTL0 |= ADC10SREF_0;              // VCC to GND
        break;
    }
    ADC10CTL0 &= ~ADC10SHT_15;                  // Clear sample hold time
    ADC10CTL0 |= ADC10SHT_4;                    // Sample and hold 64 cycles
    ADC10IE |= ADC10IE0;                        // Enable conversion complete interrupt
    // -----------------------------------------------------------------------------------------------------------------
#endif
    delayMicroseconds(10);                      // Allow reference to stabilize
}

int analogRead(pin_size_t pinNumber){
    if(PxADCCH(pinNumber) == 255 || pinNumber > MAX_PINNUM)
        return 0; // Not a valid pin
    
    // Select channel
    // Turn ADC on
    // Enable conversion (& start conversion depending on ADC)
    // Enter LPM0
    // Wait for interrupt then wake
    // Disable conversion
    // Turn ADC off

#if defined(__MSP430_HAS_ADC10__)
    // -----------------------------------------------------------------------------------------------------------------
    // F2xx and G2xx family ADC10 module
    // -----------------------------------------------------------------------------------------------------------------
#ifndef ADC10ENC
#define ADC10ENC ENC
#endif
    ADC10CTL0 |= ADC10ON;                       // Turn ADC on
    ADC10CTL1 &= ~INCH_15;                      // Clear channel selection
    ADC10CTL1 |= 
        ((PxADCCH(pinNumber) & 0xF) << 12);     // Select channel
    ADC10CTL0 |= ADC10ENC | ADC10SC;            // Enable & start conversion
    __bis_SR_register(LPM0_bits + GIE);         // Enter low power mode (will be woken by ISR)
    ADC10CTL0 &= ~(ADC10ENC | ADC10SC);         // Disable conversion
    ADC10CTL0 &= ~ADC10ON;                      // Turn ADC off
    return (int)ADC10MEM;
    // -----------------------------------------------------------------------------------------------------------------
#elif defined(__MSP430_HAS_ADC12__)
    // -----------------------------------------------------------------------------------------------------------------
    // F2xx and G2xx family ADC12 module
    // -----------------------------------------------------------------------------------------------------------------
#ifndef ADC12ENC
#define ADC12ENC ENC
#endif
    ADC12CTL0 |= ADC12ON;                       // Turn ADC on
    ADC12MCTL0 &= ~INCH_15;                     // Clear channel selection
    ADC12MCTL0 |= 
        ((PxADCCH(pinNumber) & 0xF) << 0);      // Select channel
    ADC12CTL0 |= ADC12ENC | ADC12SC;            // Enable & start conversion
    __bis_SR_register(LPM0_bits + GIE);         // Enter low power mode (will be woken by ISR)
    ADC12CTL0 &= ~(ADC12ENC | ADC12SC);         // Disable conversion
    ADC12CTL0 &= ~ADC12ON;                      // Turn ADC off
    return (int)ADC12MEM0;
    // -----------------------------------------------------------------------------------------------------------------
#elif defined(__MSP430_HAS_ADC10_B__)
    // -----------------------------------------------------------------------------------------------------------------
    // FR57xx family ADC10_B module
    // -----------------------------------------------------------------------------------------------------------------
    ADC10CTL0 |= ADC10ON;                       // Turn ADC on
    ADC10MCTL0 &= ~ADC10INCH_15;                // Clear channel selection
    ADC10MCTL0 |= 
        ((PxADCCH(pinNumber) & 0xF) << 0);      // Select channel
    ADC10CTL0 |= ADC10ENC | ADC10SC;            // Enable & start conversion
    __bis_SR_register(LPM0_bits + GIE);         // Enter low power mode (will be woken by ISR)
    ADC10CTL0 &= ~(ADC10ENC | ADC10SC);         // Disable conversion
    ADC10CTL0 &= ~ADC10ON;                      // Turn ADC off
    return (int)ADC10MEM0;
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
#else
    return 0;                                   // No known ADC
#endif
}


// TODO: ADC ISR handlers

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// PWM
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void analogWrite(pin_size_t pinNumber, int value){
    // TODO: Implement PWM w/ timers
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

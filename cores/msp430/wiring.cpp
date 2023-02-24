/**
 * @file wiring.cpp
 * Derived from Energia MSP430 wiring.c
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

volatile unsigned int aclk_freq = 0;

/**
 * Clock initialization for MSP430 chips with a "Basic Clock Module+"
 * See page 275: https://www.ti.com/lit/ug/slau144k/slau144k.pdf
 */
static inline __attribute__ ((__always_inline__)) void initClocksBC2(){
    // Set frequency for DCO (used for MCLK and SMCLK)
    // Reset state has MCLK = DCO / 1
    // and SMCLK = DOC / 1
    DCOCTL = 0;
#if defined(CAL_BC1_16MHZ) && (F_CPU == 16000000L)
    BCSCTL1 = CALBC1_16MHZ;
    DCOCTL = CALDCO_16MHZ;
#elif defined(CAL_BC1_12MHZ) && (F_CPU == 12000000L)
    BCSCTL1 = CALBC1_12MHZ;
    DCOCTL = CALDCO_12MHZ;
#elif defined(CAL_BC1_8MHZ) && (F_CPU == 8000000L)
    BCSCTL1 = CALBC1_8MHZ;
    DCOCTL = CALDCO_8MHZ;
#elif defined(CAL_BC1_1MHZ) && (F_CPU == 1000000L)
    BCSCTL1 = CALBC1_1MHZ;
    DCOCTL = CALDCO_1MHZ;
#else
    #error Invalid CPU frequency for this chip!
#endif

    // Wait up to 2 seconds for 32768 LXFT1 oscillator to start
    // Started when fault flag does not get set
    // Reset state has P2.6 and P2.7 used for LXFT1
    // Reset state has LXFT1 in normal mode (LXFT1S = 0b00)
#ifndef NOLXFT1
    unsigned int timeout = 4;
    do{
        timeout--;
        BCSCTL3 &= ~LFXT1OF;                    // Clear oscillator fault flag
        IFG1 &= ~OFIFG;                         // Clear fault interrupt flag
        __delay_cycles(500000L * 
                        (F_CPU/1000000L));      // Delay 500ms
        if(timeout == 0) break;                 // Timed out
    }while(IFG1 & OFIFG);
#else
    unsigned int timeout = 0;
#endif
    if(timeout == 0){
        // Timed out. LXFT did not start.
        // Fall back on VLO
        aclk_freq = 10000;                      // Approx 10kHz
        P2SEL &= ~(BIT6 | BIT7);                // P2.6 and P2.7 for GPIO
        BCSCTL3 &= ~(LFXT1S0 | LFXT1S1);        // Clear LXFT1S field
        BCSCTL3 |= LFXT1S_2;                    // Source LXFT from VLO
    }
}

/**
 * Clock initialization for MSP430 chips with a "Clock System module"
 * See page 98: https://www.ti.com/lit/ug/slau445i/slau445i.pdf
 */
static inline __attribute__ ((__always_inline__)) void initClocksCS(){
    // NYI
}

/**
 * Initialize MCLK to frequency F_CPU
 * Initialize SMCLK to frequency F_CPU
 * Initialize ACLK to external 32.768kHz oscillator
 *   fallback to VLO if fails (VLO freq depends on chip)
 * Note that NOLXFT1 can be defined to use the VLO directly
 */
void initClocks(){
#if defined(__MSP430_HAS_BC2__)
    initClocksBC2();
#elif defined(__MSP430_HAS_CS__)
    #error CS support NYI!
    // initClocksCS();
#endif
}

/**
 * Initialize MSP430 chip
 */
void init(){
    WDTCTL = WDTPW | WDTHOLD;               // Disable watchdog timer
    initClocks();                           // Initialize clocks
}

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
 * Initialize MCLK to frequency F_CPU
 * Initialize SMCLK to frequency F_CPU
 * Initialize ACLK to external 32.768kHz oscillator
 *   fallback to VLO if fails (VLO freq depends on chip)
 */
void initClocks(){
#if defined(__MSP430_HAS_BC2__)
    // MSP430 chips with a "Basic Clock Module+"
    // https://www.ti.com/lit/ug/slau144k/slau144k.pdf
    // Page 275

    // Get calibration values for BC1 and DCO
#if defined(CAL_BC1_16MHZ) && (F_CPU == 16000000L)
    BCSCTL1 = CAL_BC1_16MHZ;
    DCOCTL = CAL_DCO_16MHZ;
#elif defined(CAL_BC1_12MHZ) && (F_CPU == 12000000L)
    BCSCTL1 = CAL_BC1_12MHZ;
    DCOCTL = CAL_DCO_12MHZ;
#elif defined(CAL_BC1_8MHZ) && (F_CPU == 8000000L)
    BCSCTL1 = CAL_BC1_8MHZ;
    DCOCTL = CAL_DCO_8MHZ;
#elif defined(CAL_BC1_1MHZ) && (F_CPU == 1000000L)
    BCSCTL1 = CAL_BC1_1MHZ;
    DCOCTL = CAL_DCO_1MHZ;
#else
    #error Invalid CPU frequency for this chip!
#endif

    BCSCTL1 |= XT2OFF;                          // Disable XT2
    BCSCTL2 &= ~(SELM0 | SELM1);                // Clear MCLK select bits
    BCSCTL2 |= SELM_0;                          // MCLK from DCO
    BCSCTL2 &= ~SELS;                           // SCLK from DCO
    BCSCTL2 |= DIVM_0;                          // MCLK div 1
    BCSCTL2 |= DIVS_0;                          // SCLK div 1

    // Wait up to 2 seconds for 32768 LXFT1 oscillator to start
    // Started when fault flag does not get set
    P2SEL |= (BIT6 | BIT7);                     // P2.6 and P2.7 for LXFT1
    BCSCTL3 &= ~(LFXT1S0 | LFXT1S1);            // Clear LXFT1S field
    BCSCTL3 |= LFXT1S_0;                        // Source LXFT from external crystal
    unsigned int timeout = 4;
    do{
        timeout--;
        BCSCTL3 &= ~LFXT1OF;                    // Clear oscillator fault flag
        IFG1 &= ~OFIFG;                         // Clear fault interrupt flag
        __delay_cycles(500000L * 
                        (F_CPU/1000000L));      // Delay 500ms
        if(timeout == 0) break;                 // Timed out
    }while(IFG1 & OFIFG);
    if(timeout == 0){
        // Timed out. LXFT did not start.
        // Fall back on VLO
        aclk_freq = 10000;                      // Approx 10kHz
        P2SEL &= ~(BIT6 | BIT7);                // P2.6 and P2.7 for GPIO
        BCSCTL3 &= ~(LFXT1S0 | LFXT1S1);        // Clear LXFT1S field
        BCSCTL3 |= LFXT1S_2;                    // Source LXFT from VLO
    }
    

#elif defined(__MSP430_HAS_CS__)
    // MSP430 chips with a "Clock System module"
    // https://www.ti.com/lit/ug/slau445i/slau445i.pdf
    // Page 98
    # error CS support NYI!
#endif
}

/**
 * Initialize MSP430 chip
 */
void init(){
    WDTCTL = WDTPW | WDTHOLD;               // Disable watchdog timer
    initClocks();                           // Initialize clocks
}

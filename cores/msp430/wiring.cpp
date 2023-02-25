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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Globals
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

volatile unsigned int aclk_freq = 0;                                // Frequency of ACLK

// Time in milliseconds tracked by watchdog timer
volatile unsigned long wdt_millis;
volatile unsigned long wdt_frac;

// Used for micros()
volatile unsigned long wdt_overflow_count;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Clock initialization
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Initialize MCLK to frequency F_CPU
// Initialize SMCLK to frequency F_CPU
// Initialize ACLK to external 32.768kHz oscillator
//   fallback to VLO if fails (VLO freq depends on chip)
//   Note that NOLFXT1 can be defined to use the VLO without attempting
//   to use an external crystal first.


#if defined(__MSP430_HAS_BC2__)
// ---------------------------------------------------------------------------------------------------------------------
// Clock initialization for MSP430 chips with a Basic Clock module
// ---------------------------------------------------------------------------------------------------------------------
// Includes G2553
static void initClocks(){
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
#ifndef NOLFXT1
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
    }else{
        aclk_freq = 32768;
    }
}
// ---------------------------------------------------------------------------------------------------------------------
#elif (defined(__MSP430_HAS_CS__) || defined(__MSP430_HAS_CS_A__)) && (defined(__MSP430_HAS_FRAM__) || defined(__MSP430_HAS_FRCTL_A__) || defined(__MSP430_HAS_FRAM_FR5XX__)) && defined(__MSP430FR2XX_4XX_FAMILY__)
// ---------------------------------------------------------------------------------------------------------------------
// Clock initialization for MSP430 FR2XX and FR4XX family chips
// ---------------------------------------------------------------------------------------------------------------------
// Includes FR2355, FR2433
static void initClocks(){

    // These names were changed at some point. Not consistent between chips.
#if !defined(NACCESS_0)
#define NACCESS_0  NWAITS_0
#define NACCESS_1  NWAITS_1
#define NACCESS_2  NWAITS_2
#endif

    // Add FRAM wait states
#if F_CPU >= 16000000L
    FRCTL0 = FWPW | NACCESS_2;                  // two wait states
#elif F_CPU >= 8000000L
    FRCTL0 = FWPW | NACCESS_1;                  // one wait state
#endif

    CSCTL0 = 0;                                 // Configure lowest frequency

    // Note n is defined by FLLREFDIV bits
    // Here, n is 1
    // Here f_REF = f_REFO = 32.768kHz
    // f_DCO = 2^{FLLD} * (FLLN + 1) * (f_REF / n)
    // f_DCODIV = (FLLN + 1) * (f_REF / n)
    // MCLK and SMCLK from f_DCODIV
    // See section 3.2.5 https://www.ti.com/lit/ug/slau445i/slau445i.pdf
    // FLLN and FLLD in the CSCTL2 register
    // FLLN is lower 10 bits. FLLD is bits 12, 13, and 14
    // Note that FLLD is 1, 2, 4, 8, 16, or 32 (not 0-8)
#if F_CPU == 24000000L
    CSCTL1 = DCORSEL_7;                         // Range 7
    CSCTL2 = 0x02DC;                            // Loop control setting
#elif F_CPU == 20000000L
    CSCTL1 = DCORSEL_6;                         // Range 6
    CSCTL2 = 0x0262;                            // Loop control setting
#elif F_CPU == 16000000L
    CSCTL1 = DCORSEL_5;                         // Range 5
    CSCTL2 = 0x01E7;                            // Loop control setting
#elif F_CPU == 12000000L
    CSCTL1 = DCORSEL_4;                         // Range 4
    CSCTL2 = 0x016D;                            // Loop control setting
#elif F_CPU == 8000000L
    CSCTL1 = DCORSEL_3;                         // Range 3
    CSCTL2 = 0x00F3;                            // Loop control setting
#elif F_CPU == 4000000L
    CSCTL1 = DCORSEL_2;                         // Range 2
    CSCTL2 = 0x007A;                            // Loop control setting
#elif F_CPU == 2000000L
    CSCTL1 = DCORSEL_1;                         // Range 1
    CSCTL2 = 0x003D;                            // Loop control setting
#elif F_CPU == 1000000L
    CSCTL1 = DCORSEL_0;                         // Range 0
    CSCTL2 = 0x001D;                            // Loop control settings
#else
#error Invalid CPU frequency for this chip!
#endif

    CSCTL3 = SELREF__REFOCLK;                   // REFO for FLL
    CSCTL4 = SELA__XT1CLK |                     // XT1CLK for ACLK
             SELMS__DCOCLKDIV;                  // DCODIV for MCLK and SMCLK
    CSCTL7 &= ~(0x07);                          // Clear all fault flags

    // Setup pins for LXFT if needed (shared on some devices, internal on others)
#if (defined(INIT_LFXTAL_PINS))
    // Defined in pins_arduino.h for different variants
    INIT_LFXTAL_PINS;
#elif (defined(__MSP430_HAS_PORTJ_R__))
    PJDIR = 0xFF;                               // All pins output
    PJOUT = 0;                                  // All pins low
    PJSEL0 = BIT4 | BIT5;                       // PJ.4 and PJ.5 as XTAL
#endif    

    // Wait up to 2 seconds for 32768 LXFT1 oscillator to start
    // Started when fault flag does not get set
#ifndef NOLFXT1
    unsigned int timeout = 4;
    do{
        timeout--;
        CSCTL7 &= ~(DCOFFG|XT1OFFG|FLLULIFG);   // Clear oscillator fault flag
        SFRIFG1 &= ~OFIFG;                      // Clear fault interrupt flag
        __delay_cycles(500000L * 
                        (F_CPU/1000000L));      // Delay 500ms
        if(timeout == 0) break;                 // Timed out
    }while(SFRIFG1 & OFIFG);
#else
    unsigned int timeout = 0;
#endif
    if(timeout == 0){
        aclk_freq = 32768;                      // ACLK = REFO = 32768
        CSCTL4 &= ~SELA;                        // Clear ACLK select bits
        CSCTL4 |= SELA__REFOCLK;                // ACLK from REFO
        CSCTL3 &= ~SELREF;                      // Clear SELREF bits
        CSCTL3 |= SELREF__REFOCLK;              // FLL ref from REFO
        CSCTL7 &= ~(DCOFFG|XT1OFFG|FLLULIFG);   // Clear flags
        SFRIFG1 &= ~OFIFG;                      // Clear flag
    }else{
        CSCTL4 &= ~SELA;                        // Clear ACLK select bits
        CSCTL4 |= SELA__XT1CLK;                 // ACLK from LFXT1
        CSCTL3 &= ~SELREF;                      // Clear SELREF bits
        CSCTL3 |= SELREF__XT1CLK;               // FLL ref from LFXT1
        aclk_freq = 32768;
    }
}
// ---------------------------------------------------------------------------------------------------------------------
#elif (defined(__MSP430_HAS_CS__) || defined(__MSP430_HAS_CS_A__)) && (defined(__MSP430_HAS_FRAM__) || defined(__MSP430_HAS_FRCTL_A__))
// ---------------------------------------------------------------------------------------------------------------------
// Clock initialization for MSP430 FRAM chips other than FR2XX and FR4XX family
// ---------------------------------------------------------------------------------------------------------------------
// Includes FR5969
static void initClocks(){

    // These names were changed at some point. Not consistent between chips.
#if !defined(NACCESS_0)
#define NACCESS_0  NWAITS_0
#define NACCESS_1  NWAITS_1
#define NACCESS_2  NWAITS_2
#endif

    CSCTL0 = CSKEY;                             // Enable access to CS registers
    CSCTL2 &= ~SELM_7;                          // Clear MCLK source
    CSCTL2 |= SELM__DCOCLK;                     // Use DCO for MCLK
    CSCTL3 &= ~(DIVM_3 | DIVS_3);               // Clear division bits

#if F_CPU == 24000000L
    FRCTL0 = FWPW | NACCESS_2;                  // 2 wait states
    CSCTL1 = DCOFSEL_6 | DCORSEL;               // Level 6 / Range 1: 24.0 MHz
#elif F_CPU == 16000000L
    FRCTL0 = FWPW | NACCESS_1;                  // 1 wait state
    CSCTL1 = DCOFSEL_4 | DCORSEL;               // Level 4 / Range 1: 16.0 MHz
#elif F_CPU == 12000000L
    FRCTL0 = FWPW | NACCESS_1;                  // 1 wait state
    CSCTL1 = DCOFSEL_6 | DCORSEL;               // Level 6 / Ragne 1: 24.0 MHz
    CSCTL3 |= DIVM_1;                           // Divide by 2
#elif F_CPU == 8000000L
    CSCTL1 = DCOFSEL_3 | DCORSEL;               // Level 3 / Range 1: 8.0MHz
#elif F_CPU == 4000000L
    CSCTL1 = DCOFSEL_3 | DCORSEL;               // Level 3 / Range 1: 8.0MHz
    CSCTL3 |= DIVM_1;                           // Divide by 2 = 4.0 MHz
#elif F_CPU == 2000000L
    CSCTL1 = DCOFSEL_3 | DCORSEL;               // Level 3 / Range 1: 8.0MHz
    CSCTL3 |= DIVM_2;                           // Divide by 4 = 2.0 Mhz
#elif F_CPU == 1000000L
    CSCTL1 = DCOFSEL_3 | DCORSEL;               // Level 3 / Range 1: 8.0MHz
    CSCTL3 |= DIVM_3;                           // Divide by 8 = 1.0 MHz
#else
#error Invalid CPU frequency for this chip!
#endif

    // Setup pins for ACLK setup
    PJOUT = 0xFF;                               // All pins output
    PJOUT = 0;                                  // All pins low
    PJSEL0 = BIT4 | BIT5;                       // PJ.4 and PJ.5 as XTAL
    CSCTL4 &= ~LFXTOFF;                         // Enable LXFT

    // Wait up to 2 seconds for 32768 LXFT oscillator to start
    // Started when fault flag does not get set
#ifndef NOLFXT1
    unsigned int timeout = 4;
    do{
        timeout--;
        CSCTL5 &= ~LFXTOFFG;                    // Clear oscillator fault flag
        SFRIFG1 &= ~OFIFG;                      // Clear fault interrupt flag
        __delay_cycles(500000L * 
                        (F_CPU/1000000L));      // Delay 500ms
        if(timeout == 0) break;                 // Timed out
    }while(SFRIFG1 & OFIFG);
#else
    unsigned int timeout = 0;
#endif
    if(timeout == 0){
        // Exact frequency varies between devices and have a large range
        // 8kHz seems to be a reasonable middle ground...
        // Probably not that imporant what this is set to. Not really any reason
        // to disable LXFT on these devices. There are dedicated pins for it.
        // Usually, devices operate without LXFT because the pins are shared
        // with GPIO. That is not the case here.
        aclk_freq = 8000;                       // ACLK = VLO.
        CSCTL2 |= SELA__VLOCLK;                 // ACLK from VLO  
        CSCTL4 |= LFXTOFF;                      // Disable LXFT 
    }else{
        aclk_freq = 32768;
    }
}
// ---------------------------------------------------------------------------------------------------------------------
#elif defined(__MSP430_HAS_CS__) && defined(__MSP430_HAS_FRAM_FR5XX__)
// ---------------------------------------------------------------------------------------------------------------------
// Clock initialization for MSP430 FRAM with FRAM_FR5XX
// ---------------------------------------------------------------------------------------------------------------------
// Includes FR5739
// Note: Untested as I have no boards that use this
static void initClocks(){
    CSCTL0 = CSKEY;                             // Enable Access to CS Registers
  
    CSCTL2 &= ~SELM_7;                          // Clear selected Main CLK Source
    CSCTL2 |= SELM__DCOCLK;                     // Use DCO as Main Clock Source
    CSCTL3 &= ~(DIVM_3 | DIVS_3);               // clear DIVM Bits
#if F_CPU == 24000000L
    CSCTL1 = DCOFSEL0 | DCOFSEL1 | DCORSEL;     // Level 2 / Range 1 : 24.0MHz
#elif F_CPU == 16000000L
    CSCTL1 = DCORSEL;                           // Level 0 / Range 1 : 16.0MHz
#elif F_CPU == 12000000L
    CSCTL1 = DCOFSEL0 | DCOFSEL1 | DCORSEL;     // Level 2 / Range 1 : 24.0MHz
    CSCTL3 |= DIVM_1;                           // Div = 2
#elif F_CPU == 8000000L
    CSCTL1 = DCOFSEL0 | DCOFSEL1;               // Level 2 / Range 0 : 8.0MHz
#elif F_CPU == 4000000L
    CSCTL1 = DCOFSEL0 | DCOFSEL1;               // Level 2 / Range 0 : 8.0MHz
    CSCTL3 |= DIVM_1;                           // Div = 2
#elif F_CPU == 2000000L
    CSCTL1 = DCOFSEL0 | DCOFSEL1;               // Level 2 / Range 0 : 8.0MHz
    CSCTL3 |= DIVM_2;                           // Div = 4
#elif F_CPU == 1000000L
    CSCTL1 = DCOFSEL0 | DCOFSEL1;               // Level 2 / Range 0 : 8.0MHz
    CSCTL3 |= DIVM_3;                           // Div = 8
#else
#error Invalid CPU frequency for this chip!
#endif

    // Setup pins for ACLK setup
    PJOUT = 0xFF;                               // All pins output
    PJOUT = 0;                                  // All pins low
    PJSEL0 = BIT4 | BIT5;                       // PJ.4 and PJ.5 as XTAL
    CSCTL4 &= ~XT1OFF;                          // Enable LXFT (XT1)

    // Wait up to 2 seconds for 32768 LXFT oscillator to start
    // Started when fault flag does not get set
#ifndef NOLFXT1
    unsigned int timeout = 4;
    do{
        timeout--;
        CSCTL5 &= ~XT1OFFG;                     // Clear oscillator fault flag
        SFRIFG1 &= ~OFIFG;                      // Clear fault interrupt flag
        __delay_cycles(500000L * 
                        (F_CPU/1000000L));      // Delay 500ms
        if(timeout == 0) break;                 // Timed out
    }while(SFRIFG1 & OFIFG);
#else
    unsigned int timeout = 0;
#endif
    if(timeout == 0){
        // Exact frequency varies between devices and have a large range
        // 8kHz seems to be a reasonable middle ground...
        // Probably not that imporant what this is set to. Not really any reason
        // to disable LXFT on these devices. There are dedicated pins for it.
        // Usually, devices operate without LXFT because the pins are shared
        // with GPIO. That is not the case here.
        aclk_freq = 8000;                       // ACLK = VLO.
        CSCTL2 |= SELA__VLOCLK;                 // ACLK from VLO
        CSCTL4 |= XT1OFF;                       // Disable LXFT (XT1)     
    }else{
        aclk_freq = 32768;
    }
}
// ---------------------------------------------------------------------------------------------------------------------
#elif defined(__MSP430_HAS_UCS__)
// ---------------------------------------------------------------------------------------------------------------------
// Clock initialization for MSP430 chips with universal clock system
// ---------------------------------------------------------------------------------------------------------------------
// Includes F5529
// Note: Untested as I have no boards that use this
static void initClocks(){
    PMMCTL0_H = PMMPW_H;             // open PMM
    SVSMLCTL &= ~SVSMLRRL_7;         // reset
    PMMCTL0_L = PMMCOREV_0;          //
    
    PMMIFG &= ~(SVSMLDLYIFG|SVMLVLRIFG|SVMLIFG);  // clear flags
    SVSMLCTL = (SVSMLCTL & ~SVSMLRRL_7) | SVSMLRRL_1;
    while ((PMMIFG & SVSMLDLYIFG) == 0); // wait till settled
    while ((PMMIFG & SVMLIFG) == 0); // wait for flag
    PMMCTL0_L = (PMMCTL0_L & ~PMMCOREV_3) | PMMCOREV_1; // set VCore for lext Speed
    while ((PMMIFG & SVMLVLRIFG) == 0);  // wait till level reached

    PMMIFG &= ~(SVSMLDLYIFG|SVMLVLRIFG|SVMLIFG);  // clear flags
    SVSMLCTL = (SVSMLCTL & ~SVSMLRRL_7) | SVSMLRRL_2;
    while ((PMMIFG & SVSMLDLYIFG) == 0); // wait till settled
    while ((PMMIFG & SVMLIFG) == 0); // wait for flag
    PMMCTL0_L = (PMMCTL0_L & ~PMMCOREV_3) | PMMCOREV_2; // set VCore for lext Speed
    while ((PMMIFG & SVMLVLRIFG) == 0);  // wait till level reached

    PMMIFG &= ~(SVSMLDLYIFG|SVMLVLRIFG|SVMLIFG);  // clear flags
    SVSMLCTL = (SVSMLCTL & ~SVSMLRRL_7) | SVSMLRRL_3;
    while ((PMMIFG & SVSMLDLYIFG) == 0); // wait till settled
    while ((PMMIFG & SVMLIFG) == 0); // wait for flag
    PMMCTL0_L = (PMMCTL0_L & ~PMMCOREV_3) | PMMCOREV_3; // set VCore for lext Speed
    while ((PMMIFG & SVMLVLRIFG) == 0);  // wait till level reached
    SVSMHCTL &= ~(SVMHE+SVSHE);         // Disable High side SVS 
    SVSMLCTL &= ~(SVMLE+SVSLE);         // Disable Low side SVS

    PMMCTL0_H = 0;                   // lock PMM

    UCSCTL0 = 0;                     // set lowest Frequency
#if F_CPU == 25000000L
    UCSCTL1 = DCORSEL_6;             //Range 6
    UCSCTL2 = 0x1176;                //Loop Control Setting
    UCSCTL3 = SELREF__REFOCLK;       //REFO for FLL
    UCSCTL4 = SELA__XT1CLK|SELM__DCOCLK|SELS__DCOCLK;  //Select clock sources
    UCSCTL7 &= ~(0x07);               //Clear Fault flags
#elif F_CPU == 24000000L
    UCSCTL1 = DCORSEL_6;             //Range 6
    UCSCTL2 = 0x116D;                //Loop Control Setting
    UCSCTL3 = SELREF__REFOCLK;       //REFO for FLL
    UCSCTL4 = SELA__XT1CLK|SELM__DCOCLK|SELS__DCOCLK;  //Select clock sources
    UCSCTL7 &= ~(0x07);               //Clear Fault flags
#elif F_CPU == 16000000L
    UCSCTL1 = DCORSEL_6;             //Range 6
    UCSCTL2 = 0x11E7;                //Loop Control Setting
    UCSCTL3 = SELREF__REFOCLK;       //REFO for FLL
    UCSCTL4 = SELA__XT1CLK|SELM__DCOCLKDIV|SELS__DCOCLKDIV;  //Select clock sources
    UCSCTL7 &= ~(0x07);               //Clear Fault flags
#elif F_CPU == 12000000L
    UCSCTL1 = DCORSEL_6;             //Range 6
    UCSCTL2 = 0x116D;                //Loop Control Setting
    UCSCTL3 = SELREF__REFOCLK;       //REFO for FLL
    UCSCTL4 = SELA__XT1CLK|SELM__DCOCLKDIV|SELS__DCOCLKDIV;  //Select clock sources
    UCSCTL7 &= ~(0x07);               //Clear Fault flags
#elif F_CPU == 8000000L
    UCSCTL1 = DCORSEL_5;             //Range 6
    UCSCTL2 = 0x10F3;                //Loop Control Setting
    UCSCTL3 = SELREF__REFOCLK;       //REFO for FLL
    UCSCTL4 = SELA__XT1CLK|SELM__DCOCLKDIV|SELS__DCOCLKDIV;  //Select clock sources
    UCSCTL7 &= ~(0x07);               //Clear Fault flags
#elif F_CPU == 1000000L
    UCSCTL1 = DCORSEL_2;             //Range 6
    UCSCTL2 = 0x101D;                //Loop Control Setting
    UCSCTL3 = SELREF__REFOCLK;       //REFO for FLL
    UCSCTL4 = SELA__XT1CLK|SELM__DCOCLKDIV|SELS__DCOCLKDIV;  //Select clock sources
    UCSCTL7 &= ~(0x07);               //Clear Fault flags
#else
#error Invalid CPU frequency for this chip!
#endif

    // ACLK configuration

    P5SEL |= BIT4 + BIT5;
    P5DIR |= BIT2 + BIT3;
    UCSCTL6 &= ~(XT1OFF);
    UCSCTL6 |= XCAP_3;

#ifndef NOLFXT1
    unsigned int timeout = 4;
    do{
        timeout--;
        UCSCTL7 &= ~(XT2OFFG + XT1LFOFFG + DCOFFG);
        SFRIFG1 &= ~OFIFG;
        __delay_cycles(500000L * 
                        (F_CPU/1000000L));      // Delay 500ms
        if(timeout == 0) break;                 // Timed out
    }while(SFRIFG1 & OFIFG);
#else
    unsigned int timeout = 0;
#endif
    if(timeout == 0){
        UCSCTL4 &= ~SELA_7;                     // Clear ACLK selection bits
        UCSCTL4 |= SELA__REFOCLK;               // Source from REFO
        aclk_freq = 32768;
    }else{
        UCSCTL4 &= ~SELA_7;                     // Clear ACLK selection bits
        UCSCTL4 |= SELA__XT1CLK;                // Source from LFXT1
        aclk_freq = 32768;
    }
    UCSCTL6 &= ~(XT1DRIVE_3);
}
// ---------------------------------------------------------------------------------------------------------------------

#else
static void initClocks(){
#error Clock configuration unknown for this chip!
}
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Watchdog (interval) timer & timing
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Note: This formula is fine as long as F_CPU is at least 1MHz
//       If lower, this will be zero
#define CYCLES_PER_US           (F_CPU / (1000000L))

// Used for WDT interval timer
#if F_CPU < 8000000L
#define TICKS_PER_WDT_OVERFLOW 512
#else
#define TICKS_PER_WDT_OVERFLOW 8192
#endif

// us per WDT overflow (integer)
#define MICROSECONDS_PER_WDT_OVERFLOW (TICKS_PER_WDT_OVERFLOW / CYCLES_PER_US)

// Milliseconds (integer and fractional part of 1000) per WDT interrupt
#define MILLIS_INC (MICROSECONDS_PER_WDT_OVERFLOW / 1000)                                           
#define FRACT_INC (MICROSECONDS_PER_WDT_OVERFLOW % 1000)

unsigned long millis(void){
    unsigned long m;
    uint16_t state = __get_interrupt_state();
	__disable_interrupt();
    m = wdt_millis;
    __set_interrupt_state(state);
    return m;
}

unsigned long micros(void){
    unsigned long m;
    uint16_t state = __get_interrupt_state();
	__disable_interrupt();
    m = wdt_overflow_count;
    __set_interrupt_state(state);
    return m * MICROSECONDS_PER_WDT_OVERFLOW;
}

void delay(unsigned long ms){
    unsigned long start = micros();
    uint16_t state = __get_interrupt_state();       // Will need to enable during delay
    while(ms > 0){
        if(micros() - start >= 1000){
            ms--;
            start += 1000;
        }
        __bis_SR_register(LPM0_bits+GIE);           // GIE enables interrupts
    }
    __set_interrupt_state(state);                   // Restore interrupt state
}

// Note: Not acurate for large values. As indicated in arduino language reference
//       this is not to be used for delays more than a few thousand microseconds.
//       If too large a value is used, a very short delay will result
//       The max working value depends on clock speed
//       Likewise, there is a minimum dealy and a resolution limit
//       Min delay is due to function call overhead
//         F_CPU | Max Delay | Min Delay | Resolution
//       ----------------------------------------------
//         24MHz | 10922us   | 1us       | 1us
//         20MHz | 13107us   | 1us       | 1us
//         16MHz | 16383us   | 1us       | 1us
//         12MHz | 21845us   | 1us       | 1us
//          8MHz | 32767us   | 2us       | 1us
//          4MHz | 65535us   | 4us       | 1us
//          2MHz | 65535us   | 9us       | 2us
//          1MHz | 65535us   | 18us      | 4us
void delayMicroseconds(unsigned int us){
    // Note: Function call overhead determined from comments in energia code pertaining
    //       to 20 MHz clock
    // It states that 2 cycles more than function call overhead are exactly 1us delay
    // Since 20 cycles would be required for a 1us delay, this means the funciton call
    // overhead is 18 cycles. This makes sense given the other numbers in the comments
    //
    // Reference: https://www.ti.com/sc/docs/products/micro/msp430/userguid/as_5.pdf
    //
    // This is also consistent with the following (which is generated for a call to this function using CCS w/ MSPGCC)
    // calling function
    //      MOV.W    @R1, R12
    //      CALL    #delayMicroseconds
    //
    // callee function
    //      function_operations
    //      RET
    //
    // CALL: 1xADD, 1xSUB, 3xMOV
    //      Add 2 to PC (one ADD instruction)
    //      Push to stack (one push instruction)
    //          Subtract 2 from PC (one SUB)
    //          Store in SP (one MOV)
    //          Store src at SP (one MOV)
    //      Move func_addr to PC (one MOV instruction)
    // RET: 2xADD, 3xMOV
    //      Store top of stack value (frame pointer) to PC (one POP)
    //          MOV to dest (one MOV)
    //          ADD 2 to SP (one ADD)
    //          MOV to SP (one MOV)
    //      Add 2 to SP (one ADD)
    //      Store in SP (one MOV)
    // 
    // TOTAL:
    //      3xADD * 1 cycle  = 3 cycles
    //      6xMOV * 2 cycles = 12 cycles
    //      1xSUB * 1 cycle  = 1 cycle
    //                         16 cycles
    // But some MOVs not to registers (so two cycles)
    // These are PUSH and POP data moves
    // So total is actually 18 cycles
    

#if F_CPU == 24000000L
    // 24 MHz clock
    // Function call overhead is 6 cycles short of 1us
    asm volatile (
        "nop" "\n\t"
        "nop" "\n\t"
        "nop" "\n\t"
        "nop" "\n\t"
        "nop" "\n\t"
        "nop"
    );
    if(--us == 0)
        return;
    
    // Following loop is 4 cycles per iteration (4/24 = 1/6us)
    // So multiply us by 6 -> loop iterations
    us = (us << 2) + (us << 1);

    // Account for time taken in above operations
    us -= 3;
#elif F_CPU == 20000000L
    // 20 MHz clock
    // Function call overhead is 2 cycles short of 1us
    asm volatile (
        "nop" "\n\t"
        "nop"
    );
    if(--us == 0)
        return;
    
    // Following loop is 4 cycles per iteration (4/20 = 1/5us)
    // So multiply us by 6 -> loop iterations
    us = (us << 2) + us;

    // Account for time taken in above operations
    us -= 2;
#elif F_CPU == 16000000L
    // 16 MHz clock
    // Function call overhead is 1.125us, so just return
    if(--us == 0)
        return;
    
    // Loop takes 4 cycles (0.25us) per iteration
    us <<= 2;

    // Account for time in previous commands
    us -= 1;
#elif F_CPU == 12000000L
    // 12 MHz clock
    // Function call overhead is 1.5us, so just return if sub 2
    if(--us == 0)
        return;
    if(--us == 0)
        return;
    
    // Loop takes 4 cycles (1/3 us) per iteration
    us = (us << 1) + us;

    // Account for time in previous commands
    us -= 1;
#elif F_CPU == 8000000L
    // 8 MHz clock
    // Function call overhead is 2.25us, so just return if 1 or 2
    if(--us == 0)
        return;
    if(--us == 0)
        return;
    
    // Loop takes 4 cycles (0.5us) per iteration
    us <<= 1;

    // Account for time in previous commands
    us -= 1;
#elif F_CPU == 4000000L
    // 4 MHz clock
    // Function call overhead is 4.5us (so return if 5us or less)
    if(--us == 0)
        return;
    if(--us == 0)
        return;
    if(--us == 0)
        return;
    if(--us == 0)
        return;
    if(--us == 0)
        return;

    // Loop takes 4 cycles (1us) per iteration
    // us >>= 0;

    // Account for time in previous commands
    us -= 1;
#elif F_CPU == 2000000L
    // 2MHz clock
    // Function call overhead is 9us (so return if 9us or less)
    if(--us == 0)
        return;
    if(--us == 0)
        return;
    if(--us == 0)
        return;
    if(--us == 0)
        return;
    if(--us == 0)
        return;
    if(--us == 0)
        return;
    if(--us == 0)
        return;
    if(--us == 0)
        return;
    if(--us == 0)
        return;

    // Loop takes 4 cycles (2us) per iteration
    us >>= 1;

    // Can't account for time of previous commands b/c us may be zero
#elif F_CPU == 1000000L
    // 1MHz clock
    // Function call overhead is 9us (so return if 18us or less)
    if(--us == 0)
        return;
    if(--us == 0)
        return;
    if(--us == 0)
        return;
    if(--us == 0)
        return;
    if(--us == 0)
        return;
    if(--us == 0)
        return;
    if(--us == 0)
        return;
    if(--us == 0)
        return;
    if(--us == 0)
        return;
    if(--us == 0)
        return;
    if(--us == 0)
        return;
    if(--us == 0)
        return;
    if(--us == 0)
        return;
    if(--us == 0)
        return;
    if(--us == 0)
        return;
    if(--us == 0)
        return;
    if(--us == 0)
        return;
    if(--us == 0)
        return;

    // Loop takes 4 cycles (4us) per iteration
    us >>= 2;

    // Can't account for time of previous commands b/c us may be zero
#else
#error Unsupported clock frequency!
#endif

    // Loop takes 4 cycles per iteration
    asm volatile (
            "L1: nop \n\t"   
            "dec.w %[us] \n\t"
            "jnz L1 \n\t"
            : [us] "=r" (us) : "[us]" (us)
    );
}

/**
 * Configure WDT in interval mode
 * This mode will not reset the chip when it expires. It is used to generate
 * a periodic interrupt used for system timing.
 */
static void enableWdtInterval(){
    // For F_CPU < 8MHz use MCLK / 512
    // For F_CPU >= 8MHz use MCLK / 8192
#if F_CPU < 8000000L
    WDTCTL = WDTPW | WDTTMSEL | WDTCNTCL | WDT_MDLY_0_5;
#else
    WDTCTL = WDTPW | WDTTMSEL | WDTCNTCL | WDT_MDLY_8;
#endif

    // Enable WDT interrupt
#ifdef __MSP430_HAS_SFR__
    SFRIE1 |= WDTIE;
#else
    IE1 |= WDTIE;
#endif
}

__interrupt_vec(WDT_VECTOR) void watchdog_isr (void){
    // copy these to local variables so they can be stored in registers
    // (volatile variables must be read from memory on every access)
    unsigned long m = wdt_millis;
    unsigned int f = wdt_frac;

    m += MILLIS_INC;
    f += FRACT_INC;
    if (f >= 1000) {
        f -= 1000;
        m += 1;
    }

    wdt_frac = f;
    wdt_millis = m;
    wdt_overflow_count++;

    // Exit from any low power mode
    __bic_SR_register_on_exit(LPM3_bits);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// General initialization
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * Initialize MSP430 chip
 */
void init(){
    WDTCTL = WDTPW | WDTHOLD;               // Disable watchdog timer
#if defined(LOCKLPM5)
     PMMCTL0_H = PMMPW_H;                   // Open PMM
     PM5CTL0 &= ~LOCKLPM5;                  // Unlock IO ports (FR59xx)
     PMMCTL0_H = 0;                         // Lock PMM
#endif
    initClocks();                           // Initialize clocks
    enableWdtInterval();                    // Enable WDT (used as interval timer for ms timing)
    __enable_interrupt();                   // Enable interrupts
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

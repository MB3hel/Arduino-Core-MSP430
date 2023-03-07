#ifdef ARDUINO_MAIN

#include <msp430.h>
#include <stdint.h>

// port_in[x] = PxIN
const uintptr_t port_in[] = {
    0,
#ifdef __MSP430_HAS_PORT1_R__
    (const uintptr_t)(&P1IN),
#endif
#ifdef __MSP430_HAS_PORT2_R__
    (const uintptr_t)(&P2IN),
#endif
#ifdef __MSP430_HAS_PORT3_R__
    (const uintptr_t)(&P3IN),
#endif
#ifdef __MSP430_HAS_PORT4_R__
    (const uintptr_t)(&P4IN),
#endif
#ifdef __MSP430_HAS_PORT5_R__
    (const uintptr_t)(&P5IN),
#endif
#ifdef __MSP430_HAS_PORT6_R__
    (const uintptr_t)(&P6IN),
#endif
#ifdef __MSP430_HAS_PORT7_R__
    (const uintptr_t)(&P7IN),
#endif
#ifdef __MSP430_HAS_PORT8_R__
    (const uintptr_t)(&P8IN),
#endif
#ifdef __MSP430_HAS_PORT9_R__
    (const uintptr_t)(&P9IN),
#endif
#ifdef __MSP430_HAS_PORT10_R__
    (const uintptr_t)(&P10IN),
#endif
#ifdef __MSP430_HAS_PORT11_R__
    (const uintptr_t)(&P11IN),
#endif
};

// port_out[x] = PxOUT
const uintptr_t port_out[] = {
    0,
#ifdef __MSP430_HAS_PORT1_R__
    (const uintptr_t)(&P1OUT),
#endif
#ifdef __MSP430_HAS_PORT2_R__
    (const uintptr_t)(&P2OUT),
#endif
#ifdef __MSP430_HAS_PORT3_R__
    (const uintptr_t)(&P3OUT),
#endif
#ifdef __MSP430_HAS_PORT4_R__
    (const uintptr_t)(&P4OUT),
#endif
#ifdef __MSP430_HAS_PORT5_R__
    (const uintptr_t)(&P5OUT),
#endif
#ifdef __MSP430_HAS_PORT6_R__
    (const uintptr_t)(&P6OUT),
#endif
#ifdef __MSP430_HAS_PORT7_R__
    (const uintptr_t)(&P7OUT),
#endif
#ifdef __MSP430_HAS_PORT8_R__
    (const uintptr_t)(&P8OUT),
#endif
#ifdef __MSP430_HAS_PORT9_R__
    (const uintptr_t)(&P9OUT),
#endif
#ifdef __MSP430_HAS_PORT10_R__
    (const uintptr_t)(&P10OUT),
#endif
#ifdef __MSP430_HAS_PORT11_R__
    (const uintptr_t)(&P11OUT),
#endif
};

// port_sel0[x] = PxSEL0 or PxSEL
const uintptr_t port_sel0[] = {
    0,
#ifdef __MSP430_HAS_PORT1_R__
#if defined(__MSP430_HAS_P1SEL__)
    (const uintptr_t)(&P1SEL),
#else
    (const uintptr_t)(&P1SEL0),
#endif
#endif
#ifdef __MSP430_HAS_PORT2_R__
#if defined(__MSP430_HAS_P2SEL__)
    (const uintptr_t)(&P2SEL),
#else
    (const uintptr_t)(&P2SEL0),
#endif
#endif
#ifdef __MSP430_HAS_PORT3_R__
#if defined(__MSP430_HAS_P3SEL__)
    (const uintptr_t)(&P3SEL),
#else
    (const uintptr_t)(&P3SEL0),
#endif
#endif
#ifdef __MSP430_HAS_PORT4_R__
#if defined(__MSP430_HAS_P4SEL__)
    (const uintptr_t)(&P4SEL),
#else
    (const uintptr_t)(&P4SEL0),
#endif
#endif
#ifdef __MSP430_HAS_PORT5_R__
#if defined(__MSP430_HAS_P5SEL__)
    (const uintptr_t)(&P5SEL),
#else
    (const uintptr_t)(&P5SEL0),
#endif
#endif
#ifdef __MSP430_HAS_PORT6_R__
#if defined(__MSP430_HAS_P6SEL__)
    (const uintptr_t)(&P6SEL),
#else
    (const uintptr_t)(&P6SEL0),
#endif
#endif
#ifdef __MSP430_HAS_PORT7_R__
#if defined(__MSP430_HAS_P7SEL__)
    (const uintptr_t)(&P7SEL),
#else
    (const uintptr_t)(&P7SEL0),
#endif
#endif
#ifdef __MSP430_HAS_PORT8_R__
#if defined(__MSP430_HAS_P8SEL__)
    (const uintptr_t)(&P8SEL),
#else
    (const uintptr_t)(&P8SEL0),
#endif
#endif
#ifdef __MSP430_HAS_PORT9_R__
#if defined(__MSP430_HAS_P9SEL__)
    (const uintptr_t)(&P9SEL),
#else
    (const uintptr_t)(&P9SEL0),
#endif
#endif
#ifdef __MSP430_HAS_PORT10_R__
#if defined(__MSP430_HAS_P10SEL__)
    (const uintptr_t)(&P10SEL),
#else
    (const uintptr_t)(&P10SEL0),
#endif
#endif
#ifdef __MSP430_HAS_PORT11_R__
#if defined(__MSP430_HAS_P11SEL__)
    (const uintptr_t)(&P11SEL),
#else
    (const uintptr_t)(&P11SEL0),
#endif
#endif
};

// port_sel1[x] = PxSEL1 or PxSEL2
const uintptr_t port_sel1[] = {
    0,
#ifdef __MSP430_HAS_PORT1_R__
#if defined(__MSP430_HAS_P1SEL2__)
    (const uintptr_t)(&P1SEL2),
#else
    (const uintptr_t)(&P1SEL1),
#endif
#endif
#ifdef __MSP430_HAS_PORT2_R__
#if defined(__MSP430_HAS_P2SEL2__)
    (const uintptr_t)(&P2SEL2),
#else
    (const uintptr_t)(&P2SEL1),
#endif
#endif
#ifdef __MSP430_HAS_PORT3_R__
#if defined(__MSP430_HAS_P3SEL2__)
    (const uintptr_t)(&P3SEL2),
#else
    (const uintptr_t)(&P3SEL1),
#endif
#endif
#ifdef __MSP430_HAS_PORT4_R__
#if defined(__MSP430_HAS_P4SEL2__)
    (const uintptr_t)(&P4SEL2),
#else
    (const uintptr_t)(&P4SEL1),
#endif
#endif
#ifdef __MSP430_HAS_PORT5_R__
#if defined(__MSP430_HAS_P5SEL2__)
    (const uintptr_t)(&P5SEL2),
#else
    (const uintptr_t)(&P5SEL1),
#endif
#endif
#ifdef __MSP430_HAS_PORT6_R__
#if defined(__MSP430_HAS_P6SEL2__)
    (const uintptr_t)(&P6SEL2),
#else
    (const uintptr_t)(&P6SEL1),
#endif
#endif
#ifdef __MSP430_HAS_PORT7_R__
#if defined(__MSP430_HAS_P7SEL2__)
    (const uintptr_t)(&P7SEL2),
#else
    (const uintptr_t)(&P7SEL1),
#endif
#endif
#ifdef __MSP430_HAS_PORT8_R__
#if defined(__MSP430_HAS_P8SEL2__)
    (const uintptr_t)(&P8SEL2),
#else
    (const uintptr_t)(&P8SEL1),
#endif
#endif
#ifdef __MSP430_HAS_PORT9_R__
#if defined(__MSP430_HAS_P9SEL2__)
    (const uintptr_t)(&P9SEL2),
#else
    (const uintptr_t)(&P9SEL1),
#endif
#endif
#ifdef __MSP430_HAS_PORT10_R__
#if defined(__MSP430_HAS_P10SEL2__)
    (const uintptr_t)(&P10SEL2),
#else
    (const uintptr_t)(&P10SEL1),
#endif
#endif
#ifdef __MSP430_HAS_PORT11_R__
#if defined(__MSP430_HAS_P11SEL2__)
    (const uintptr_t)(&P11SEL2),
#else
    (const uintptr_t)(&P11SEL1),
#endif
#endif
};

// port_dir[x] = PxDIR
const uintptr_t port_dir[] = {
    0,
#ifdef __MSP430_HAS_PORT1_R__
    (const uintptr_t)(&P1DIR),
#endif
#ifdef __MSP430_HAS_PORT2_R__
    (const uintptr_t)(&P2DIR),
#endif
#ifdef __MSP430_HAS_PORT3_R__
    (const uintptr_t)(&P3DIR),
#endif
#ifdef __MSP430_HAS_PORT4_R__
    (const uintptr_t)(&P4DIR),
#endif
#ifdef __MSP430_HAS_PORT5_R__
    (const uintptr_t)(&P5DIR),
#endif
#ifdef __MSP430_HAS_PORT6_R__
    (const uintptr_t)(&P6DIR),
#endif
#ifdef __MSP430_HAS_PORT7_R__
    (const uintptr_t)(&P7DIR),
#endif
#ifdef __MSP430_HAS_PORT8_R__
    (const uintptr_t)(&P8DIR),
#endif
#ifdef __MSP430_HAS_PORT9_R__
    (const uintptr_t)(&P9DIR),
#endif
#ifdef __MSP430_HAS_PORT10_R__
    (const uintptr_t)(&P10DIR),
#endif
#ifdef __MSP430_HAS_PORT11_R__
    (const uintptr_t)(&P11DIR),
#endif
};

// port_ren[x] = PxREN
const uintptr_t port_ren[] = {
    0,
#ifdef __MSP430_HAS_PORT1_R__
    (const uintptr_t)(&P1REN),
#endif
#ifdef __MSP430_HAS_PORT2_R__
    (const uintptr_t)(&P2REN),
#endif
#ifdef __MSP430_HAS_PORT3_R__
    (const uintptr_t)(&P3REN),
#endif
#ifdef __MSP430_HAS_PORT4_R__
    (const uintptr_t)(&P4REN),
#endif
#ifdef __MSP430_HAS_PORT5_R__
    (const uintptr_t)(&P5REN),
#endif
#ifdef __MSP430_HAS_PORT6_R__
    (const uintptr_t)(&P6REN),
#endif
#ifdef __MSP430_HAS_PORT7_R__
    (const uintptr_t)(&P7REN),
#endif
#ifdef __MSP430_HAS_PORT8_R__
    (const uintptr_t)(&P8REN),
#endif
#ifdef __MSP430_HAS_PORT9_R__
    (const uintptr_t)(&P9REN),
#endif
#ifdef __MSP430_HAS_PORT10_R__
    (const uintptr_t)(&P10REN),
#endif
#ifdef __MSP430_HAS_PORT11_R__
    (const uintptr_t)(&P11REN),
#endif
};

// port_ies[x] = PxIES
const uintptr_t port_ies[] = {
    0,
#ifdef PORT1_VECTOR
    (const uintptr_t)(&P1IES),
#endif
#ifdef PORT2_VECTOR
    (const uintptr_t)(&P2IES),
#endif
#ifdef PORT3_VECTOR
    (const uintptr_t)(&P3IES),
#endif
#ifdef PORT4_VECTOR
    (const uintptr_t)(&P4IES),
#endif
#ifdef PORT5_VECTOR
    (const uintptr_t)(&P5IES),
#endif
#ifdef PORT6_VECTOR
    (const uintptr_t)(&P6IES),
#endif
#ifdef PORT7_VECTOR
    (const uintptr_t)(&P7IES),
#endif
#ifdef PORT8_VECTOR
    (const uintptr_t)(&P8IES),
#endif
#ifdef PORT9_VECTOR
    (const uintptr_t)(&P9IES),
#endif
#ifdef PORT10_VECTOR
    (const uintptr_t)(&P10IES),
#endif
#ifdef PORT11_VECTOR
    (const uintptr_t)(&P11IES),
#endif
};

// port_ie[x] = PxIE
const uintptr_t port_ie[] = {
    0,
#ifdef PORT1_VECTOR
    (const uintptr_t)(&P1IE),
#endif
#ifdef PORT2_VECTOR
    (const uintptr_t)(&P2IE),
#endif
#ifdef PORT3_VECTOR
    (const uintptr_t)(&P3IE),
#endif
#ifdef PORT4_VECTOR
    (const uintptr_t)(&P4IE),
#endif
#ifdef PORT5_VECTOR
    (const uintptr_t)(&P5IE),
#endif
#ifdef PORT6_VECTOR
    (const uintptr_t)(&P6IE),
#endif
#ifdef PORT7_VECTOR
    (const uintptr_t)(&P7IE),
#endif
#ifdef PORT8_VECTOR
    (const uintptr_t)(&P8IE),
#endif
#ifdef PORT9_VECTOR
    (const uintptr_t)(&P9IE),
#endif
#ifdef PORT10_VECTOR
    (const uintptr_t)(&P10IE),
#endif
#ifdef PORT11_VECTOR
    (const uintptr_t)(&P11IE),
#endif
};

// port_ifg[x] = PxIFG
const uintptr_t port_ifg[] = {
    0,
#ifdef PORT1_VECTOR
    (const uintptr_t)(&P1IFG),
#endif
#ifdef PORT2_VECTOR
    (const uintptr_t)(&P2IFG),
#endif
#ifdef PORT3_VECTOR
    (const uintptr_t)(&P3IFG),
#endif
#ifdef PORT4_VECTOR
    (const uintptr_t)(&P4IFG),
#endif
#ifdef PORT5_VECTOR
    (const uintptr_t)(&P5IFG),
#endif
#ifdef PORT6_VECTOR
    (const uintptr_t)(&P6IFG),
#endif
#ifdef PORT7_VECTOR
    (const uintptr_t)(&P7IFG),
#endif
#ifdef PORT8_VECTOR
    (const uintptr_t)(&P8IFG),
#endif
#ifdef PORT9_VECTOR
    (const uintptr_t)(&P9IFG),
#endif
#ifdef PORT10_VECTOR
    (const uintptr_t)(&P10IFG),
#endif
#ifdef PORT11_VECTOR
    (const uintptr_t)(&P11IFG),
#endif
};

#endif // ARDUINO_MAIN
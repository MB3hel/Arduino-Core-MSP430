// =============================================================================
// Pinout
// =============================================================================
//                             +-\/-+
//                     VCC    1|    |20  GND
//         (A0)        P1.0   2|    |19  P2.6             (XIN)
//  (RX0)  (A1)        P1.1   3|    |18  P2.7             (XOUT)
//  (TX0)  (A2) (PWM)  P1.2   4|    |17  TEST
//         (A3)        P1.3   5|    |16  RST
//         (A4)        P1.4   6|    |15  P1.7  (PWM) (A7) (MISO)
// (SCLK)  (A5)        P1.5   7|    |14  P1.6  (PWM) (A6) (MOSI)
//   (CS)              P2.0   8|    |13  P2.5  (PWM)
//  (SCL)       (PWM)  P2.1   9|    |12  P2.4  (PWM)
//  (SDA)       (PWM)  P2.2  10|    |11  P2.3
//                             +----+
// =============================================================================
// Serial uses TX0 and RX0 and is available as the ez-FET backchannel UART
// Wire is software I2C (master only) using SCL and SDA
// SPI uses SCLK, MISO, and MOSI pins. CS is the default chip select
// =============================================================================


#pragma once

#include <stdint.h>


#define MAX_PINNUM                  (20)
#define NUM_DIGITAL_PINS            (16)
// TODO: #define NUM_ANALOG_PINS             (8)

// TODO: analogInputToDigitalPin macro
// TODO: digitalPinHasPWM() macro


#define PIN_SPI_SS                  (8)
#define PIN_SPI_MOSI                (14)
#define PIN_SPI_MISO                (15)
#define PIN_SPI_SCK                 (7)

static const uint8_t SS   = PIN_SPI_SS;
static const uint8_t MOSI = PIN_SPI_MOSI;
static const uint8_t MISO = PIN_SPI_MISO;
static const uint8_t SCK  = PIN_SPI_SCK;

#define WIRE_IS_SW                  (1)
#define PIN_WIRE_SDA                (10)
#define PIN_WIRE_SCL                (9)

static const uint8_t SDA = PIN_WIRE_SDA;
static const uint8_t SCL = PIN_WIRE_SCL;

// TODO: analog pins

// TODO: digitalPinToInterrupt macro


#ifdef ARDUINO_MAIN

const uintptr_t pin_inreg[] = {
    0,                                                  // Placeholder. We count from 1 not 0.
    0,                                                  // VCC
    (const uintptr_t)(&P1IN),                           // P1.0
    (const uintptr_t)(&P1IN),                           // P1.1
    (const uintptr_t)(&P1IN),                           // P1.2
    (const uintptr_t)(&P1IN),                           // P1.3
    (const uintptr_t)(&P1IN),                           // P1.4
    (const uintptr_t)(&P1IN),                           // P1.5
    (const uintptr_t)(&P2IN),                           // P2.0
    (const uintptr_t)(&P2IN),                           // P2.1
    (const uintptr_t)(&P2IN),                           // P2.2
    (const uintptr_t)(&P2IN),                           // P2.3
    (const uintptr_t)(&P2IN),                           // P2.4
    (const uintptr_t)(&P2IN),                           // P2.5
    (const uintptr_t)(&P1IN),                           // P1.6
    (const uintptr_t)(&P1IN),                           // P1.7
    0,                                                  // RST
    0,                                                  // TEST
    (const uintptr_t)(&P2IN),                           // P2.7
    (const uintptr_t)(&P2IN),                           // P2.6
    0,                                                  // GND
};

const uintptr_t pin_outreg[] = {
    0,                                                  // Placeholder. We count from 1 not 0.
    0,                                                  // VCC
    (const uintptr_t)(&P1OUT),                          // P1.0
    (const uintptr_t)(&P1OUT),                          // P1.1
    (const uintptr_t)(&P1OUT),                          // P1.2
    (const uintptr_t)(&P1OUT),                          // P1.3
    (const uintptr_t)(&P1OUT),                          // P1.4
    (const uintptr_t)(&P1OUT),                          // P1.5
    (const uintptr_t)(&P2OUT),                          // P2.0
    (const uintptr_t)(&P2OUT),                          // P2.1
    (const uintptr_t)(&P2OUT),                          // P2.2
    (const uintptr_t)(&P2OUT),                          // P2.3
    (const uintptr_t)(&P2OUT),                          // P2.4
    (const uintptr_t)(&P2OUT),                          // P2.5
    (const uintptr_t)(&P1OUT),                          // P1.6
    (const uintptr_t)(&P1OUT),                          // P1.7
    0,                                                  // RST
    0,                                                  // TEST
    (const uintptr_t)(&P2OUT),                          // P2.7
    (const uintptr_t)(&P2OUT),                          // P2.6
    0,                                                  // GND
};

const uintptr_t pin_sel0reg[] = {
    0,                                                  // Placeholder. We count from 1 not 0.
    0,                                                  // VCC
    (const uintptr_t)(&P1SEL),                          // P1.0
    (const uintptr_t)(&P1SEL),                          // P1.1
    (const uintptr_t)(&P1SEL),                          // P1.2
    (const uintptr_t)(&P1SEL),                          // P1.3
    (const uintptr_t)(&P1SEL),                          // P1.4
    (const uintptr_t)(&P1SEL),                          // P1.5
    (const uintptr_t)(&P2SEL),                          // P2.0
    (const uintptr_t)(&P2SEL),                          // P2.1
    (const uintptr_t)(&P2SEL),                          // P2.2
    (const uintptr_t)(&P2SEL),                          // P2.3
    (const uintptr_t)(&P2SEL),                          // P2.4
    (const uintptr_t)(&P2SEL),                          // P2.5
    (const uintptr_t)(&P1SEL),                          // P1.6
    (const uintptr_t)(&P1SEL),                          // P1.7
    0,                                                  // RST
    0,                                                  // TEST
    (const uintptr_t)(&P2SEL),                          // P2.7
    (const uintptr_t)(&P2SEL),                          // P2.6
    0,                                                  // GND
};

const uintptr_t pin_sel1reg[] = {
    0,                                                  // Placeholder. We count from 1 not 0.
    0,                                                  // VCC
    (const uintptr_t)(&P1SEL2),                         // P1.0
    (const uintptr_t)(&P1SEL2),                         // P1.1
    (const uintptr_t)(&P1SEL2),                         // P1.2
    (const uintptr_t)(&P1SEL2),                         // P1.3
    (const uintptr_t)(&P1SEL2),                         // P1.4
    (const uintptr_t)(&P1SEL2),                         // P1.5
    (const uintptr_t)(&P2SEL2),                         // P2.0
    (const uintptr_t)(&P2SEL2),                         // P2.1
    (const uintptr_t)(&P2SEL2),                         // P2.2
    (const uintptr_t)(&P2SEL2),                         // P2.3
    (const uintptr_t)(&P2SEL2),                         // P2.4
    (const uintptr_t)(&P2SEL2),                         // P2.5
    (const uintptr_t)(&P1SEL2),                         // P1.6
    (const uintptr_t)(&P1SEL2),                         // P1.7
    0,                                                  // RST
    0,                                                  // TEST
    (const uintptr_t)(&P2SEL2),                         // P2.7
    (const uintptr_t)(&P2SEL2),                         // P2.6
    0,                                                  // GND
};

const uintptr_t pin_dirreg[] = {
    0,                                                  // Placeholder. We count from 1 not 0.
    0,                                                  // VCC
    (const uintptr_t)(&P1DIR),                          // P1.0
    (const uintptr_t)(&P1DIR),                          // P1.1
    (const uintptr_t)(&P1DIR),                          // P1.2
    (const uintptr_t)(&P1DIR),                          // P1.3
    (const uintptr_t)(&P1DIR),                          // P1.4
    (const uintptr_t)(&P1DIR),                          // P1.5
    (const uintptr_t)(&P2DIR),                          // P2.0
    (const uintptr_t)(&P2DIR),                          // P2.1
    (const uintptr_t)(&P2DIR),                          // P2.2
    (const uintptr_t)(&P2DIR),                          // P2.3
    (const uintptr_t)(&P2DIR),                          // P2.4
    (const uintptr_t)(&P2DIR),                          // P2.5
    (const uintptr_t)(&P1DIR),                          // P1.6
    (const uintptr_t)(&P1DIR),                          // P1.7
    0,                                                  // RST
    0,                                                  // TEST
    (const uintptr_t)(&P2DIR),                          // P2.7
    (const uintptr_t)(&P2DIR),                          // P2.6
    0,                                                  // GND
};

const uintptr_t pin_renreg[] = {
    0,                                                  // Placeholder. We count from 1 not 0.
    0,                                                  // VCC
    (const uintptr_t)(&P1REN),                          // P1.0
    (const uintptr_t)(&P1REN),                          // P1.1
    (const uintptr_t)(&P1REN),                          // P1.2
    (const uintptr_t)(&P1REN),                          // P1.3
    (const uintptr_t)(&P1REN),                          // P1.4
    (const uintptr_t)(&P1REN),                          // P1.5
    (const uintptr_t)(&P2REN),                          // P2.0
    (const uintptr_t)(&P2REN),                          // P2.1
    (const uintptr_t)(&P2REN),                          // P2.2
    (const uintptr_t)(&P2REN),                          // P2.3
    (const uintptr_t)(&P2REN),                          // P2.4
    (const uintptr_t)(&P2REN),                          // P2.5
    (const uintptr_t)(&P1REN),                          // P1.6
    (const uintptr_t)(&P1REN),                          // P1.7
    0,                                                  // RST
    0,                                                  // TEST
    (const uintptr_t)(&P2REN),                          // P2.7
    (const uintptr_t)(&P2REN),                          // P2.6
    0,                                                  // GND
};

const uint8_t pin_bitmask[] = {
    0,                                                  // Placeholder. We count from 1 not 0.
    0,                                                  // VCC
    BIT0,                                               // P1.0
    BIT1,                                               // P1.1
    BIT2,                                               // P1.2
    BIT3,                                               // P1.3
    BIT4,                                               // P1.4
    BIT5,                                               // P1.5
    BIT0,                                               // P2.0
    BIT1,                                               // P2.1
    BIT2,                                               // P2.2
    BIT3,                                               // P2.3
    BIT4,                                               // P2.4
    BIT5,                                               // P2.5
    BIT6,                                               // P1.6
    BIT7,                                               // P1.7
    0,                                                  // RST
    0,                                                  // TEST
    BIT7,                                               // P2.7
    BIT6,                                               // P2.6
    0,                                                  // GND
};

#endif // ARDUINO_MAIN


// These serial port names are intended to allow libraries and architecture-neutral
// sketches to automatically default to the correct port name for a particular type
// of use.  For example, a GPS module would normally connect to SERIAL_PORT_HARDWARE_OPEN,
// the first hardware serial port whose RX/TX pins are not dedicated to another use.
//
// SERIAL_PORT_MONITOR        Port which normally prints to the Arduino Serial Monitor
//
// SERIAL_PORT_USBVIRTUAL     Port which is USB virtual serial
//
// SERIAL_PORT_LINUXBRIDGE    Port which connects to a Linux system via Bridge library
//
// SERIAL_PORT_HARDWARE       Hardware serial port, physical RX & TX pins.
//
// SERIAL_PORT_HARDWARE_OPEN  Hardware serial ports which are open for use.  Their RX & TX
//                            pins are NOT connected to anything by default.
#define SERIAL_PORT_MONITOR   Serial
#define SERIAL_PORT_HARDWARE  Serial

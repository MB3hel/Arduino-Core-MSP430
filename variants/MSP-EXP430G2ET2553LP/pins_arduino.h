// =============================================================================
// Pinout
// =============================================================================
//                             +-\/-+
//                     VCC    1|    |20  GND
//         (A0)        P1.0   2|    |19  P2.6             (XIN)
//  (RX0)  (A1)        P1.1   3|    |18  P2.7             (XOUT)
//  (TX0)  (A2) (PWM)  P1.2   4|    |17  TEST
//         (A3)        P1.3   5|    |16  RST#
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


#define NUM_DIGITAL_PINS            (16)
#define NUM_ANALOG_PINS             (8)

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

#define PIN_A0                      (2)
#define PIN_A1                      (3)
#define PIN_A2                      (4)
#define PIN_A3                      (5)
#define PIN_A4                      (6)
#define PIN_A5                      (7)
#define PIN_A6                      (14)
#define PIN_A7                      (15)

static const uint8_t A0 = PIN_A0;
static const uint8_t A1 = PIN_A1;
static const uint8_t A2 = PIN_A2;
static const uint8_t A3 = PIN_A3;
static const uint8_t A4 = PIN_A4;
static const uint8_t A5 = PIN_A5;
static const uint8_t A6 = PIN_A6;
static const uint8_t A7 = PIN_A7;

// TODO: digitalPinToInterrupt macro


#ifdef ARDUINO_MAIN

// TODO: Lookup table for pin registers

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

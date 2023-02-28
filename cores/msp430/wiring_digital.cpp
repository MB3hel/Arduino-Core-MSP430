/**
 * @file wiring_digital.cpp
 * Derived from Energia MSP430 wiring_digital.c
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
/// Digital I/O
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void pinMode(pin_size_t pinNumber, PinMode pinMode){
    if(PINMASK(pinNumber) == 0 || pinNumber > MAX_PINNUM)
        return; // Not a valid GPIO pin

    // Put pin in GPIO mode
    PSEL0REG(pinNumber) &=~ PINMASK(pinNumber);
    PSEL1REG(pinNumber) &= ~PINMASK(pinNumber);

    switch(pinMode){
    case OUTPUT:
        // Configure as output default low
        PDIRREG(pinNumber) |= PINMASK(pinNumber);
        POUTREG(pinNumber) &= ~PINMASK(pinNumber);
        break;
    case INPUT:
        // Configure as input with no pull resistor
        PDIRREG(pinNumber) &= ~PINMASK(pinNumber);
        PRENREG(pinNumber) &= ~PINMASK(pinNumber);
        break;
    case INPUT_PULLUP:
        // Configure as input with pullup resistor
        PDIRREG(pinNumber) &= ~PINMASK(pinNumber);
        PRENREG(pinNumber) |= PINMASK(pinNumber);
        POUTREG(pinNumber) |= PINMASK(pinNumber);
        break;
    case INPUT_PULLDOWN:
        // Configure as input with pulldown resistor
        PDIRREG(pinNumber) &= ~PINMASK(pinNumber);
        PRENREG(pinNumber) |= PINMASK(pinNumber);
        POUTREG(pinNumber) |= PINMASK(pinNumber);
        break;
    default:
        // Do nothing
        break;
    }
}

void digitalWrite(pin_size_t pinNumber, PinStatus status){
    if(PINMASK(pinNumber) == 0 || pinNumber > MAX_PINNUM)
        return; // Not a valid GPIO pin
    
    switch(status){
    case HIGH:
        POUTREG(pinNumber) |= PINMASK(pinNumber);
        break;
    case LOW:
        POUTREG(pinNumber) &= ~PINMASK(pinNumber);
        break;
    default:
        // Do nothing
        break;
    }
}

PinStatus digitalRead(pin_size_t pinNumber){
    if(PINMASK(pinNumber) == 0 || pinNumber > MAX_PINNUM)
        return LOW; // Not a valid GPIO pin

    if(PINREG(pinNumber) & PINMASK(pinNumber)){
        return HIGH;
    }else{
        return LOW;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

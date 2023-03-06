/**
 * @file wiring_digital.c
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
    if(PxIN(pinNumber) == 0 || pinNumber > MAX_PINNUM)
        return; // Not a valid GPIO pin

    // Put pin in GPIO mode
    PxSEL0(pinNumber) &= ~PxMASK(pinNumber);
    PxSEL1(pinNumber) &= ~PxMASK(pinNumber);

    switch(pinMode){
    case OUTPUT:
        // Configure as output default low
        PxDIR(pinNumber) |= PxMASK(pinNumber);
        PxOUT(pinNumber) &= ~PxMASK(pinNumber);
        break;
    case INPUT:
        // Configure as input with no pull resistor
        PxDIR(pinNumber) &= ~PxMASK(pinNumber);
        PxREN(pinNumber) &= ~PxMASK(pinNumber);
        break;
    case INPUT_PULLUP:
        // Configure as input with pullup resistor
        PxDIR(pinNumber) &= ~PxMASK(pinNumber);
        PxREN(pinNumber) |= PxMASK(pinNumber);
        PxOUT(pinNumber) |= PxMASK(pinNumber);
        break;
    case INPUT_PULLDOWN:
        // Configure as input with pulldown resistor
        PxDIR(pinNumber) &= ~PxMASK(pinNumber);
        PxREN(pinNumber) |= PxMASK(pinNumber);
        PxOUT(pinNumber) |= PxMASK(pinNumber);
        break;
    default:
        // Do nothing
        break;
    }
}

void digitalWrite(pin_size_t pinNumber, PinStatus status){
    if(PxMASK(pinNumber) == 0 || pinNumber > MAX_PINNUM)
        return; // Not a valid GPIO pin
    
    switch(status){
    case HIGH:
        PxOUT(pinNumber) |= PxMASK(pinNumber);
        break;
    case LOW:
        PxOUT(pinNumber) &= ~PxMASK(pinNumber);
        break;
    default:
        // Do nothing
        break;
    }
}

#ifdef __cplusplus
// Compatability function to allow "bool" or "int" to digitalWrite
void digitalWrite(pin_size_t pinNumber, int status){
    digitalWrite(pinNumber, status ? HIGH : LOW);
}
#endif

PinStatus digitalRead(pin_size_t pinNumber){
    if(PxMASK(pinNumber) == 0 || pinNumber > MAX_PINNUM)
        return LOW; // Not a valid GPIO pin

    if(PxIN(pinNumber) & PxMASK(pinNumber)){
        return HIGH;
    }else{
        return LOW;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

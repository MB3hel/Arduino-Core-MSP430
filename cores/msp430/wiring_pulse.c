/**
 * @file wiring_pulse.c
 * Derived from Energia MSP430 wiring_pulse.c
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


unsigned long pulseIn(pin_size_t pin, uint8_t state, unsigned long timeout){
    // Counts width in number of loop iterations
    unsigned long width = 0;
    
    // Count number of loop iterations
    unsigned long numLoops = 0;

    // Convert timeout in us to clock cycles
    unsigned long maxLoops = timeout * (F_CPU / 1000000L);

    // Mask to match for pulse
    uint8_t stateMask = state ? PINMASK(pin) : 0;

    // Wait for previous pulse to end
    while((PxIN(pin) & PINMASK(pin)) == stateMask){
        if(numLoops++ == maxLoops){
            return 0;
        }
    }

    // Wait for pulse to start
    while((PxIN(pin) & PINMASK(pin)) != stateMask){
        if(numLoops++ == maxLoops){
            return 0;
        }
    }

    // Wait for pulse to stop
    while((PxIN(pin) & PINMASK(pin)) == stateMask){
        if(numLoops++ == maxLoops){
            return 0;
        }
        width++;
    }

    // Convert to microseconds
    // Cycles = (width * 13 + 11)
    // Based on comments in energia code
    /*
      "The loop has been determined to be 13 clock cycles long and have about 11 
       clocks between the edge and the start of the loop. There will be some error
       introduced by the interrupt handlers."
    */
   return (width * 13 + 11) / (F_CPU / 1000000L);
}

// Designed to be better for long pulses and more tolerant of interrupts
// by using micros()
unsigned long pulseInLong(pin_size_t pin, uint8_t state, unsigned long timeout){
    uint8_t stateMask = state ? PINMASK(pin) : 0;
    unsigned long start = micros(); // Start of function not pulse. Used for timeout

    // Wait for previous pulse to end
    while((PxIN(pin) & PINMASK(pin)) == stateMask){
        if(micros() - start > timeout){
            return 0;
        }
    }

    // Wait for the pulse to start
    while((PxIN(pin) & PINMASK(pin)) != stateMask){
        if(micros() - start > timeout){
            return 0;
        }
    }
    unsigned long pulseStart = micros();

    // Wait for pulse to stop
    while((PxIN(pin) & PINMASK(pin)) == stateMask){
        if(micros() - start > timeout){
            return 0;
        }
    }

    return micros() - pulseStart;
}

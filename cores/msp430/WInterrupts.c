/**
 * @file WInterrupts.c
 * Derived from Energia MSP430 WInterrupts.c
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

#if defined(PORT11_VECTOR)
#define NUM_INT_PORTS 11
#elif defined(PORT10_VECTOR)
#define NUM_INT_PORTS 10
#elif defined(PORT9_VECTOR)
#define NUM_INT_PORTS 9
#elif defined(PORT8_VECTOR)
#define NUM_INT_PORTS 8
#elif defined(PORT7_VECTOR)
#define NUM_INT_PORTS 7
#elif defined(PORT6_VECTOR)
#define NUM_INT_PORTS 6
#elif defined(PORT5_VECTOR)
#define NUM_INT_PORTS 5
#elif defined(PORT4_VECTOR)
#define NUM_INT_PORTS 4
#elif defined(PORT3_VECTOR)
#define NUM_INT_PORTS 3
#elif defined(PORT2_VECTOR)
#define NUM_INT_PORTS 2
#elif defined(PORT1_VECTOR)
#define NUM_INT_PORTS 1
#else
#define NUM_INT_PORTS 0
#endif

#if NUM_INT_PORTS > 0

// isr_func[port][pin] = func
static volatile voidFuncPtr isr_func[NUM_INT_PORTS][8];

// ies_toggle[port] = mask
static volatile uint8_t isr_toggle[NUM_INT_PORTS];


void attachInterrupt(pin_size_t interruptNumber, voidFuncPtr callback, PinStatus mode){
    // Interrupt numbers are equal to pin numbers since all pins support interrupts on MSP430
    if(PxIN(interruptNumber) == 0 || interruptNumber > MAX_PINNUM)
        return; // Not a valid pin

    uint16_t state = __get_interrupt_state();
    __disable_interrupt();

    if(mode == CHANGE){
        // MSP430 doesn't support a "change" mode so we need to toggle IES bit on each interrupt
        // This is done by toggling all bits set in the ies_toggle mask for the port

        // TODO
    }

    switch(mode){
    case RISING:
        PxIES(interruptNumber) &= ~PxMASK(interruptNumber);
        break;
    case FALLING:
        PxIES(interruptNumber) |= PxMASK(interruptNumber);
        break;
    }

    __set_interrupt_state(state);
}

void attachInterruptParam(pin_size_t interruptNumber, voidFuncPtrParam callback, PinStatus mode, void* param) __attribute__ ((error("attachInterruptParam is not supported.")));;


void detachInterrupt(pin_size_t interruptNumber){
    
}


#endif // NUM_INT_PORTS > 0
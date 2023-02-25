# Rewrite Plan

*Note: Loose plan.*

## Core

- Implement the core (largely based on the old core) using the [Arduino Core API](https://github.com/arduino/ArduinoCore-API)
- Ideally, DriverLib will not be used
    - I may backtrack on this. It may provide useful abstractions between devices.
- Serial Communications
    - USCI_A will support UART mode
    - USCI_B will support SPI and I2C mode
    - USCI_As will be used as HardwareSerial objects
    - If there are two USCI_B modules
        - Default `Wire` and `SPI` would be different USCI_Bs
        - Each USCI_B has a SPI and Wire object
    - If there is only one USCI_B module
        - `Wire` will be software I2C supporting master mode only
        - `SPI` will be USCI_B module
        - Maybe (stretch goal): way to switch USCI_B module to I2C mode with an alternate `Wire` object. Note quite sure how I'd want this API to work. Few ideas: 
            - `Wire1` object shared with `SPI`, but this feels not explicit enough and strange since boards with 2 modules wouldn't have SPI and Wire for each USCI_B
            - `WireSPI` object (explicit naming), but still a little odd since boards with multiple don't have this
            - Preprocessor flag that causes `Wire` to instead be the hardware (option in IDE tools menu).
            - Function on `Wire` instance to change to hardware (this function would do nothing on boards with two USCI_Bs). Similar idea to energia's `setModule` function
            - Alternatively, this could just not be supported. This is the easy option.
    - Same ideas apply for eUSCI modules (but slightly different implementation)
- Clock configuration
    - Support multiple CPU frequencies (through tool menu in IDE). Options depend on board.
    - SMCLK will match MCLK
    - ACLK will be external oscillator with VLO as fallback
- Analog Inputs
    - TODO: Supported references
    - All boards default to same resolution (10-bit?)
- Digital Inputs
    - Support interrupts on all pins


## Libraries

The following common arduino libraries will be ported to this core

- SPI (implementation of HardwareSPI class from core API)
- SoftwareSerial (port of existing library if needed; may just work as is)
- Wire (implementation of HardwareI2C class from core API)


The following libraries from Energia will still be included

- Servo
- Maybe USBSerial
- MspFlash


The following were included in Energia, but probalby don't need to be (can just use versions in library manager now)

- LiquidCrystal
- Stepper
- IRRemote
- WiFi

The following will not be included (possibly moved as zips to a separate location)

- AIR430BoostEuropeETSI
- AIR430BoostUSAFCC
- DriverLib
- EduBPMKII_Screen
- Kentec_35_SPI
- LCD_Launchpad
- PubNub
- aJson


## Boards

- Ideally, all launchpads supported by energia core will work with this core
- However, I don't have all these boards, so...
- Some older ones (ez430 based boards) may be dropped (or maybe not; depends on how much of my time they take)
- Starting with the launchpads I have
    - FR2355
    - FR5969
    - FR2433
    - G2553 (G2ET launchpad)
- Porting the others after (port = make sure they compile)


## Core Implementation TODO List (kindof in order)

- Chip initialization and clock configuration (focus on chips I have first then port for other chips based on energia code)
    - Note that most launchpads have an (LF)XT1 32786Hz crystal, however on some they are not connected by default. On such launchpads, the external crystal is disabled by default, however it can be enabled in the Tools menu of the IDE.
    - All boards default to a clock speed of 16MHz. Higher values (if supported) and lower values are available in a tools menu.
- Delay and timing support (millis, delay, micros, delayMicros)
    - WDT is used as an interval timer
    - delayMicroseconds fixed for various frequencies
    - More clock frequencies supported for delayMicroseconds

<br />

- Digital input and output (with pullup and puldown resistors)
- Digital pin interrupts (all pins / ports)
- Implement shift and pulse stuff

<br />

- Analog inputs with "normal" reference in 10-bit mode
- Analog input support for other resolutions
- Analog input support for other references

<br />

- HardwareSerial implemented with USCI_A or eUSCI_A
 
<br />

- HardwareSPI and Hardware_I2C implementation with USCI_B

<br />

- Add / port other libraries

# Rewrite Plan

*Note: Loose plan.*

## Core

- Implement the core (largely based on the old core) using the [Arduino Core API](https://github.com/arduino/ArduinoCore-API)
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
    - Some devices have "USI" modules??? Need to look into this more.
- Clock configuration
    - Support multiple CPU frequencies (through tool menu in IDE). Options depend on board.
    - SMCLK will match MCLK
    - ACLK will be external oscillator with VLO/REFO as fallback
- Analog Inputs
    - Support all internal references, VCC, and external (all use GND as ref-)
    - Support multiple resolutions on FR2xx_FR4xx family
- Digital Inputs
    - Support interrupts on all pins


## Libraries

The following common arduino libraries will be ported to this core

- SPI (implementation of HardwareSPI class from core API)
- SoftwareSerial (port of existing library if needed; may just work as is)
- Wire (implementation of HardwareI2C class from core API)


The following libraries from Energia will still be included

- Servo
- Maybe USBSerial (possibly replace with TinyUSB implementation)


The following were included in Energia, but probably don't need to be (can just use versions in library manager now)

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
- MspFlash


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

- [x] Chip initialization and clock configuration (focus on chips I have first then port for other chips based on energia code)
- [x] Delay and timing support (millis, delay, micros, delayMicros)
    

<br />

- [x] Digital input and output (with pullup and puldown resistors)
- [ ] Digital pin interrupts (all pins / ports)
- [ ] Implement shift and pulse stuff

<br />

- [ ] Analog inputs (analogRead and analogReference)
    - [ ] Resolution selection for FR2xx_FR4xx family
- [ ] Analog input support for other references
- [ ] PWM (analogWrite) using timers

<br />

- [ ] HardwareSerial implemented with USCI_A
- [ ] HardwareSPI using USCI_B (SPI library)
- [ ] Hardware_I2C implementation with USCI_B (Wire library)
- [ ] Software_I2C implementation (master mode) for devices without two USCI_B modules (Wire library)

<br />

- [ ] Add / port other libraries
    - [ ] Servo

## Implementation notes

- Note that most launchpads have an (LF)XT1 32786Hz crystal, however on some they are not connected by default. On such launchpads, the external crystal is disabled by default, however it can be enabled in the Tools menu of the IDE.
- All boards default to a clock speed of 16MHz. Higher values (if supported) and lower values are available in a tools menu.
    - Note that it may be better to default FRAM devices to 8MHz to avoid needing FRAM wait states by default.

- WDT is used as an interval timer
- delayMicroseconds fixed for various frequencies
- More clock frequencies supported for delayMicroseconds than originally in energia core

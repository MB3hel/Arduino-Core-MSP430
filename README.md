# Arduino Core MSP430

A fork of the now unmaintained [Energia MSP430 Core](https://github.com/energia/msp430-lg-core).

This repo provides package index files that can be used in the [Arduino IDE](https://www.arduino.cc/en/software).


Newer versions of the msp430-gcc compiler are supported than what were provided in the last official Energia release (`1.0.7` for MSP430 boards).

I do intend to fix bugs if I find them (PRs are also welcome if anyone else finds a bug).

If bugs are reported on the issue tracker, I do also intend to investigate (though I have a limited number of launchpads).


*This is a fork of the MSP430 core. There is no support for MSP432 boards or other boards that Eneriga supported.*


## Installing

- [Arduino IDE](https://www.arduino.cc/en/software)
- Open preferences / settings
    - On Windows or Linux `File > Preferences`
    - On macOS `Arduino IDE > Settings`
- Add the following in the "Additional boards manager URLs" section

```
https://raw.githubusercontent.com/MB3hel/Arduino-Core-MSP430/main/package_mb3hel-msp430_index.json
```

- Open the boards manager (`Tools > Boards > Boards Manager`) and search for "MSP430" and install the package.


## Pinout Diagrams

Some boards have diagrams in `extras/pinmaps`. Others may not. There is typically a comment in the `pins_energia.h` file for each variant with an ASCII pinout diagram.


## Supported Host Systems

- Linux x86_64 (64-bit)
- Windows x86_64 (64-bit)
- Windows i686 (32-bit)
- macOS x86_64 (Intel processors)

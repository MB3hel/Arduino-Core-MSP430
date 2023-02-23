# Arduino Core MSP430

A fork of the now unmaintained [Energia MSP430 Core](https://github.com/energia/msp430-lg-core).



## Installing

Tools for this boards package are provided for the following systems

- Linux x86_64 (64-bit)
- Windows x86_64 (64-bit)
- Windows i686 (32-bit)
- macOS x86_64 (Intel processors)

Installing the boards package:

- Install the [Arduino IDE](https://www.arduino.cc/en/software)
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


## Purpose & Scope of this Fork

Energia is officially unmaintained as of November 2022 and the last Release was in December 2019.

The last Energia release uses significantly older tools (compiler, uploader, etc) and though some work was done to update Energia to newer tools, the only such releases were beta and not widely tested / easily available (and will not be worked on further).

The main purpose of this repo is to package the MSP430 core with newer tools and to fix bugs that are found. I do intend to fix any bugs I find (PRs are also welcome if anyone else finds a bug). I also plan to investigate any reported issues (though I only have a limited number of launchpad boards).

Note that this is a fork of the Energia **MSP430** core. Other boards (MSP432, etc) are not supported by this core.

## Major Changes

Completed Changes:

- Packaged newer MSP430-GCC
    - Fixed bugs with compiling for various boards using newer gcc
    - Enabled link time optimizations
- Replaced use of floating point capable printf calls in core and libraries
- Switched to using `mspdebug` instead of the TI proprietary `DSLite` to upload programs
    - This tool is easier to package and is open source
    - Additionally, since CCSv8 support for some architectures (such as 32-bit windows) are not supported

Planned changes:

- Support for [UniFlash](https://www.ti.com/tool/UNIFLASH) CLI as an alternate upload tool
- More options exposed via menus in the Arduino IDE (similar to what other cores do)
    - Upload tool (if UniFlash support is implemented)
    - Debug info
    - Warnings
    - Optimization Level
    - CPU Frequency
- Map file generation
- Pinmaps diagrams for additional boards (specifically MSP-EXP430FR2355LP)

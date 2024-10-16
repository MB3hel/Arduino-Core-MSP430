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
 


## Usage & Documentation

### Port Selection & Uploading

Most launchpad boards&ast; use an ez-FET debugger (onboard). This will show up as two serial ports. One serial port is used to communicate with the debugger itself (this is the "upload" port). The second port is used to communicate with the target chip, where your program is actually running (this is the "target" port).

When uploading a sketch, you will need to select the upload port in the `Tools > Ports` menu. To communicate with the device using `Serial` and the Serial Monitor, you will need to select the target port. Note that if you attempt to upload with the target selected the upload will fail. However, opening the serial monitor with the upload port selected, will result in no data being received from the board.

*Note that the information below is provided in case you want to figure out how to identify ports, however in practice there are usually only two. Just try uploading to both to figure out which works. This is the upload port. The other is the target port.*

*If more than one launchpad is in use, it is advised to connect one then the other to determine which sets of ports are associated with each.*


<details><summary>Identifying Ports on Windows</summary>
<hr />
<p>

Open device manager and go to the "Ports (COM and LPT)" section and expand it.

The upload port is listed as `MSP Debug Interface (COMx)` where `x` is the number.

The target port is listed as `MSP Application UART1 (COMx)` where `x` is the number.

Note that there is not really an easy way to determine which sets of ports are on the same launchpad. It is possible by going to `Properties > Details`. Compare the "Siblings" property to other port's "Device Instance Path" property. Siblings of a device are the same physical launchpad.

</p>
<hr />
</details>

<details><summary>Identifying Ports on macOS</summary>
<hr />
<p>

On macOS, the ez-FET will show up as `/dev/cu.usbmodem[num]` devices where `[num]` is the port number. The upload port is enumerated first, so generally has a lower number than the target port. 

*Note: I'm not 100% certain the following information is always correct, but it seems to be on my system.*

To identify actual port numbers run the following command

```sh
ioreg -p IOUSB
```

Look for "MSP Tools Driver" entries and note the number after the `@` symbol (eg `MSP Tools Driver@14200000`). Note the first four digits of this number (in this example `1420`). This number is referred to as `id`.

The upload port will be `/dev/cu.usbmodem[id]1` and the target port will be `/dev/cu.usbmodem[id]3`.

If you want the serial number of the board for a certain id, run the following and look for the "USB Serial Number" entry under the device entry

```
ioreg -p IOUSB -l -b
```

</p>
<hr />
</details>



<details><summary>Identifying Ports on Linux</summary>
<hr />
<p>

On Linux, the ez-FET will show up as `/dev/ttyACMx` devices where `x` is the port number. The upload port is enumerated first, so generally has a lower number than the target port. To identify actual port numbers run the following in a terminal

```sh
$ ls /dev/serial/by-id
```

You will see output like the following where SERIAL is replaced by your board's serial number.

```
usb-Texas_Instruments_MSP_Tools_Driver_SERIAL-if00
usb-Texas_Instruments_MSP_Tools_Driver_SERIAL-if02
```

The one ending in `if00` is the upload port and `if02` the target port. Use the following command to identify which `/dev/ttyACM` ports they correspond to (the port numbers will be printed).

```sh
$ realpath usb-Texas_Instruments_MSP_Tools_Driver_SERIAL-if00
/dev/ttyACM0

$ realpath usb-Texas_Instruments_MSP_Tools_Driver_SERIAL-if02
/dev/ttyACM1
```

</p>
<hr />
</details>


&ast;*I don't have any older launchpads with the ez430 debuggers, but it seems that the same general information applies. One upload port and one target port.*


### UniFlash Uploader

As an alternative to the included `mspdebug` TI's [UniFlash](https://www.ti.com/tool/UNIFLASH) can be used to upload a program to the board. *UniFlash must be installed on your computer manually.* It will not be automatically installed by the Arduino IDE when using this core.

UniFlash is invoked using a wrapper that searches for the newest version installed on your computer. Note that you can put the UniFlash directory in the PATH (so that `dslite.sh` or `dslite.bat` is in the path) to override what version is used.

Note that when using UniFlash, it will always attempt to upload the the first device that was connected to your computer. Thus, **the Port setting has no effect on uploading**. You must still select the target port to use the Serial Monitor though.

To use UniFlash as an uploader, select "UniFlash" under `Tools > Upload Tool`. Note that this is not supported for older launchpads using the ez430 debugger.

### Libraries

For specific library documentation, refer to the "Core Libraries" section of [Energia's docs](https://energia.nu/guide/libraries/).

These libraries are generally compatible with the [Arduino Libraries](https://www.arduino.cc/reference/en/libraries/) by the same names.

### Pinout Diagrams

Some boards have diagrams in `extras/pinmaps`. Others may not. There is typically a comment in the `pins_energia.h` file for each variant with an ASCII pinout diagram.



## Purpose & Scope of this Fork

Energia is officially unmaintained as of November 2022 and the last Release was in December 2019.

The last Energia release uses significantly older tools (compiler, uploader, etc) and though some work was done to update Energia to newer tools, the only such releases were beta and not widely tested / easily available (and will not be worked on further).

The main purpose of this repo is to package the MSP430 core with newer tools and to fix bugs that are found. I do intend to fix any bugs I find (PRs are also welcome if anyone else finds a bug). I may also be able to help investigate any reported issues (though I only have a limited number of launchpad boards).

Note that this is a fork of the Energia **MSP430** core. Other boards (MSP432, etc) are not supported by this core.

### Changes

**Completed Changes:**  
- Packaged newer MSP430-GCC
    - Fixed bugs with compiling for various boards using newer gcc
    - Enabled link time optimizations
- Replaced use of floating point capable printf calls in core and libraries
- Switched to using `mspdebug` instead of the TI proprietary `DSLite` to upload programs
    - This tool is easier to package and is open source
    - Additionally, since CCSv8 there is no support for some architectures (such as 32-bit windows)
- Support using UniFlash (DSLite internally) as an alternate uploader
- Added support for various Arduino IDE settings
    - Verbose upload setting
    - Verify after upload setting
    - Warning level setting
    - Support `Tools > Port` menu selection

**Planned changes:**  
- `mspdebug` with readline on non-linux platforms
- More options exposed via menus in the Arduino IDE (similar to what other cores do)
    - Debug info
    - Optimization Level
    - CPU Frequency
- Map file generation
- Pinmaps diagrams for additional boards (specifically MSP-EXP430FR2355LP)
- Maybe eventually debug support in Arduino IDE 2.0
- Maybe eventually adapt / cleanup the core using [ArduinoCore-API](https://github.com/arduino/ArduinoCore-API)

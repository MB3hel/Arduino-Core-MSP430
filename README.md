# Arduino Core MSP430


My fork of Energia core for MSP430 with compiler updates and maybe some bug fixes as needed.


## Use

- Install the Arduino IDE
- Add the following as a boards manager URL in preferences (`File > Preferences` on Windows or Linux, `Arduino IDE > Settings` on macOS)

```
https://raw.githubusercontent.com/MB3hel/Arduino-Core-MSP430/main/arduino_core_msp430.json
```

- Install the MSP430 boards package from the board manager


*Note: Currently support is provided for 64-bit Windows, macOS, and Linux systems (x86-64).*




## Building


### Core Package

Run `./package.sh`


### Compiler (MPS430-GCC-OPENSOURCE) Tool Package

Install the compiler on the same OS (can't extract installer, must install then make archive from installed folder).

```
cd /path/to/msp430-gcc/..
tar --exclude="msp430-gcc/uninstall*" --exclude=msp430-gcc/install_logs --exclude=msp430-gcc/examples --exclude=msp430-gcc/common --exclude=msp430-gcc/reidist --exclude=msp430-gcc/emulation --exclude=msp430-gcc/docs --exclude=msp430-gcc/install_scripts --exclude=msp430-gcc/include/gdb --create --bzip2 -f ~/tool.tar.bz2 msp430-gcc/
```

On windows, use 7zip to make the archive. Manually exclude the folders listed as excludes above.


### Debug Server (UniFlash) Tool Package

Note: Version numbers match UniFlash version, not DSLite or mspdebug version.

Install UniFlash on the same OS (can't extract installer, must install then make archive from installed folder).

```
cd /path/to/uniflash/deskdb/content/TICloudAgent
cd linux   # Change to match host os
cp -r ccs_base/ DebugServer/
cp ../../../../docs/licenses/license.txt DebugServer
tar --create --bzip2 -f ~/tool.tar.bz2 DebugServer
rm -r DebugServer/
```

On windows, use 7zip to make the archive. Manually exclude the folders listed as excludes above.

### Updating index file

Add entries in same form. Need hashsum (use `sha256sum`) and size in bytes (`wc -c`).


## References

[Platform Spec](https://arduino.github.io/arduino-cli/0.31/platform-specification/)

[Package Index Spec](https://arduino.github.io/arduino-cli/0.31/package_index_json-specification/)

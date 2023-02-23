# Development Information



## MSP430 Arduino Core Package

Run `extras/package.sh` and enter the version number. The tarball will be created in the `build` directory. This script is intended to be run on a Linux system. It may work on macOS or on MSYS2 on windows, but those are not tested.

Note that while developing the core, clone to `SKETCHBOOK/hardware/arduino-core-msp430/msp430` and restart the Arduino IDE after making changes for them to take effect.


Also, be aware of [this bug](https://github.com/arduino/arduino-ide/issues/1030) where the IDE won't pickup changes to files that it should. Make sure to delete the folder indicated if editing installed files.


## MSP430-GCC Tool Package

Install the compiler on the same OS (can't extract installer, must install then make archive from installed folder). This unfortunately means a computer of each OS and architecture combination is required to package the debug server.

```
cd /path/to/msp430-gcc/..
tar --exclude="msp430-gcc/uninstall*" --exclude=msp430-gcc/install_logs --exclude=msp430-gcc/examples --exclude=msp430-gcc/common --exclude=msp430-gcc/reidist --exclude=msp430-gcc/emulation --exclude=msp430-gcc/docs --exclude=msp430-gcc/install_scripts --exclude=msp430-gcc/include/gdb --create --bzip2 -f ~/tool.tar.bz2 msp430-gcc/
```

On windows, use 7zip to make the archive. Manually exclude the folders listed as excludes above. This is best done by duplicating the msp430-gcc directory and deleting the excluded files (since the archive needs to have a top level directory named `msp430-gcc`)



## mspdebug Tool Package

- Build [mspdebug](https://github.com/dlbeer/mspdebug). Note that libusb and libreadline are required. Use msys2 on windows. Use brew on macos. Copy the resulting binary to an empty directory name `mspdebug`. 
    - On windows, build without readline (make WITHOUT_READLINE=1)
    - If using msys2, libusb 0.1 is libusb-win32 and change -lusb to -lusb0 in the makefile
    - For macos, use libusb and libusb-compat and WITHOUT_READLINE=1. Will also need hidapi from brew. Make sure pkg-config is installed first.
- Download [TI's MSP Debug Stack](https://www.ti.com/tool/MSPDS) DLLs (not source code) and grab the dll (windows), so (linux), or dynlib (macos) required. Could build from source too, but that is more involved (follow instructions in the source package's readme if attempting).
- Place the libmsp430 dynamic library in the same directory as the built mspdebug tool. Remove the "_64" suffix if one exists. Note for windows it is not libmsp430, but MSP430.dll. Note that on macos, the library may need to be given `.so` suffix instead of `dylib` for mspdebug to find it.
- Use `ldd` (linux) or `otool -L` (macos), or [Dependencies](https://github.com/lucasg/Dependencies) (windows) to determine what dynamic libraries also need to be copied. Libraries every system will have can be skipped.
- If linux or macos, rename `mspdebug` to `mspdebug.bin`
- Add the wrapper script named `mspdebug` to launch `mspdebug.bin` and make it executable (linux and macos only)
- Run `./mspdebug tilib` and make sure it works (no errors about libmsp430).
- tar bz2 the directory (`tar --create --bzip2 -f mspdebug.tar.bz2 mspdebug`). It is important that the top level directory of the tar be named mspdebug.

Linux script

```sh
#!/usr/bin/env bash
DIR=$(dirname "$0")
LD_LIBRARY_PATH="$DIR":$LD_LIBRARY_PATH "$DIR"/mspdebug.bin "$@"
```

macOS script:

```sh
#!/usr/bin/env bash
DIR=$(dirname "$0")
DYLD_LIBRARY_PATH="$DIR":$DYLD_LIBRARY_PATH "$DIR"/mspdebug.bin "$@"
```


## Index File

The index file is manually updated. Copy / paste an existing entry of the same type and add new URL, hashsum (`sha256sum filename` command), and size in bytes (`wc -c filename` command). 



## Useful References

[Arduino Platform Spec](https://arduino.github.io/arduino-cli/0.31/platform-specification/)

[Arduino Package Index Spec](https://arduino.github.io/arduino-cli/0.31/package_index_json-specification/)

[MSP430 GCC User Guide](https://www.ti.com/lit/ug/slau646f/slau646f.pdf)

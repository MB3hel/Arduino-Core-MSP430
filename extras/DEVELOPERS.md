# Development Information



## MSP430 Arduino Core Package

Run `extras/package.sh` and enter the version number. The tarball will be created in the `build` directory. This script is intended to be run on a Linux system. It may work on macOS or on MSYS2 on windows, but those are not tested.

Note that while developing the core, clone to `SKETCHBOOK/hardware/mb3hel-msp430/msp430` and restart the Arduino IDE after making changes for them to take effect.

Tool packages should be able to be manually installed to `SKETCHBOOK/hardware/mb3hel-msp430/TOOL_NAME`.

Also, be aware of [this bug](https://github.com/arduino/arduino-ide/issues/1030) where the IDE won't pickup changes to files that it should. Make sure to delete the folder indicated if editing installed files.



## MSP430-GCC Tool Package

[Download](https://www.ti.com/tool/MSP430-GCC-OPENSOURCE) the "toolchain only" archives for each platform. Also download the support files. Extract each archive and merge the support file `include/` with the toolchain `include`. Then recompress the file. This should be done on a Linux / unix filesystem so that extracted macos and linux tarballs retain file permissions.



## mspdebug Tool Package

### Windows

Install [MSYS2](https://www.msys2.org/). Run in `mingw32` or `mingw64` for `i686` and `amd64` builds respectively.

```sh
# TODO
```

### macOS

- Install [homebrew](https://brew.sh/)
- Run the following commands
    ```sh
    cd mspdebug-version
    brew install libusb libusb-compat hidapi
    make WITHOUT_READLINE=1
    mv mspdebug mspdebug.bin
    mkdir mspdebug
    cp mspdebug.bin mspdebug/
    cd mspdebug/
    ```
- Then run `otool -L mspdebug.bin`. Copy each non-builtin library (probably all in `/usr/local`) to the same directory as `mspdebug.bin`.
- Then, run `otool -L` on each of the copied libraries and copy anything they depend on. Repeat this until all libraries are collected in the current directory.
- Then, create a launch wrapper called `mspdebug`. Make it executable by running `chmod a+x mspdebug`
    ```sh
    #!/usr/bin/env bash
    DIR=$(dirname "$0")
    DYLD_LIBRARY_PATH="$DIR":$DYLD_LIBRARY_PATH "$DIR"/mspdebug.bin "$@"
    ```
- Compress the archive (note that the root directory of the archive must be `msp430gcc`)
    ```sh
    cd ..
    tar --create --bzip2 -f mspdebug-VERSION-mac-ARCH.tar.bz2 mspdebug/
    ```



### Linux

- Note that it is best to build an a system with an older GLIBC (build on an older distro). This is often easily done using a debian / ubuntu chroot
- Run the following commands
    ```sh
    cd mspdebug-version
    sudo apt install libreadline-dev libusb-dev
    make
    mv mspdebug mspdebug.bin
    mkdir mspdebug
    cp mspdebug.bin mspdebug/
    cd mspdebug/
    ```
- Then run `ldd mspdebug.bin`. Copy each non-builtin library to the same directory as `mspdebug.bin`. There is no need to copy libc, libdl, or libpthread.
- Then, create a launch wrapper called `mspdebug`. Make it executable by running `chmod a+x mspdebug`
    ```sh
    #!/usr/bin/env bash
    DIR=$(dirname "$0")
    LD_LIBRARY_PATH="$DIR":$LD_LIBRARY_PATH "$DIR"/mspdebug.bin "$@"
    ```
- Compress the archive (note that the root directory of the archive must be `msp430gcc`)
    ```sh
    cd ..
    tar --create --bzip2 -f mspdebug-VERSION-linux-ARCH.tar.bz2 mspdebug/
    ```



### Old

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



## Index File

The index file is manually updated. Copy / paste an existing entry of the same type and add new URL, hashsum (`sha256sum filename` command), and size in bytes (`wc -c filename` command). 



## Useful References

[Arduino Platform Spec](https://arduino.github.io/arduino-cli/0.31/platform-specification/)

[Arduino Package Index Spec](https://arduino.github.io/arduino-cli/0.31/package_index_json-specification/)

[MSP430 GCC User Guide](https://www.ti.com/lit/ug/slau646f/slau646f.pdf)

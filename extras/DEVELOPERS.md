# Development Information



## MSP430 Arduino Core Package

Run `extras/package.sh` and enter the version number. The tarball will be created in the `build` directory. This script is intended to be run on a Linux system. It may work on macOS or on MSYS2 on windows, but those are not tested.

Note that while developing the core, clone to `SKETCHBOOK/hardware/mb3hel-msp430/msp430` and restart the Arduino IDE after making changes for them to take effect.

Also, be aware of [this bug](https://github.com/arduino/arduino-ide/issues/1030) where the IDE won't pickup changes to files that it should. Make sure to delete the folder indicated if editing installed files.



## MSP430-GCC Tool Package

[Download](https://www.ti.com/tool/MSP430-GCC-OPENSOURCE) the "toolchain only" archives for each platform. Also download the support files. Extract each archive and merge the support file `include/` with the toolchain `include`. Then recompress the file. This should be done on a Linux / unix filesystem so that extracted macos and linux tarballs retain file permissions.



## mspdebug Tool Package

For all platforms, download [TI's MSP Debug Stack](https://www.ti.com/tool/MSPDS) DLLs (not source code). For platforms without a prebuilt library, the source code can be downloaded and built according the the instructions provided in the archive.

### Windows

- Install [MSYS2](https://www.msys2.org/).
- Run in `mingw32` or `mingw64` environments (i686 or amd64 builds respectively)
    ```sh
    # For mingw32
    pacman -S mingw-w64-i686-libusb-win32 mingw-w64-i686-readline

    # For mingw64
    pacman -S mingw-w64-x86_64-libusb-win32 mingw-w64-x86_64-readline

    # For both
    cd mspdebug-version
    sed -i 's/-lusb/-lusb0/g' Makefile
    make
    mkdir mspdebug
    cp mspdebug.exe mspdebug/
    cd mspdebug/
    ```
- Run [Dependencies](https://github.com/lucasg/Dependencies) and open `mspdebug.exe`
- Check through the list of dependency dlls and copy them from `/mingw32/bin` or `/mingw64/bin` to the same folder as `mspdebug.exe`. Make sure to expand the tree and copy dependencies of the dependencies themselves too. There is no need to copy builtin windows dlls (in `C:\Windows\System32`).
    - Note that `/mingw32` or `/mingw64` are relative to where msys2 is installed.
- Next, copy the `MSP430.dll` file from TI's MSPDS (use the 64-bit version for 64 bit builds, but remove `_64`). For some versions of `mspdebug` you may need to rename it to end with `.so` instead. 
- Test the setup by running `.\mspdebug.exe tilib`. Make sure there are not errors loading `MSP430.dll`.
- Compress the `mspdebug` directory using 7zip (archive as tar, then compress that tar as bzip2).


### macOS

- Install [homebrew](https://brew.sh/)
- Run the following commands
    ```sh
    cd mspdebug-version
    brew install libusb libusb-compat hidapi readline
    sed -i.bak 's/READLINE_LIBS = \-lreadline/READLINE_LIBS = -lreadline -L\/usr\/local\/opt\/readline\/lib/g' Makefile
    sed -i.bak 's/READLINE_CFLAGS = -DUSE_READLINE/READLINE_CFLAGS = -DUSE_READLINE -I\/usr\/local\/opt\/readline\/include/g' Makefile
    make
    mv mspdebug mspdebug.bin
    mkdir mspdebug
    cp mspdebug.bin mspdebug/
    cd mspdebug/
    ```
- Then run `otool -L mspdebug.bin`. Copy each non-builtin library (probably all in `/usr/local`) to the same directory as `mspdebug.bin`.
- Then, run `otool -L` on each of the copied libraries and copy anything they depend on. Repeat this until all libraries are collected in the current directory.
- Next, copy the `libmsp430.dylib` file from TI's MSPDS. For some versions of `mspdebug` you may need to rename it to end with `.so` instead. 
- Then, create a launch wrapper called `mspdebug`. Make it executable by running `chmod a+x mspdebug`
    ```sh
    #!/usr/bin/env bash
    args=("$@")
    for i in "${!args[@]}"; do
        if [[ ${args[$i]} == /dev/cu.usbmodem* ]]; then
            args[$i]=${args[$i]#"/dev/cu."}
        fi
    done
    DIR=$(dirname "$0")
    DYLD_LIBRARY_PATH="$DIR":$DYLD_LIBRARY_PATH "$DIR"/mspdebug.bin "${args[@]}"
    ```
- Test the setup by running `./mspdebug tilib`. Make sure there are not errors loading `libmsp430`.
- Compress the archive (note that the root directory of the archive must be `mspdebug`)
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
- Then run `ldd mspdebug.bin`. Copy each non-builtin library to the same directory as `mspdebug.bin`. There is no need to copy `libc`, `libdl`, or `libpthread`.
- Next, copy the `libmsp430.so` file from TI's MSPDS. Make sure to remove the `_64` suffix.
- Then, create a launch wrapper called `mspdebug`. Make it executable by running `chmod a+x mspdebug`
    ```sh
    #!/usr/bin/env bash
    DIR=$(dirname "$0")
    LD_LIBRARY_PATH="$DIR":$LD_LIBRARY_PATH "$DIR"/mspdebug.bin "$@"
    ```
- Test the setup by running `./mspdebug tilib`. Make sure there are not errors loading `libmsp430`.
- Compress the archive (note that the root directory of the archive must be `mspdebug`)
    ```sh
    cd ..
    tar --create --bzip2 -f mspdebug-VERSION-linux-ARCH.tar.bz2 mspdebug/
    ```


## UniFlash Launcher Tool Package

```sh
cd extras
mkdir -p ../build
tar --create --bzip2 -f ../build/uniflash-launcher-VERSION.tar.bz2 uniflash-launcher
```


## Index File

The index file is manually updated. Copy / paste an existing entry of the same type and add new URL, hashsum (`sha256sum filename` command), and size in bytes (`wc -c filename` command). 



## Useful References

[Arduino Platform Spec](https://arduino.github.io/arduino-cli/0.31/platform-specification/)

[Arduino Package Index Spec](https://arduino.github.io/arduino-cli/0.31/package_index_json-specification/)

[MSP430 GCC User Guide](https://www.ti.com/lit/ug/slau646f/slau646f.pdf)

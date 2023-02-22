# Development Information



## MSP430 Arduino Core Package

Run `extras/package.sh` and enter the version number. The tarball will be created in the `build` directory. This script is intended to be run on a Linux system. It may work on macOS or on MSYS2 on windows, but those are not tested.

Note that while developing the core, the `dev-update.sh` script can be used to install it in the IDE (it is assumed that the toolchain and debug server tool packages are already installed). Note that you will need to manually delete `~/.arduino15/packages/arduino-core-msp430/hardware/msp430/999.999.999/` to be able to install official releases.



## MSP430-GCC Tool Package

Install the compiler on the same OS (can't extract installer, must install then make archive from installed folder). This unfortunately means a computer of each OS and architecture combination is required to package the debug server.

```
cd /path/to/msp430-gcc/..
tar --exclude="msp430-gcc/uninstall*" --exclude=msp430-gcc/install_logs --exclude=msp430-gcc/examples --exclude=msp430-gcc/common --exclude=msp430-gcc/reidist --exclude=msp430-gcc/emulation --exclude=msp430-gcc/docs --exclude=msp430-gcc/install_scripts --exclude=msp430-gcc/include/gdb --create --bzip2 -f ~/tool.tar.bz2 msp430-gcc/
```

On windows, use 7zip to make the archive. Manually exclude the folders listed as excludes above. This is best done by duplicating the msp430-gcc directory and deleting the excluded files (since the archive needs to have a top level directory named `msp430-gcc`)



## Debug Server Tool Package

Note: Version numbers match UniFlash version, not DSLite or mspdebug version.

Install UniFlash on the same OS (can't extract installer, must install then make archive from installed folder). This unfortunately means a computer of each OS and architecture combination is required to package the debug server.

```
cd /path/to/uniflash/deskdb/content/TICloudAgent
cd linux   # Change to match host os
cp -r ccs_base/ DebugServer/
cp ../../../../docs/licenses/license.txt DebugServer
tar --create --bzip2 -f ~/tool.tar.bz2 DebugServer
rm -r DebugServer/
```

On windows, use 7zip to make the archive. Manually copy / rename files and folders as directed above.



## Index File

The index file is manually updated. Copy / paste an existing entry of the same type and add new URL, hashsum (`sha256sum filename` command), and size in bytes (`wc -c filename` command). 



## Useful References

[Arduino Platform Spec](https://arduino.github.io/arduino-cli/0.31/platform-specification/)

[Arduino Package Index Spec](https://arduino.github.io/arduino-cli/0.31/package_index_json-specification/)

[MSP430 GCC User Guide](https://www.ti.com/lit/ug/slau646f/slau646f.pdf)

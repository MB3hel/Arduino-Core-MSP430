# Arduino Core MSP430


My WIP fork of Energia core for MSP430 with compiler updates and maybe some bug fixes as needed.


## Use

TODO




## Building


### Core Package

Run `./package.sh`


### Compiler (MPS430-GCC-OPENSOURCE) Tool Package

Install the compiler on the same OS (can't extract installer, must install then make archive from installed folder).

```
cd /path/to/msp430-gcc/..
tar --exclude="msp430-gcc/uninstall*" --exclude=msp430-gcc/install_logs --exclude=msp430-gcc/examples --exclude=msp430-gcc/common --exclude=msp430-gcc/reidist --exclude=msp430-gcc/emulation --exclude=msp430-gcc/docs --exclude=msp430-gcc/install_scripts --create --bzip2 -f ~/tool.tar.bz2 msp430-gcc/
```

On windows, use 7zip to make the archive. Manually exclude the folders listed as excludes above.


### Debug Server (UniFlash) Tool Package

Note: Version numbers match UniFlash version, not DSLite or mspdebug version.

Install UniFlash on the same OS (can't extract installer, must install then make archive from installed folder).

```
cd /path/to/uniflash/deskdb/content/TICloudAgent
cd linux   # Change to matchcd host os
cd ccs_base/
cp ../../../../../docs/licenses/license.txt DebugServer
tar --create --bzip2 -f ~/tool.tar.bz2 DebugServer
```

On windows, use 7zip to make the archive. Manually exclude the folders listed as excludes above.
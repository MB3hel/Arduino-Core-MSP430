#!/usr/bin/env bash

rm -rf ~/.arduino15/packages/arduino-core-msp430/hardware/msp430
mkdir -p ~/.arduino15/packages/arduino-core-msp430/hardware/msp430/999.999.999/
cp -r cores/ libraries/ variants/ boards.txt platform.txt programmers.txt ~/.arduino15/packages/arduino-core-msp430/hardware/msp430/999.999.999/
echo "Restart Arduino IDE for changes to take effect!"
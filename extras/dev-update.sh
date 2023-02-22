#!/usr/bin/env bash

DIR=$(realpath $(dirname "$0"))

rm -rf ~/.arduino15/packages/arduino-core-msp430/hardware/msp430
mkdir -p ~/.arduino15/packages/arduino-core-msp430/hardware/msp430/999.999.999/
pushd "$DIR/.." > /dev/null
cp -r cores/ libraries/ variants/ boards.txt platform.txt programmers.txt ~/.arduino15/packages/arduino-core-msp430/hardware/msp430/999.999.999/
popd > /dev/null
echo "Restart Arduino IDE for changes to take effect!"
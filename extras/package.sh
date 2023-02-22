#!/usr/bin/env bash


DIR=$(realpath $(dirname "$0"))
printf "Version: "
read version
sed -i "s/^version=.*\$/version=${version}/g" platform.txt
mkdir -p "$DIR/../build/"
rm -rf "$DIR/../build/arduino-core-msp430"
mkdir -p "$DIR/../build/arduino-core-msp430"
pushd "$DIR/.." > /dev/null
cp -r cores/ build/arduino-core-msp430
cp -r libraries build/arduino-core-msp430
cp -r variants build/arduino-core-msp430
cp boards.txt build/arduino-core-msp430
cp platform.txt build/arduino-core-msp430
cp programmers.txt build/arduino-core-msp430
pushd build/
tar --create --bzip2 -f "msp430-core-${version}.tar.bz2" arduino-core-msp430
rm -rf arduino-core-msp430
popd > /dev/null
popd > /dev/null

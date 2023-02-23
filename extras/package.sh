#!/usr/bin/env bash


DIR=$(realpath $(dirname "$0"))
printf "Version: "
read version
sed -i "s/^version=.*\$/version=${version}/g" platform.txt
mkdir -p "$DIR/../build/"
rm -rf "$DIR/../build/mb3hel-msp430"
mkdir -p "$DIR/../build/mb3hel-msp430"
pushd "$DIR/.." > /dev/null
cp -r cores/ build/mb3hel-msp430
cp -r libraries build/mb3hel-msp430
cp -r variants build/mb3hel-msp430
cp boards.txt build/mb3hel-msp430
cp platform.txt build/mb3hel-msp430
cp programmers.txt build/mb3hel-msp430
pushd build/
tar --create --bzip2 -f "msp430-core-${version}.tar.bz2" mb3hel-msp430
rm -rf mb3hel-msp430
popd > /dev/null
popd > /dev/null

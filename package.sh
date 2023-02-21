#!/usr/bin/env bash


DIR=$(realpath $(dirname "$0"))
printf "Version: "
read version
sed -i "s/^version=.*\$/version=${version}/g" platform.txt
mkdir -p "$DIR/build/"
pushd "$DIR"
shopt -s dotglob
tar --exclude=arduino_core_msp430.json --exclude=build --exclude=package.sh --exclude=.git* --create --bzip2 -f "$DIR/build/msp430-core-${version}.tar.bz2" *
popd

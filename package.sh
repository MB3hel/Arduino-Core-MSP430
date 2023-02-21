#!/usr/bin/env bash


DIR=$(realpath $(dirname "$0"))
mkdir -p "$DIR/build/"
pushd "$DIR"
shopt -s dotglob
tar --exclude=arduino_core_msp430.json --exclude=build --exclude=package.sh --exclude=.git* --create --bzip2 -f "$DIR/build/package.tar.bz2" *
popd

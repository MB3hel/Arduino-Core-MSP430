#!/usr/bin/env bash

UNAMEO="$(uname -o)"

if [ "$UNAMEO" = "GNU/Linux" ]; then
    rm -rf ~/.config/arduino-ide/
elif [ "$UNAMEO" = "Msys" ]; then
    rm -rf $APPDATA/arduino-ide/
elif [ "$UNAMEO" = "Darwin" ]; then 
    rm -rf ~/Library/Application Support/arduino-ide/
else
    echo "Unknown OS"
    exit 1
fi

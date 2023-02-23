#!/usr/bin/env sh
# Finds UniFlash installed in standard locations
# Linux: /opt/ti/uniflash_VERSION or ~/ti/uniflash_VERSION
# macOS: /Applications/ti/uniflash_VERSION
# Picks the version with the highest version number
# If dslite.sh is in the PATH, it will be used instead

UNAMEO="$(uname -o)"


if [ "$UNAMEO" = "Darwin" ]; then
    uniflash_ver=$(ls /Applications/ti 2> /dev/null | grep uniflash | grep -Eo '[0-9]+\.[0-9]+\.[0-9]+' | sort --version-sort --field-separator=. | tail -n 1)
    if command -v dslite.sh > /dev/null; then
        echo "[INFO]: dslite.sh found in path."
        dslite_script="$(command -v dslite.sh)"
        uniflash_dir=$(dirname "$dslite_script")
        uniflash_ver=$(echo "$uniflash_dir" | grep -Eo '[0-9]+\.[0-9]+\.[0-9]+')
    elif [ -d "/Applications/ti/uniflash_${uniflash_ver}" ]; then
        uniflash_dir="/opt/ti/uniflash_${uniflash_ver}/"
        dslite_script="$uniflash_dir/dslite.sh" 
    else
        echo "[ERROR]: Unable to find UniFlash." >&2
        exit 1
    fi
elif [ "$UNAMEO" = "GNU/Linux" ]; then
    uniflash_ver=$({ ls ~/ti 2> /dev/null & ls /opt/ti 2> /dev/null; } | grep uniflash | grep -Eo '[0-9]+\.[0-9]+\.[0-9]+' | sort --version-sort --field-separator=. | tail -n 1)
    if command -v dslite.sh > /dev/null; then
        echo "[INFO]: dslite.sh found in path."
        dslite_script="$(command -v dslite.sh)"
        uniflash_dir=$(dirname "$dslite_script")
        uniflash_ver=$(echo "$uniflash_dir" | grep -Eo '[0-9]+\.[0-9]+\.[0-9]+')
    elif [ -d "/opt/ti/uniflash_${uniflash_ver}" ]; then
        uniflash_dir="/opt/ti/uniflash_${uniflash_ver}/"
        dslite_script="$uniflash_dir/dslite.sh"
    elif [ -d "$HOME/ti/uniflash_${uniflash_ver}" ]; then
        uniflash_dir="$HOME/ti/uniflash_${uniflash_ver}/"
        dslite_script="$uniflash_dir/dslite.sh"        
    else
        echo "[ERROR]: Unable to find UniFlash." >&2
        exit 1
    fi
else
    echo "[ERROR]: Unknown operating system. UniFlash Launcher will not work." >&2
    exit 1
fi

echo "[INFO]: UniFlash version: $uniflash_ver"
echo "[INFO]: UniFlash directory: $uniflash_dir"
echo "[INFO]: dslite.sh script: $dslite_script"

"$dslite_script" "$@"

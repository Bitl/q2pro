#!/bin/sh

CONFIGNAME=config
INPUT=`gcc -dumpmachine`
if [[ $INPUT == *"x86_64"* ]]; then
  CONFIGNAME=config64
fi

echo "Using config '"$CONFIGNAME"'."
cp mgw-sdk/$CONFIGNAME .config
read -p "Press any key to resume after reviewing your config file..."
# review .config
make strip
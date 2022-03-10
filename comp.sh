#!/bin/sh

cp mgw-sdk/config .config
read -p "Press any key to resume after reviewing your config file..."
# review .config
make strip
#!/bin/bash

MAP_DIR="./maps"
PROGRAM="./cub3D"

if [ ! -f "$PROGRAM" ]; then
    echo "Error: Program '$PROGRAM' not found!"
    exit 1
fi

if [ ! -d "$MAP_DIR" ]; then
    echo "Error: Directory '$MAP_DIR' not found!"
    exit 1
fi

USE_VALGRIND=false
if [ "$1" == "mem" ]; then
    USE_VALGRIND=true
    VALGRIND_CMD="valgrind --leak-check=full"
    echo "Running with Valgrind..."
else
    VALGRIND_CMD=""
fi

# Loop through all files starting with "bad_" in the directory
for map in "$MAP_DIR"/bad_*
do
    if [ -f "$map" ]; then
        echo "Running with map: $map"
        if $USE_VALGRIND; then
            $VALGRIND_CMD "$PROGRAM" "$map"
        else
            "$PROGRAM" "$map"
        fi
        echo "-------------------------------------"
    else
        echo "No 'bad_' maps found in $MAP_DIR"
        break
    fi
done

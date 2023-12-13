#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <source_file>"
    exit 1
fi

g++ "$1.cpp" Connection.cpp -o "${1%.*}" -I  -lboost_system -lboost_thread -lSDL2 -lSDL2_net && echo "Compilation successful. Executable '${1%.*}' created." || echo "Compilation failed."
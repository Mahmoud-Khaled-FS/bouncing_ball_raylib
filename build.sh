#!/bin/bash
SOURCE="main.c"
OUTPUT="main"
CFLAGS="-Wall -Wextra -Wpedantic"
LIBS="-lraylib -lm -lpthread -ldl -lrt -lX11"

gcc $CFLAGS $SOURCE -o $OUTPUT $LIBS
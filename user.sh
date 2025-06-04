#!/bin/bash

OUTPUT="user.exe"
INCLUDE_DIR="./src/include"
SRC_MAIN="./src/main/user.c"
HELPERS=$(find ./src/helper -name "*.c")

echo "Compiling user..."
gcc -o $OUTPUT $SRC_MAIN $HELPERS -I$INCLUDE_DIR

if [ $? -eq 0 ]; then
    echo "User compiled successfully!"
    ./$OUTPUT
else
    echo "User compilation failed."
fi

#!/bin/bash

OUTPUT="admin.exe"
INCLUDE_DIR="./src/include"
SRC_MAIN="./src/main/admin.c"
SERVICE=$(find ./src/service -name "*.c")
HELPERS=$(find ./src/helper -name "*.c")

echo "Compiling test..."
gcc -o $OUTPUT $SRC_MAIN $HELPERS $SERVICE -I$INCLUDE_DIR

if [ $? -eq 0 ]; then
    ./$OUTPUT
else
    echo "Test compilation failed."
fi

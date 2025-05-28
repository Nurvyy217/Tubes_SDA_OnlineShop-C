#!/bin/bash

OUTPUT="admin.exe"
INCLUDE_DIR="./src/include"
SRC_MAIN="./src/main/admin.c"
HELPERS=$(find ./src/helper -name "*.c")

echo "Compiling admin..."
gcc -o $OUTPUT $SRC_MAIN $HELPERS -I$INCLUDE_DIR

if [ $? -eq 0 ]; then
    echo "Admin compiled successfully!"
    ./$OUTPUT
else
    echo "Admin compilation failed."
fi

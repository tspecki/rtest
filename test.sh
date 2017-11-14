#!/bin/bash

cd ./cmake/
make
if [ $? -eq 0 ]; then
    cd ..
    ./rar_shot
else
    echo FAIL
fi


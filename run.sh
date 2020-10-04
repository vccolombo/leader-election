#!/bin/sh

cd ./build
cmake ../
cmake --build .
ulimit -s 65536
./application
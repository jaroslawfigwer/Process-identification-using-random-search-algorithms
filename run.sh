#!/bin/bash

mkdir -p build && cd "$_" || exit
cmake .. && make
./Example
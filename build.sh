#!/bin/bash
cmake -S . -B build

cmake --build build --target sfml-template

./build/sfml-template

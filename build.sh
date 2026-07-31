#!/bin/bash
cmake -S . -B default

cmake --build build --target sfml-template

./build/sfml-template

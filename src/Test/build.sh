#!/bin/bash
g++ -shared -Wall -std=c++11 -fPIC -I../../include/ Test.cpp -o Test.so

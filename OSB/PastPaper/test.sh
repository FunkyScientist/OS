#!/bin/bash

gcc client.c -o client
gcc server.c -o server -lm
gcc matrix.c -o matrix

./client localhost 1234
./server 1234
./matrix

ls
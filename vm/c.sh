#!/bin/bash

../software/asm ../champions/$1.s; make; ./corewar ../champions/$1.cor


#!/bin/bash

../software/asm ../champions/$1.s; make; ./vm ../champions/$1.cor

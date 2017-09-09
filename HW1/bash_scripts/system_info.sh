#!/bin/sh


echo Operating System Type: $(uname -o)  > info.txt
echo >> info.txt
echo OS Distribution: $(cat /etc/issue) >> info.txt
echo >> info.txt
echo Kernel Version: $(uname -r) >> info.txt
echo >> info.txt
echo Information on the Kernel build: $(uname -v) >> info.txt
echo >> info.txt
echo Kernel GCC version build: $(gcc --version) >> info.txt
echo >> info.txt
echo Kernel Build time: $(uname -v) >> info.txt
echo >> info.txt
echo System Architecture: $(uname -p) >> info.txt

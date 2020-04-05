#!/bin/bash -e
echo "Compiling"
gcc mmu2.c -o mmu2
echo "Running"
./mmu2 BACKING_STORE.bin addresses.txt > out.txt
echo "Comparing"
diff out.txt correct.txt
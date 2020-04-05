cmake_minimum_required(VERSION 3.15)
project(EECS3221_MiniProject3_master)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(figs)
include_directories(StartKit)

add_executable(EECS3221_MiniProject3_master
        figs/address.png
        figs/vmm.png
        StartKit/addresses.txt
        StartKit/BACKING_STORE.bin
        StartKit/correct.txt
        StartKit/test.sh
        README.md StartKit/mmu.c StartKit/test.c)

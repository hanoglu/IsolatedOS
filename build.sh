#!/bin/bash
rm kernel.iso
nasm -f elf32 -o boot.o kernel.asm 
# gcc -fno-pie -m64 kmain.cpp boot4.o -o kernel.bin -nostdlib -ffreestanding -std=c++11 -mno-red-zone -fno-exceptions -nostdlib -fno-rtti -Wall -Wextra -Werror -m32 -T linker.ld
gcc -fno-pie -m64 kmain.cpp boot.o -o kernel.iso -nostdlib -ffreestanding -std=c++11 -mno-red-zone -fno-exceptions -nostdlib -fno-rtti -Wall -Wextra -m32 -T linker.ld
# 512*16=8192 
# 256K = 262 144
truncate kernel.iso -s 256K

all:
	nasm -f bin boot\boot.asm -o bin\bootloader.bin

	nasm -f elf boot\binaries.asm -o bin\binaries.o

	nasm -f elf kernel\kernel_entry.asm -o bin\kernel_entry.o

	i686-elf-gcc -m32 -ffreestanding -O0 -fno-pic -fno-pie -c kernel\kernel.c -o bin\kernel.o
	
	i686-elf-ld -T linker.ld -o bin\kernel.bin bin\kernel_entry.o bin\kernel.o --oformat binary

	copy /b bin\bootloader.bin + bin\kernel.bin out\os.img

	qemu-system-i386 -drive format=raw,file=out\os.img

asm:
	nasm -f bin boot\boot.asm -o boot.bin

disam:
	ndisasm boot.bin

dikernel:
	ndisasm -b 32 bin\kernel.bin > debug\kernel.txt

celf:
	i686-elf-gcc -m32 -ffreestanding -c kernel\kernel.c -o bin\kernel.o
	i686-elf-ld -T linker.ld bin\kernel.o -o kernel.elf
	i686-elf-objdump -d kernel.elf > debug\kernelElf.txt

obj:
	i686-elf-readelf -a bin\kernel.o > debug\kernelObj.txt

fs:
	qemu-system-x86_64 out\os.img -full-screen
all:
	nasm -f bin boot\boot.asm -o bin\bootloader.bin

	nasm -f elf kernel\kernel_entry.asm -o bin\kernel_entry.o

	i686-elf-gcc -m32 -ffreestanding -O0 -fno-pic -fno-pie -c kernel\kernel.c -o bin\kernel.o
	
	i686-elf-ld -T linker.ld -o bin\kernel.bin bin\kernel_entry.o bin\kernel.o --oformat binary

	copy /b bin\bootloader.bin + bin\kernel.bin out\os.img

	qemu-system-i386 -drive format=raw,file=out\os.img

asm:
	nasm -f bin boot\boot.asm -o boot.bin

disam:
	ndisasm boot.bin

fs:
	qemu-system-x86_64 out\os.img -full-screen
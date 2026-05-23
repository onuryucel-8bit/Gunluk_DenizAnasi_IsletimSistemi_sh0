FLAGS = -m32 -ffreestanding -O0 -fno-pic -fno-pie -c

LINK_FILES = bin\kernel_entry.o \
             bin\kernel.o \
             bin\std_string.o \
             bin\std_cctype.o \
             bin\idt.o \
             bin\idt_asm.o \
			 bin\std_io.o

all:
	nasm -f bin boot\boot.asm -o bin\bootloader.bin

	nasm -f elf kernel\kernel_entry.asm -o bin\kernel_entry.o

	nasm -f elf kernel\idt_asm.asm -o bin\idt_asm.o

	i686-elf-gcc ${FLAGS} kernel\kernel.c -o bin\kernel.o

	i686-elf-gcc ${FLAGS} kernel\std_string.c -o bin\std_string.o

	i686-elf-gcc ${FLAGS} kernel\std_cctype.c -o bin\std_cctype.o

	i686-elf-gcc ${FLAGS} kernel\idt.c -o bin\idt.o

	i686-elf-gcc ${FLAGS} kernel\std_io.c -o bin\std_io.o

	i686-elf-ld -T linker.ld \
	-o bin\kernel.bin \
	${LINK_FILES} \
	--oformat binary

	copy /b bin\bootloader.bin + bin\kernel.bin out\os.img

	
run:
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
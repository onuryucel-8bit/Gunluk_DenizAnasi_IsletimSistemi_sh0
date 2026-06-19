FLAGS = -m32 -ffreestanding -O0 -fno-pic -fno-pie -c

OBJ_FILES = \
	bin/kernel_entry.o \
	bin/idt_asm.o \
	bin/kernel.o \
	bin/string.o \
	bin/cctype.o \
	bin/idt.o \
	bin/portio.o \
	bin/stdlib.o \
	bin/stdio.o	\
	bin/pong.o \
	bin/idtKey.o

all:
	@echo ========================================================
	@echo ============BOOTLOADER==================================
	@echo ========================================================
	nasm -f bin boot\boot.asm -o bin\bootloader.bin
	@echo ========================================================

	nasm -f elf kernel\kernel_entry.asm -o bin\kernel_entry.o

	nasm -f elf kernel\idt\idt_asm.asm -o bin\idt_asm.o
	i686-elf-gcc ${FLAGS} kernel\kernel.c -o bin\kernel.o
	
	i686-elf-gcc ${FLAGS} kernel\idt\idt.c -o bin\idt.o
	i686-elf-gcc ${FLAGS} kernel\idt\idtKey.c -o bin\idtKey.o

	i686-elf-gcc ${FLAGS} kernel\pong.c -o bin\pong.o

	i686-elf-gcc ${FLAGS} kernel\io\portio.c -o bin\portio.o

	i686-elf-gcc ${FLAGS} kernel\std\cctype.c -o bin\cctype.o
	i686-elf-gcc ${FLAGS} kernel\std\stdlib.c -o bin\stdlib.o
	i686-elf-gcc ${FLAGS} kernel\std\string.c -o bin\string.o
	i686-elf-gcc ${FLAGS} kernel\std\stdio.c -o bin\stdio.o

	@echo ==================================
	@echo ======LINKER======================
	@echo ==================================
	i686-elf-ld -T linker.ld \
	-o bin\kernel.bin \
	${OBJ_FILES} \
	--oformat binary

	@echo ===========IMG_FILE==============
	copy /b bin\bootloader.bin + bin\kernel.bin out\os.img
	@echo ==================================
	

run:
	qemu-system-i386 -drive format=raw,file=out\os.img

fs:
	qemu-system-x86_64 out\os.img -full-screen

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

 
ifeq ($(OS),Windows_NT)
    ObjKiller = del /Q
else
    ObjKiller = rm -f
endif

clean:
	$(ObjKiller) bin\*.o
	$(ObjKiller) bin\*.bin
all:
	nasm -f bin boot.asm -o bin\boot.bin

	nasm -f bin mesaj.asm -o bin\mesaj.bin

	copy /b bin\boot.bin + bin\mesaj.bin bin\boot.bin

	qemu-system-x86_64 -drive format=raw,file=bin\boot.bin

asm:
	nasm -f bin boot.asm -o bin\boot.bin

disam:
	ndisasm bin\boot.bin

fs:
	qemu-system-x86_64 bin\boot.bin -full-screen
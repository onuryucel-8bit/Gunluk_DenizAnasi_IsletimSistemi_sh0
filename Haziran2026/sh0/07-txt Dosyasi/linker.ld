OUTPUT_FORMAT(binary)

ENTRY(kernel_main)

INPUT
(
    bin\binaries.o
)


SECTIONS
{
    . = 0x7E00;

    .text : {
        *(.text)
    }

    .rodata : {
        *(.rodata)
    }

    .data : {
        *(.data)
    }

    .bss : {
        *(.bss)
    }
}
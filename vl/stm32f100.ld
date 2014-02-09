/*
Linker script for STM32F100RB. If you are unsure about RAM and flash size, probe the flash with
a telnet connection to openocd - 'flash probe 0'. This will tell you the flash size,128k in this
case. Then check the datasheet's device overview. This will show you the amount of SRAM, 8k here.
*/

/*
There will be a link error if there is not this amount of RAM free at the
end.
*/
ENTRY(main)


/* Memory Spaces Definitions */
MEMORY
{
    RAM (rwx)  : ORIGIN = 0x20000000, LENGTH = 8K
    FLASH (rx) : ORIGIN = 0x08000000, LENGTH = 128K
}

/* highest address of the user mode stack */
_estack = 0x20002000;

/* Sections Definitions */

SECTIONS
{
    . = 0x0;

    .isr_vector :
    {
        . = ALIGN(512);
        __isr_vector_load  = LOADADDR(.isr_vector);
        __isr_vector_start = .;
        KEEP(*(.isr_vector)) /* Vector table in RAM and FLASH */
        . = ALIGN(4);
        __isr_vector_end = .;
    } >RAM AT >FLASH


    .text :
    {
        *(.text)             /* Program code */
        *(.text*)            /* Program code */
        *(.rodata)           /* Read only data */
        *(.rodata*)          /* Read only data */
    } >FLASH

    _sidata = LOADADDR(.data);

    .data :
    {
        . = ALIGN(4);
        _sdata = .;     /* Global symbol at data start */
        *(.data)        /* Data memory */
        *(.data*)       /* Data memory */
        . = ALIGN(4);
        _edata = .;     /* End of initialized data */
    } >RAM AT >FLASH

    .bss :
    {
        . = ALIGN(4);
        _sbss = .;     /* Global symbol at start of bss */
        __bss_start__ = _sbss;
        *(.bss)       /* Zero-filled run time allocate data memory */
        *(.bss*)       /* Zero-filled run time allocate data memory */
        *(COMMON)
        . = ALIGN(4);
        _ebss = .;     /* Global symbol at end of bss */
        __bss_end__ = _ebss;
        _end = .;
        PROVIDE (end = .);
    } >RAM
}

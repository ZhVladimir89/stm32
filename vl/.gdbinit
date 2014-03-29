tar ext:3333
monitor halt
file out/main.elf
load out/main.elf
monitor reset halt
mon arm semihosting enable
stepi



#tar ext:3333
#monitor reset halt
#monitor stm32f1x mass_erase 0
#monitor reset halt
#file out/main.elf
#load out/main.elf
#monitor flash write_image out/main.elf 0
#monitor flash write_bank 0 out/main.elf 0
#monitor program out/main.elf
#monitor reset halt
#stepi

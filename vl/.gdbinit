tar ext:3333
monitor halt
file out/main.elf
load out/main.elf
monitor reset halt
stepi

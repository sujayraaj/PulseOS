#Directories
TOPDIR=.
BIN=$(TOPDIR)/bin
BOOT=$(TOPDIR)/boot
IO=$(TOPDIR)/io
KERNEL=$(TOPDIR)/kernel
SYSTEM=$(TOPDIR)/system
GDT=$(SYSTEM)/gdt
IDT=$(SYSTEM)/idt
ISR=$(SYSTEM)/isr
IRQ=$(SYSTEM)/irq
DISPLAY=$(TOPDIR)/textvideo
ISO=$(TOPDIR)/iso
KEYBOARD=$(TOPDIR)/keyboard
UTILITY=$(TOPDIR)/utility
TIMER=$(TOPDIR)/timer
CRT=$(SYSTEM)/crt
MEM=$(TOPDIR)/memory
#Compiler and Assembler
COMPILERPREFIX=#i386-rtems4.12
CC=$(COMPILERPREFIX)gcc
AS=$(TOPDIR)/nasm-2.13.02rc2/nasm
GAS=$(COMPILERPREFIX)as
CPP=$(COMPILERPREFIX)g++
LD=$(COMPILERPREFIX)ld
DOCKCROSS=$(TOPDIR)/dockcross
INCLUDES= -I$(DISPLAY) -I$(IO) -I$(SYSTEM) -I$(BOOT) -I$(KERNEL) -I$(GDT) -I$(IDT) -I$(ISR) -I$(IRQ) -I$(KEYBOARD) -I$(UTILITY) -I$(TIMER) -I$(MEM)
LINKERLD=-T $(TOPDIR)/linker/linker.ld
FLAGS= -m32 -ffreestanding -O2 -std=gnu99 -Wall -Wextra -nostdlib -fno-exceptions
CPFLAGS= -ffreestanding -O2 -Wall -Wextra -nostdlib -fno-exceptions -fno-rtti
LIBS=-lgcc
CRTI_OBJ=$(BIN)/crti.o
CRTBEGIN_OBJ:=$(shell $(CC) $(CFLAGS) -print-file-name=crtbegin.o)
CRTEND_OBJ:=$(shell $(CC) $(CFLAGS) -print-file-name=crtend.o)
CRTN_OBJ=$(BIN)/crtn.o
OBJF=$(BIN)/kernel.o $(BIN)/boot.o $(BIN)/io.o $(BIN)/textmode.o $(BIN)/vgamodes.o $(BIN)/gdtflush.o $(BIN)/idtload.o $(BIN)/idt.o $(BIN)/isrhand.o $(BIN)/isr.o $(BIN)/utility.o $(BIN)/irqcode.o $(BIN)/irq.o $(BIN)/gdt.o $(BIN)/welcome.o $(BIN)/keyboard.o
OBJ=boot.o io.o textmode.o vgamodes.o gdtflush.o idtload.o idt.o isrhand.o isr.o utility.o irqcode.o irq.o kernel.o gdt.o welcome.o keyboard.o
OBJECTFILES:= $(OBJF)



all: setupNasm  myos.iso

setupNasm:
	if [ -f $(AS) ];\
	then\
		export NASM_FOUND=1;\
	else\
	    cd ./nasm-2.13.02rc2;\
		./autogen.sh;\
		./configure;\
		make -j8;\
	fi;

myos.iso: myos.bin
	qemu-system-i386 -kernel ./bin/myos.bin
#	cp $(BIN)/myos.bin $(ISO)/boot/
#	grub-mkrescue -o myos.iso $(ISO)

myos.bin: $(OBJ)
	$(LD) -m elf_i386 $(LINKERLD) -o $(BIN)/myos.bin $(OBJECTFILES)
#	$(CC) $(INCLUDES) $(LINKERLD) -o $(BIN)/myos.bin $(FLAGS) $(OBJECTFILES) 

boot.o: $(BOOT)/boot.asm
	$(AS) -felf $(BOOT)/boot.asm -o $(BIN)/boot.o

memmgr.o: $(MEM)/memmgr.c
	$(CC) $(INCLUDES) -c $(MEM)/memmgr.c -o $(BIN)/memmgr.o $(FLAGS)

pagefault.o: $(MEM)/pagefault.c
	$(CC) $(INCLUDES) -c $(MEM)/pagefault.c -o $(BIN)/pagefault.o $(FLAGS)

io.o: $(IO)/io.c 
	$(CC) $(INCLUDES) -c $(IO)/io.c -o $(BIN)/io.o $(FLAGS)

gdt.o: $(GDT)/gdt.c gdtflush.o
	$(CC) $(INCLUDES) -c $(GDT)/gdt.c -o $(BIN)/gdt.o $(FLAGS)

gdtflush.o: $(GDT)/gdtflush.asm
	$(AS) -felf $(GDT)/gdtflush.asm -o $(BIN)/gdtflush.o

idt.o: $(IDT)/idt.c idtload.o
	$(CC) $(INCLUDES) -c $(IDT)/idt.c -o $(BIN)/idt.o $(FLAGS)

idtload.o: $(IDT)/idtload.asm
	$(AS) -felf $(IDT)/idtload.asm -o $(BIN)/idtload.o

isr.o: $(ISR)/isr.c isrhand.o
	$(CC) $(INCLUDES) -c $(ISR)/isr.c -o $(BIN)/isr.o $(FLAGS)

isrhand.o: $(ISR)/isrhand.asm
	$(AS) -felf $(ISR)/isrhand.asm -o $(BIN)/isrhand.o

utility.o: $(UTILITY)/utility.c welcome.o
	$(CC) $(INCLUDES) -c $(UTILITY)/utility.c -o $(BIN)/utility.o $(FLAGS)

welcome.o: $(BOOT)/welcome.c 
	$(CC) $(INCLUDES) -c $(BOOT)/welcome.c -o $(BIN)/welcome.o $(FLAGS)

irq.o: $(IRQ)/irq.c irqcode.o
	$(CC) $(INCLUDES) -c $(IRQ)/irq.c -o $(BIN)/irq.o $(FLAGS)

irqcode.o: $(IRQ)/irqcode.asm
	$(AS) -felf $(IRQ)/irqcode.asm -o $(BIN)/irqcode.o

kernel.o: $(KERNEL)/kernel.c
	$(CC) $(INCLUDES) -c $(KERNEL)/kernel.c -o $(BIN)/kernel.o  $(FLAGS)	

textmode.o: $(DISPLAY)/textmode.c
	$(CC) $(INCLUDES) -c $(DISPLAY)/textmode.c -o $(BIN)/textmode.o $(FLAGS)

vgamodes.o: $(DISPLAY)/vgamodes.c
	$(CC) $(INCLUDES) -c $(DISPLAY)/vgamodes.c -o $(BIN)/vgamodes.o $(FLAGS)

keyboard.o: $(KEYBOARD)/keyboard.c
	$(CC) $(INCLUDES) -c $(KEYBOARD)/keyboard.c -o $(BIN)/keyboard.o $(FLAGS)

crti.o: $(CRT)/crti.s
	$(GAS) --32 $(CRT)/crti.s -o $(BIN)/crti.o

crtn.o: $(CRT)/crtn.s
	$(GAS) --32 $(CRT)/crtn.s -o $(BIN)/crtn.o

.PHONY: clean
clean:
	rm $(BIN)/* myos.iso

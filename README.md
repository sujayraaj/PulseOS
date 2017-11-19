# PulseOS v0.2

![PulseOs Screens](https://raw.githubusercontent.com/sujayraaj/PulseOS/master/PulseOS.png)
#### Attempt at making an x86 operating system.

A friendly neighbourhood operating system with a 32 bit kernel. 

Features it has: 

1. Multiboot using grub
2. Colorful text mode output ( and a welcome banner :P )
3. Fully functional keyboard drivers
4. Memory protection using Global Descriptor Table
5. Interrupt Descriptor Tables
6. Interrupts handling using ISR
7. Interrupt Requests 

Now PulseOS uses dock-cross ( https://github.com/dockcross/dockcross ) for cross-compiler management. Also It has its own NASM subtree that gets compiled beforehand.

A dockcross script is attached but you will need your own dockross script to work.

    docker run --rm dockcross/linux-x86 > ./dockcross

To make, 

    ./dockcross bash -c 'make'

There are multiple ways you can go about running the OS.
The simplest is :

    qemu-system-i386 -kernel ./bin/myos.bin

If you are on linux, and you have _grub-mkrescue_ installed, then you can make a multi-booting ISO using it.

    cp ./bin/myos.bin ./iso/boot/
	grub-mkrescue -o myos.iso ./iso
	
And then run it using

    qemu-system-i386  -cdrom ./myos.iso

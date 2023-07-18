head -c 1474560 /dev/zero > MyDrive.vfd
nasm -f bin -o Prog.bin Prog.asm
dd status=noxfer conv=notrunc if=Prog.bin of=MyDrive.vfd




The first of the 3 Linux commands creates and empty Floppy Drive. The next one is to create a .bin file by compiling a Assembly Program
using NASM. The 3rd command inserts the .bin file in the virtual Floppy.
Now, we can use this MyDrive.vfd as a bootable floppy for our raw machine.
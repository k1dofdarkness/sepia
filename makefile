CC=gcc
AS=nasm
CFLAGS=-O2
ASFLAGS=-f elf64
LDFLAGS=-lm

main: main.o image.o sepia.o header.o bmp.o sepia.asm asm.o
	$(CC) $(CFLAGS) -g -F dwarf main.o image.o sepia.o header.o bmp.o asm.o -no-pie -o main $(LDFLAGS)

main.o: main.c image.h sepia.h header.h
	$(CC) $(CFLAGS) -g -F dwarf main.c -no-pie -c

image.o: image.c image.h
	$(CC) $(CFLAGS) image.c -no-pie -c

header.o: header.c header.h
	$(CC) $(CFLAGS) header.c -no-pie -c

sepia.o: sepia.c sepia.h
	$(CC) $(CFLAGS) sepia.c -no-pie -c

bmp.o: bmp.c bmp.h
	$(CC) $(CFLAGS) bmp.c -no-pie -c

asm.o: sepia.asm
	$(AS) $(ASFLAGS) -g -F dwarf sepia.asm -o asm.o


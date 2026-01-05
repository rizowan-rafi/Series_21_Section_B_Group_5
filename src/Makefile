CC = gcc
LD = ld

CFLAGS = -m32 -ffreestanding -fno-builtin -nostdlib -nodefaultlibs -I. -g

LDFLAGS = -m elf_i386 -T link.ld

C_SOURCES = $(wildcard *.c)
S_SOURCES = $(wildcard *.S)

OBJ = $(C_SOURCES:.c=.o) $(S_SOURCES:.S=.o)

KERNEL = kernel.elf

all: $(KERNEL)

$(KERNEL): $(OBJ)
	$(LD) $(LDFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.S
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o $(KERNEL)

run: $(KERNEL)
	qemu-system-i386 -kernel $(KERNEL) -serial stdio -display none
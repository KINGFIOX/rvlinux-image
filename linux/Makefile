BINARY = /oslab/linux/arch/riscv/boot/Image
INITRAMFS = /initramfs/initramfs.cpio.gz

qemu:
	qemu-system-riscv64 -nographic -machine virt \
		-kernel $(BINARY) \
		-initrd $(INITRAMFS) \
		-append "console=ttyS0"

qemu-gdb:
	qemu-system-riscv64 \
		-nographic \
		-machine virt \
		-kernel $(BINARY) \
		-initrd $(INITRAMFS) \
		-append "console=ttyS0" -s -S

SRC := main.c

build: $(SRC)
	rm -f $(INITRAMFS)
	riscv64-unknown-linux-gnu-gcc -static $(SRC) -o /initramfs/bin/a.out
	cd /initramfs && find . -print0 | cpio --null -ov --format=newc | gzip -9 > initramfs.cpio.gz 

gdb:
	riscv64-unknown-elf-gdb -ex "target remote localhost:1234" -ex "file ./linux/vmlinux"

dump:
	riscv64-unknown-linux-gnu-objdump -d /initramfs/bin/a.out > dump.txt
qemu:
	qemu-system-riscv64 -nographic -machine virt \
		-kernel /linux-5.4.286/arch/riscv/boot/Image \
		-initrd /initramfs/initramfs.cpio.gz \
		-append "console=ttyS0"

qemu-gdb:
	qemu-system-riscv64 \
		-nographic \
		-machine virt \
		-kernel /linux-5.4.286/arch/riscv/boot/Image \
		-initrd /initramfs/initramfs.cpio.gz \
		-append "console=ttyS0" -s -S

SRC := main.c

build: $(SRC)
	rm -f /initramfs/initramfs.cpio.gz
	riscv64-linux-gnu-gcc -static $(SRC) -o /initramfs/bin/a.out
	cd /initramfs && find . -print0 | cpio --null -ov --format=newc | gzip -9 > initramfs.cpio.gz 

gdb:
	gdb-multiarch -x .gdbinit
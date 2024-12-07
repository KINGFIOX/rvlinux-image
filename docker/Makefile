qemu:
	qemu-system-riscv64 -nographic -machine virt \
		-kernel linux-5.4.286/arch/riscv/boot/Image \
		-initrd /initramfs/initramfs.cpio.gz \
		-append "console=ttyS0"

qemu-gdb:
	qemu-system-riscv64 -nographic -machine virt \
		-kernel linux-5.4.286/arch/riscv/boot/Image \
		-initrd /initramfs/initramfs.cpio.gz \
		-append "console=ttyS0" -s

gdb:
	gdb
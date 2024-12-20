FROM toolchain:latest

ENV CROSS_COMPILE=riscv64-unknown-linux-gnu-
ENV ARCH=riscv

RUN dnf update -y \
    && dnf install -y git flex bison bc cpio wget qemu-system-riscv64 bear

# download linux and compile it
RUN mkdir -p /oslab && cd /oslab \
    && git clone https://github.com/KINGFIOX/linux-5.4.286 linux \
    && cd /oslab/linux \
    && make defconfig \
    && ./scripts/config --file $PWD/.config \
    -d CONFIG_COMPILE_TEST \
    -e CONFIG_DEBUG_KERNEL \
    -e CONFIG_DEBUG_INFO \
    -d CONFIG_DEBUG_INFO_NONE \
    -e CONFIG_DEBUG_INFO_DWARF_TOOLCHAIN_DEFAULT \
    -d CONFIG_DEBUG_INFO_REDUCED \
    -e CONFIG_DEBUG_INFO_COMPRESSED_NONE \
    -d CONFIG_DEBUG_INFO_COMPRESSED_ZLIB \
    -d CONFIG_DEBUG_INFO_SPLIT \
    -d CONFIG_DEBUG_INFO_BTF \
    -e CONFIG_GDB_SCRIPTS \
    -e DEBUG_INFO_DWARF4 \
    && bear -- make -j$(nproc)

# build busybox
RUN git clone https://git.busybox.net/busybox --depth=1 --branch=1_36_stable \
    && cd /busybox \
    && make defconfig \
    && echo "CONFIG_STATIC=y" >> .config \
    && make -j$(nproc)

# build initramfs
RUN mkdir /initramfs \
    && cd /initramfs \
    && mkdir -p bin \
    && mkdir -p sbin \
    && mkdir -p dev \
    && mkdir -p etc \
    && mkdir -p home \
    && mkdir -p mnt \
    && mkdir -p proc \
    && mkdir -p sys \
    && mkdir -p usr \
    && mkdir -p tmp \
    && mkdir -p usr/bin \
    && mkdir -p usr/sbin \
    && mkdir -p proc/sys/kernel \
    && cd dev \
    && mknod sda b 8 0 \
    && mknod console c 5 1 \
    && cd .. \
    && cp ../busybox/busybox ./bin/ \
    && echo '#!/bin/busybox sh \n\
    /bin/busybox --install -s \n\
    mount -t devtmpfs devtmpfs /dev \n\
    mount -t proc proc /proc \n\
    mount -t sysfs sysfs /sys \n\
    mount -t tmpfs tmpfs /tmp \n\
    setsid cttyhack sh \n\
    echo /sbin/mdev > /proc/sys/kernel/hotplug \n\
    mdev -s \n\
    sh' > init && chmod +x init

# some config
COPY ./.bashrc /root/.bashrc
COPY ./.gdbinit /root/.gdbinit

# directory environment
COPY ./Makefile /oslab/Makefile
WORKDIR /oslab

# install clangd
RUN apt install -y clangd
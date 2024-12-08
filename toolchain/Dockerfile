FROM ubuntu:22.04

# toolchain
RUN apt update -y \
    && apt install -y autoconf automake autotools-dev curl python3 python3-pip libmpc-dev libmpfr-dev libgmp-dev gawk build-essential bison flex texinfo gperf libtool patchutils bc zlib1g-dev libexpat-dev ninja-build git cmake libglib2.0-dev libslirp-dev

RUN git clone https://github.com/riscv/riscv-gnu-toolchain \
    && cd /riscv-gnu-toolchain \ 
    && mkdir newlib_build && cd newlib_build && mkdir -p /opt/riscv/newlib \
    && ../configure --prefix=/opt/riscv/newlib && make -j$(nproc) && make install \
    && cd /riscv-gnu-toolchain \ 
    && mkdir linux_build && cd linux_build && mkdir -p /opt/riscv/linux \
    && ../configure --prefix=/opt/riscv/linux && make -j$(nproc) linux && make install \
    && rm -rf /riscv-gnu-toolchain

ENV PATH="/opt/riscv/newlib/bin:/opt/riscv/linux/bin:$PATH"
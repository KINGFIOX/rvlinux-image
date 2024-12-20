FROM fedora:latest

# toolchain
RUN dnf update -y \
    && dnf install -y git diffutils which \
    autoconf automake python3 libmpc-devel mpfr-devel gmp-devel gawk bison flex texinfo patchutils gcc gcc-c++ zlib-devel expat-devel libslirp-devel

RUN git clone https://github.com/riscv/riscv-gnu-toolchain \
    && cd /riscv-gnu-toolchain \ 
    && mkdir newlib_build && cd newlib_build && mkdir -p /opt/riscv/newlib \
    && ../configure --prefix=/opt/riscv/newlib && make -j$(nproc) && make install \
    && cd /riscv-gnu-toolchain \ 
    && mkdir linux_build && cd linux_build && mkdir -p /opt/riscv/linux \
    && ../configure --prefix=/opt/riscv/linux && make -j$(nproc) linux && make install \
    && rm -rf /riscv-gnu-toolchain

ENV PATH="/opt/riscv/newlib/bin:/opt/riscv/linux/bin:$PATH"
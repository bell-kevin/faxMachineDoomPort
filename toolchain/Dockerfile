FROM ubuntu:24.04

RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y \
    build-essential git make cmake pkg-config \
    gcc-arm-linux-gnueabihf g++-arm-linux-gnueabihf \
    gcc-mips-linux-gnu g++-mips-linux-gnu \
    qemu-user-static file binutils \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /work
CMD ["bash"]

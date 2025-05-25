FROM ubuntu:24.04

RUN apt update && \
    apt install -y --no-install-recommends \
        build-essential \
        gcc-13 g++-13 \
        cmake \
        gdb \
        valgrind \
        linux-tools-generic \
        locales \
        sudo \
        curl \
        git \
        vim \
        pkg-config \
        lsb-release \
        ca-certificates \
        manpages-dev \
        iproute2 \
        netcat-openbsd \
    && update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-13 100 \
    && update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-13 100 \
    && locale-gen en_US.UTF-8

ENV LANG=en_US.UTF-8
ENV LC_ALL=en_US.UTF-8

# Create user to avoid root use in CLion
RUN useradd -ms /bin/bash dev && echo "dev ALL=(ALL) NOPASSWD:ALL" >> /etc/sudoers
USER dev
WORKDIR /home/dev
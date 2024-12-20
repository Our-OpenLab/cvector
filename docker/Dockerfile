FROM ubuntu:22.04

RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    python3-pip \
    git \
    wget \
    curl \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*

RUN pip3 install conan

RUN useradd -ms /bin/bash devuser
USER devuser
WORKDIR /home/devuser/app

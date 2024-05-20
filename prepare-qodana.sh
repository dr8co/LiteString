#!/usr/bin/env sh

# Run from this directory
cd "$(dirname "$0")" || (echo "Running from $(pwd)" && exit 1)

# Install dependencies
sudo apt update && sudo apt install -y ninja-build clang wget tar build-essential

# Download and install CMake
wget -qO- "https://github.com/Kitware/CMake/releases/download/v3.29.3/cmake-3.29.3-linux-x86_64.tar.gz" | tar --strip-components=1 -xz -C /usr/local

# Configure CMake
/usr/local/bin/cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug -DCMAKE_C_COMPILER=gcc -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -G Ninja

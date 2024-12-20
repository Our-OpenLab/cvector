#!/bin/bash

# Colors for output
GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m' # No color

# Directories
BUILD_DIR="build"

# CMake options
CMAKE_BUILD_TYPE="Debug" # Change to "Release" if needed
BUILD_TESTS=ON           # Enable or disable tests

echo -e "${GREEN}--- Configuring and building with CMake ---${NC}"

# Install Conan dependencies if tests are enabled
if [ "$BUILD_TESTS" = "ON" ]; then
    echo -e "${GREEN}--- Installing dependencies with Conan ---${NC}"
    if ! conan install . --output-folder="$BUILD_DIR" --build=missing -s build_type="$CMAKE_BUILD_TYPE"; then
        echo -e "${RED}Conan dependency installation failed.${NC}"
        exit 1
    fi
fi

# Configure and generate build files using CMake
if ! cmake -B "$BUILD_DIR" -DCMAKE_BUILD_TYPE="$CMAKE_BUILD_TYPE" -DBUILD_TESTS="$BUILD_TESTS" -DCMAKE_TOOLCHAIN_FILE="$BUILD_DIR/build/Debug/generators/conan_toolchain.cmake" .; then
    echo -e "${RED}CMake configuration failed.${NC}"
    exit 1
fi

# Build the project
if ! cmake --build "$BUILD_DIR" --config "$CMAKE_BUILD_TYPE"; then
    echo -e "${RED}Build failed.${NC}"
    exit 1
fi

echo -e "${GREEN}--- Build completed successfully ---${NC}"

# Run tests if enabled
if [ "$BUILD_TESTS" = "ON" ]; then
    echo -e "${GREEN}--- Running tests ---${NC}"
    if ! ctest --test-dir "$BUILD_DIR" --output-on-failure; then
        echo -e "${RED}Some tests failed.${NC}"
        exit 1
    fi
    echo -e "${GREEN}All tests passed successfully.${NC}"
fi

echo -e "${GREEN}Script completed successfully.${NC}"

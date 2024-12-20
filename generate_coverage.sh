#!/bin/bash

# Colors for output
GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m' # No color

# Build directory
BUILD_DIR="build"

# Check if gcovr is installed
if ! command -v gcovr &> /dev/null; then
    echo -e "${RED}gcovr is not installed. Please install it.${NC}"
    exit 1
fi

# Check if build directory exists
if [ ! -d "$BUILD_DIR" ]; then
    echo -e "${RED}Build directory '$BUILD_DIR' not found. Please build the project first.${NC}"
    exit 1
fi

# Generate the coverage report
echo -e "${GREEN}--- Generating coverage report with gcovr ---${NC}"
if ! gcovr --root . --filter src/ --html --html-details --output "$BUILD_DIR/coverage.html"; then
    echo -e "${RED}Failed to generate coverage report.${NC}"
    exit 1
fi

echo -e "${GREEN}Coverage report generated at $BUILD_DIR/coverage.html${NC}"

if command -v open &> /dev/null; then
    open "$BUILD_DIR/coverage.html" # macOS
elif command -v xdg-open &> /dev/null; then
    xdg-open "$BUILD_DIR/coverage.html" # Linux
else
    echo -e "${RED}Cannot automatically open the coverage report. Please open it manually.${NC}"
fi

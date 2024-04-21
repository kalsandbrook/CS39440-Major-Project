#!/bin/bash

clean_build=false
run_after_build=false
install_app=false

while [[ "$#" -gt 0 ]]; do
    case $1 in
        --clean) clean_build=true;;
        --run) install_app=true run_after_build=true;;
        --install) install_app=true;;
        *) echo "Unknown parameter passed: $1"; exit 1;;
    esac
    shift
done

# Clear the build directory if specified
if [ "$clean_build" = true ]; then
    if [ -d "build" ]; then
        echo "Removing existing build directory..."
        rm -rf build
    fi
fi

# Create build directory if it doesn't exist
if [ ! -d "build" ]; then
    echo "Creating build directory..."
    mkdir build
fi

# Run CMake
echo "Running CMake..."
cmake -S . -B ./build

# Build the project
echo "Building project..."
cmake --build ./build

if [ "$install_app" = true ]; then
    echo "Installing the application..."
    sudo cmake --install ./build
fi

if [ "$run_after_build" = true ]; then
    echo "Running the application..."
    GamePile
fi

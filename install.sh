#!/bin/bash
echo "Install some required packages"
sudo apt-get install make cmake libsdl2-dev libsdl2-ttf-dev libsdl2-image-dev libsdl2-mixer-dev
echo "Building cmake build"
mkdir build
cd build
cmake ..
echo "Installing Deadly Wish"
sudo make
echo "Cleaning files"
cd ..
sudo rm -rf build
echo "Installation Done."
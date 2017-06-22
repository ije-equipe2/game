#!/bin/bash
sudo apt-get install build-essential devscripts
./install.sh
echo "Copying root files for packaging"
mkdir package/usr
mkdir package/usr/local
mkdir package/usr/local/bin
mkdir package/usr/local/include
mkdir package/usr/local/share
mkdir package/usr/local/lib
sudo mv /usr/local/bin/deadlywish package/usr/local/bin/
sudo mv /usr/local/include/ijengine package/usr/local/include/ijengine
sudo mv /usr/local/lib/kernel.so.0.1.0 package/usr/local/lib/
sudo mv /usr/local/lib/libijengine.a package/usr/local/lib/
sudo mv /usr/local/share/deadlywish package/usr/local/share/deadlywish
echo "Packaging deadlywish"
dpkg-deb -b package/ deadlywish_1.0_amd64.deb
echo "Cleaning files"
sudo rm -rf package/usr
echo "Packaging Done."
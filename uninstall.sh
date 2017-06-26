#!/bin/bash
echo "Uninstalling DeadlyWish"
sudo rm /usr/local/bin/deadlywish
sudo rm /usr/local/lib/kernel.so.0.1.0
sudo rm /usr/local/lib/libijengine.a
sudo rm -r /usr/local/include/ijengine
sudo rm -r /usr/local/share/deadlywish
echo "DeadlyWish unstaled with sucess"
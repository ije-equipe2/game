echo "Install some required packages"
sudo apt-get install libsdl2-dev libsdl2-ttf-dev libsdl2-image-dev libsdl2-mixer-dev
echo "Building cmake build"
mkdir build
cd build
cmake ..
echo "Installing Deadly Wish"
make
echo "Done."
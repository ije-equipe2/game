# Deadly Wish

## Install and Run

```sh
sudo apt-get install libsdl2-dev libsdl2-ttf-dev libsdl2-image-dev libsdl2-mixer-dev 

cd Deadly-Wish/ijengine
tar -vzxf ijengine.tar.gz
make
sudo make install
mkdir ../libs/ && cp kernel/sdl2/kernel.so.0.1.0 ../libs/ 

cd ..
make
./bin/ije02_game
```

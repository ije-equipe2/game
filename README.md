# Deadly Wish

## Automatic Installation

* change the permission of install script and run script

    ```sh
    $ chmod 777 install.sh run.sh uninstall.sh bundle.sh
    ```

* Run the script ```$ ./install.sh``` then run ```$ ./run.sh```

* Enjoy

## Manual Installation

```sh
$ git clone https://github.com/fgagamedev/Deadly-Wish.git

$ sudo apt-get install make cmake libsdl2-dev libsdl2-ttf-dev libsdl2-image-dev libsdl2-mixer-dev 

$ cd Deadly-Wish/
$ mkdir build 
$ cd build
$ cmake ..
$ sudo make
$ cd ..
$ deadlywish
```
## Uninstall
```$ ./uninstall.sh```

## Debian Packaging
```sh
$ ./bundle
$ sudo dpkg -i deadlywish_1.0_amd64.deb
```

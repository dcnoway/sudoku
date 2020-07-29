# Overview
A modern C++ app to solve sudoku problems.
# Development enviroment
## Prerequsite
- cmake
- gcc or clang or visual studio build tools
- Catch2
## Recommand tools
- visual studio code
- vcpkg
## Enviroment setup
```bash
sudo apt update && sudo apt upgrade -y
sudo apt install build-essential tar curl zip unzip
cd ~
git clone https://github.com/microsoft/vcpkg
./vcpkg/bootstrap-vcpkg.sh
./vcpkg/vcpkg install catch2
./vcpkg/vcpkg integrate install
sudo echo "export $VCPKG_ROOT=~/vcpkg/" >> ~/.bashrc
source ~/.bashrc
```
Addtional Doxygen comment documetation toolchain setup
```
sudo apt install doxygen graphviz
```


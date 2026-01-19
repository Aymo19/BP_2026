#! /usr/bin/bash

sudo apt update
sudo apt install gcc-11 g++-11 gcc-13 g++-13
sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-11 11
sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-13 13
sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/g++-11 11
sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/g++-13 13

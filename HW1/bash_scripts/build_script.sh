#!/bin/sh

VERSION = 4.12.13
CORES = 2

echo ..Downloading dependencies
sudo apt-get install libncurses5-dev gcc make git exuberant-ctags bc libssl-dev
wget https://www.kernel.org/pub/linux/kernel/v3.x/linux-$(VERSION).tar.xz
echo extracting packages...
tar -xvJf linux-$(VERSION).tar.xz
cd linux-$(VERSION)
cp /boot/config-$(uname–r) .config
make -j$(CORES)
make modules_install
make install
sudo grub-mkconfig -o /boot/grub/grub.cfg

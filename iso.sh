#!/bin/bash

set -e
. ./build.sh

mkdir -p isodir
mkdir -p isodir/boot
mkdir -p isodir/grub

cp sysroot/boot/oyster.kernal isodir/boot/oyster.kernel
cat > isodir/boot/grub/grub.cfg << EOF
menuentry "oyster" {
  multiboot /boot/oyster.kernel
}
EOF
grub-mkrescue -o oyster.iso isodir

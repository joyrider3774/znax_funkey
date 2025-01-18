#!/bin/sh

make clean
make TARGET=funkey

mkdir -p opk
cp znax opk/znax
cp -r ./graphics opk/graphics
cp -r ./fonts opk/fonts
cp -r ./sound opk/sound
cp -r ./music opk/music
cp Znax.funkey-s.desktop opk/Znax.funkey-s.desktop

mksquashfs ./opk Znax.opk -all-root -noappend -no-exports -no-xattrs

rm -r opk
#!/usr/bin/env bash

set -xe

# If project not ready, generate cmake file.
if [[ ! -d build ]]; then
    mkdir -p build
    cd build
    cmake ..
    cd ..
fi

# Build project.
cd build
make -j
cd ..

# Run all testcases. 
# You can comment some lines to disable the run of specific examples.
rm -rf output
mkdir -p output
mkdir -p output/tmp
time bin/render output
# bin/render testcases/scene01_basic.txt output/scene01.bmp
# bin/render testcases/scene02_cube.txt output/scene02.bmp
# bin/render testcases/scene03_sphere.txt output/scene03.bmp
# bin/render testcases/scene04_axes.txt output/scene04.bmp
# bin/render testcases/scene05_bunny_200.txt output/scene05.bmp
# bin/render testcases/scene06_bunny_1k.txt output/scene06.bmp
# bin/render testcases/scene07_shine.txt output/scene07.bmp

mogrify -format jpg output/final.bmp
rm -rf output_bmp
mkdir -p output_bmp
mv output/final.bmp output_bmp
[ -d output/tmp ] && mv output/tmp output_bmp
mv output/final.jpg output/test-$(date +%m-%d-%H-%M-%S).jpg

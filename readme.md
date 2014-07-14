vtf2tga
=======

Converts Valve Texture Format (.vtf) files to Targa (.tga) files.

### Dependencies
 
 * [VTFLib](https://github.com/panzi/VTFLib) For reading .vtf files.
 * [ImageMagick] (http://www.imagemagick.org/) For writing .tga files.

### Compiling

$g++ -std=c++11 vtf2tga.cpp -lVTFLib13 \`Magick++-config --cppflags --cxxflags --ldflags --libs\` -o vtf2tga.exe

### Usage

$vtf2tga.exe "/path/to/.vtf" "/path/to/output/.tga"

### License

MIT License. See LICENSE file for further details.
# ImageToAscii
ImageToAscii is a program that takes images and turns them into ascii art

# Installation requirements
- CMake
- OpenCV

# Installation instructions
- Configure the build

  `mkdir build`

  `cd build`

  `cmake ..`

- Build the project

  `make`

- Done! you now have an executable which can turn images into ascii art!

# Usage

`./ImageToAscii <options> <image file> <more options>`

For example:

`./ImageToAscii -d 50x50 imagefile.jpg -i`

Here are the possible options you can use:


- `-d`, `--dimensions`

  Set the dimensions of the ascii art, ignoring the aspect ratio of the image

  Usage: `-d <width>x<height>`, `--dimensions <width>x<height>`

  Example: `./ImageToAscii -d 50x50 imagefile.jpg

- `-w`, `--width`
  Set the width of the ascii art, maintaining the aspect ratio of the image

  Usage: `-w <width>`

  Example: `./ImageToAscii -w 50 imagefile.jpg`

- `-h`, `--height`

  Set the height of the ascii art, maintaining the aspect ratio of the image

  Usage: `-h <height>`

  Example: `./ImageToAscii -w 50 imagefile.jpg

- `-i`, `--invert`

  Inverts the ascii image, making whitespace filled, and dark colors unfilled. This is useful
  if you use a white on black colorscheme to view the art

  Usage: `-i`

  Example: `./ImageToascii -i imagefile.jpg`

- `--charset`

  Specify a set of charaters to build the art from

  Usage: `--charset <characters>`, `--charset "<characters>"`
  
  Example: `./ImageToAscii --charset " .:#$"`
  
  By default, uses the first characters for whiter portions of the image, and the later characters for darker portions. 
  Vice-versa if the -i option is used
  

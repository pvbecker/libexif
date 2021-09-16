# libexif project for OS training by PUC

## composition of project
This project has as a motto opening image files and parsing its contents regarding their header's
content, checking if it's either a JIFF or TIFF header.
Initially this library provides pretty much nothing; its goal will be to work somewhat like Phil
Harvey's exiftool, but instead of having to call it from the target program, one will simply need to
import this library and get all important metadata.

## Goals for the lab
### Creating a dynamic library
This is libexif.so; in order to compile it, one can run
> $ make shared
on the /libexif directory and a binary named 'libexif.so' will be generated in the project's build
directory.
### Creating a simple test program
This is exiftest, a more than basic executable at the moment. It simply invokes the only call in the
library, which subsequently prints out to stdout the first header information.
In order to compile it, one can run
> $ make
on the /exiftest directory and a binary named 'exiftest' will be generated in the project's build
directory.
### Creating an installable package for the library
This is done via the **create_package.sh** script. In order to generate it, run
> $./create_package.sh
and a .deb package will be created in the /libexif directory. If the script can't be executed, add
execution permission to the file. The package installation goes to /usr/local/lib directory
### Creating an installable package for the test program
This is also done via a **create_package.sh** script. Same drill, run
> $./create_package.sh
and a .deb package will be created in the /exiftest directory and so on. This executable goes to
/usr/local/bin directory.


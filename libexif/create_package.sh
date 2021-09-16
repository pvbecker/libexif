#!/bin/bash

echo "LIBEXIF package creation script"
echo "Revision numbers and other data will have to be changed in the variables below; still looking
up on how to to this a little better."
echo "create directory structure..."

LIBRARY_NAME="libexif"
MAJOR_VERSION=0
MINOR_VERSION=0
REVISION_NUMBER=0

PACKAGE_NAME=$LIBRARY_NAME-$MAJOR_VERSION.$MINOR_VERSION-$REVISION_NUMBER
mkdir $PACKAGE_NAME
mkdir $PACKAGE_NAME/usr
mkdir $PACKAGE_NAME/usr/local
mkdir $PACKAGE_NAME/usr/local/lib

echo "guaranteeing a fresh build and that the target binaries will be in place..."
make clean
make shared
cp build/libexif.so $PACKAGE_NAME/usr/local/lib

echo "creating control file"
mkdir $PACKAGE_NAME/DEBIAN
PACKAGE_INFO="Package: libexif
Version: 0.0-0
Section: base
Priority: optional
Architecture: i386
Depends:
Maintainer: Paulo Andrade <pevebecker@gmail.com>
Description: libexif
 This library is a first attempt on generating something like Phil Harvey's exiftool, but in both
 static and shared library formats, in order to more easily have access to image metadata on certain
 environments, when either we don't have access to exiftool's executable or don't want to pipe it's
 output to our program."
echo -e "$PACKAGE_INFO" > $PACKAGE_NAME/DEBIAN/control

dpkg-deb --build $PACKAGE_NAME

echo clean up afterwards, removing package directory...
rm -rf $PACKAGE_NAME
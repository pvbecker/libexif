#!/bin/bash

echo "LIBEXIF package creation script"
echo "Revision numbers and other data will have to be changed in the variables below; still looking
up on how to to this a little better."
echo "create directory structure..."

LIBRARY_NAME="exifdump"
MAJOR_VERSION=0
MINOR_VERSION=0
REVISION_NUMBER=0

PACKAGE_NAME=$LIBRARY_NAME-$MAJOR_VERSION.$MINOR_VERSION-$REVISION_NUMBER
mkdir $PACKAGE_NAME
mkdir $PACKAGE_NAME/usr
mkdir $PACKAGE_NAME/usr/local
mkdir $PACKAGE_NAME/usr/local/bin

echo "guaranteeing a fresh build and that the target binaries will be in place..."
make clean
make
cp build/exifdump $PACKAGE_NAME/usr/local/bin

echo "creating control file"
mkdir $PACKAGE_NAME/DEBIAN
PACKAGE_INFO="Package: exifdump
Version: 0.0-0
Section: base
Priority: optional
Architecture: i386
Depends: libexif
Maintainer: Paulo Andrade <pevebecker@gmail.com>
Description: exifdump
 Very silly test program for my libexif shared library."
echo -e "$PACKAGE_INFO" > $PACKAGE_NAME/DEBIAN/control

dpkg-deb --build $PACKAGE_NAME

echo clean up afterwards, removing package directory...
rm -rf $PACKAGE_NAME
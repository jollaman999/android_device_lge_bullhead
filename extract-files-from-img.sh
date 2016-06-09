#!/bin/bash

# Modified by jollaman999

# 1. Make folder named 'system' in home dirctory.
# 2. Copy 'system.img' to '~/system/'.
# 3. Launch this file.

export VENDOR=lge
export DEVICE_VENDOR=lge
export DEVICE=bullhead
# Check to see if the user passed a folder in to extract from rather than adb pull
if [ $# -eq 1 ]; then
COPY_FROM=$1
test ! -d "$COPY_FROM" && echo error reading dir "$COPY_FROM" && exit 1
fi
set -e

function extract_img() {
if [ ! -e ~/system/system.img ]; then
echo system.img not found in '~/system/'
exit 2
fi

rm -rf extracted/
rm -rf  ~/system/extracted/
./imgtool ~/system/system.img extract
mv extracted/ ~/system/
}

function mount_img() {
if [ ! -e ~/system/extracted/image.img ]; then
echo image.img not found in '~/system/extracted/'
exit 3
fi

if [ ! -d ~/system/mount_dir ]; then
mkdir ~/system/mount_dir
fi
echo
echo "Type \"sudo mount ~/system/extracted/image.img ~/system/mount_dir\" in another shell."
echo "If mounted already, skip this step."
echo
echo "If you mounted successfully, type this command to prevent permission denial."
echo "\"sudo chmod o+r ~/system/mount_dir/bin/qmuxd\""
echo
read -p "Press [Enter] to continue..."
}

function extract() {
echo
for FILE in `egrep -v '(^#|^$)' $1`; do
echo "Extracting /system/$FILE ..."
OLDIFS=$IFS IFS=":" PARSING_ARRAY=($FILE) IFS=$OLDIFS
FILE=`echo ${PARSING_ARRAY[0]} | sed -e "s/^-//g"`
DEST=${PARSING_ARRAY[1]}
if [ -z $DEST ]; then
DEST=$FILE
fi
DIR=`dirname $FILE`
if [ ! -d $2/$DIR ]; then
mkdir -p $2/$DIR
fi
if [ "$COPY_FROM" = "" ]; then
# Try destination target first
if [ -f /system/$DEST ]; then
cp ~/system/mount_dir/$DEST $2/$DEST
else
# if file does not exist try OEM target
if [ "$?" != "0" ]; then
cp ~/system/mount_dir/$FILE $2/$DEST
fi
fi
else
# Try destination target first
if [ -f $COPY_FROM/$DEST ]; then
cp $COPY_FROM/$DEST $2/$DEST
else
# if file does not exist try OEM target
if [ "$?" != "0" ]; then
cp $COPY_FROM/$FILE $2/$DEST
fi
fi
fi
done
}

extract_img
mount_img
APP_TEMP=../../../vendor/$VENDOR/$DEVICE/app
DEVICE_BASE=../../../vendor/$VENDOR/$DEVICE/proprietary
mv $DEVICE_BASE/app $APP_TEMP
rm -rf $DEVICE_BASE/*
mv $APP_TEMP $DEVICE_BASE/app
# Extract the device specific files
extract ../../$DEVICE_VENDOR/$DEVICE/proprietary-blobs.txt $DEVICE_BASE
./setup-makefiles.sh

echo
echo "Finished"
echo "Type \"sudo umount ~/system/mount_dir\" to unmount mounted system directory"

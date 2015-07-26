#!/usr/bin/env bash

TIMESTAMP=`date +%Y-%m-%d-%H-%M-%S`

make linux
PACK_NAME=nnlaf_linux_$TIMESTAMP
cp -rv ./bin/linux ./packs/$PACK_NAME
(cd packs && zip -r $PACK_NAME $PACK_NAME)

make win32
PACK_NAME=nnlaf_win32_$TIMESTAMP
cp -rv ./bin/win32 ./packs/$PACK_NAME
(cd packs && zip -r $PACK_NAME $PACK_NAME)


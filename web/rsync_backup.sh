#!/usr/bin/env sh
rsync -e ssh -av --bwlimit=100 --delete-during Animations Books Documents Fonts Icons Projects Pictures Old b318293@hanjin.dreamhost.com:~/

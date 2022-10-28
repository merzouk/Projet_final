#!/bin/sh

if test -f  "$1"; then
        dt=$(date  "+%Y%m%d-%H%M%S%s")
        mv "$1" /home/mrzk/success/"$dt"
fi

exit 0
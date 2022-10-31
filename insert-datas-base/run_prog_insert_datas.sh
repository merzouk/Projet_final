#!/bin/sh

source=/home/mrzk/datas/

for entry in "$source"*;
do
        ./insert_db "$entry"  ../values.properties
        sleep 1
done

exit 0

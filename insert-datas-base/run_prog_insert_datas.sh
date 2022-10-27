#!/bin/sh
source=/home/mrzk/datas/

for entry in "$source"*;
do
        ./insert_db "$entry"  /usr/local/db/meteo.db
        sleep 1
done

exit 0

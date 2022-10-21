#!/bin/sh
source=/home/ubuntu/datas/

for entry in "$source"*;
do
        ./insert_db "$entry"  /usr/local/db/db_temperature.db
        sleep 1
done

exit 0

#!/bin/sh


if [ "$#" -eq 0 ]; then
        echo "Le numero de port du server TCP n'est pas renseigne"
        exit 1
fi

g++ -L /usr/lib/ -L/usr/include  -o "read_db" *.cpp  -lboost_system -lboost_thread -lpthread -lsqlite3

./read_db "$1" "$2"

exit 0
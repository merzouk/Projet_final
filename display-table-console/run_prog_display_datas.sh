#!/bin/sh


if [ "$#" -eq 0 ]; then
        echo "Le numero de port du server TCP n'est pas renseigne"
        exit 1
fi

g++ -L /usr/lib/ -L/usr/include  -o "client" *.cpp  -lboost_system -lboost_thread -lpthread -lsqlite3

./client "$1" "$2" 

exit 0
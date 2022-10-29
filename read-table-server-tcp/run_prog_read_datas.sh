#!/bin/sh

if [ "$#" -ne 3 ]; then
        echo "                                Deux parametres sont attendus : "
	    echo "                                   1) Le numero de port du service Boost::asio sur le server TCP "
	    echo "                                   2) Le chemin vers le fichier de ressources"
	    exit 1
fi

echo "1) build and create executable"

g++ -L /usr/lib/ -L/usr/include  -o "read_db" *.cpp  -lboost_system -lboost_thread -lpthread -lsqlite3

echo "2) run executable"

./read_db "$1" "$2"

exit 0
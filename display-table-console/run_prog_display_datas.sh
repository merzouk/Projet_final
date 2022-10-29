#!/bin/sh

if [ "$#" -ne 2 ]; then
        echo "                                Deux parametres sont attendus : "
	    echo "                                   1) Le numero de port du service Boost::asio sur le server TCP "
	    echo "                                   2) Le chemin vers le fichier de ressources"
	    exit 1
fi

echo "1) build and create executable"

g++ -L /usr/lib/ -L/usr/include  -o "client" *.cpp  -lboost_system -lboost_thread -lpthread -lsqlite3

echo "2) run executable"

./client "$1" "$2" 

exit 0
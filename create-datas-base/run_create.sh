#!/bin/sh

#g++ -L/usr/include -o "create_db"  *.cpp  -lsqlite3

if [ "$#" -eq 0 ]; then
        echo "Le chemin vers le fichier ressources est obligatoire"
        exit 1
fi

./create_db "$1"

rm create_db

exit 0

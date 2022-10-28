#!/bin/sh

g++ -L /usr/lib/ -L/usr/include  -o "read_db" *.cpp  -lboost_system -lboost_thread -lpthread -lsqlite3

exit 0
#Manage cpp project by Makefile

OS=linux

CC = g++  -L/usr/include -g -Wall -ansi -pedantic -lsqlite3

PROG=manage_prj
ARCHIVE=sortie.zip
TARGET_ARCHIVE=*.cpp *.hpp Makefile

ifeq ($(OS), linux)
	DELETE=rm -rf $(PROG) $(ARCHIVE)
	ZIP=tar -cvzf $(ARCHIVE) $(TARGET_ARCHIVE)
	CLEAN=rm -rf *.o
else
	DELETE=del $(PROG) $(ARCHIVE)
endif

#Identifier tous les fichiers .cpp de mon programme
SRC = $(wildcard *.cpp)

#Créer une liste des fichiers .o liés aux fichiers .cpp
OBJ = $(SRC:.cpp=.o)

all: $(PROG)

$(PROG): $(OBJ)
	@echo "Fin build des fichiers .o et generation du fichier executable ==> \"$(PROG)\" : "
	$(CC) -o $@  $^

%.o : %.c
	$(CC) -o $@ -c $<

clean:
	@echo "Suppresion des fichiers .o : "
	$(CLEAN)

mrproper: clean
	@echo "Suppresion du programme executable \"$(PROG)\" et du fichier archive \"$(ARCHIVE)\" : "
	$(DELETE)

zip:
	@echo "Generation du fichier archive \"$(ARCHIVE)\" : "
	$(ZIP)

#g++ -L/usr/include -o "create"  *.cpp  -lsqlite3

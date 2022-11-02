#Manage cpp project by Makefile

CLEAN = rm -rf *.o
PROG = create_db
CLEAN_EXEC=rm $(PROG)

ARCHIVE=sortie.zip
TARGET_ARCHIVE=*.cpp *.hpp Makefile
ZIP=tar -cvzf $(ARCHIVE) $(TARGET_ARCHIVE)
CLEAN_ZIP=rm $(ARCHIVE)

CC = g++ -L /usr/lib/ -L/usr/include  -o $(PROG) *.cpp
SQLITE = -lpthread -lsqlite3


build:
	@echo "Fin build des fichiers .o et generation du fichier executable ==> \"$(PROG)\" : "
	$(CC) $(SQLITE)

clean:
	@echo "Suppresion des fichiers .o, \"$(PROG)\" et \"$(ARCHIVE)\": "
	$(CLEAN) $(CLEAN_EXEC) $(CLEAN_ZIP)

zip:
	@echo "Generation du fichier archive \"$(ARCHIVE)\" : "
	$(ZIP)

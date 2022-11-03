#Manage cpp project by Makefile

CLEAN = rm -rf *.o
PROG = client
CLEAN_EXEC=rm $(PROG)

ARCHIVE=sortie.zip
TARGET_ARCHIVE=*.cpp *.hpp Makefile
ZIP=tar -cvzf $(ARCHIVE) $(TARGET_ARCHIVE)
CLEAN_ZIP=rm $(ARCHIVE)

CC = g++ -L /usr/lib/ -L/usr/include  -o $(PROG) *.cpp
BOOST = -lboost_system -lboost_thread
SQLITE = -lpthread -lsqlite3


build:
	@echo "Fin build et generation du fichier executable ==> \"$(PROG)\" : "
	$(CC) $(BOOST) $(SQLITE)

clean:
	@echo "Suppresion des fichiers .o, \"$(PROG)\" et \"$(ARCHIVE)\": "
	$(CLEAN) $(CLEAN_EXEC) $(CLEAN_ZIP)

zip:
	@echo "Generation du fichier archive \"$(ARCHIVE)\" : "
	$(ZIP)

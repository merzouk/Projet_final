#Manage cpp project by Makefile

CLEAN = rm -rf sources/*.o
PROG = create_db
CLEAN_EXEC=rm $(PROG)

ARCHIVE=sortie.zip
TARGET_ARCHIVE=sources/*.cpp header/*.hpp Makefile
ZIP=tar -cvzf $(ARCHIVE) $(TARGET_ARCHIVE)
CLEAN_ZIP=rm $(ARCHIVE)

CC = g++ -L /usr/lib/ -L/usr/include  -o $(PROG) sources/*.cpp
SQLITE = -lpthread -lsqlite3


build:
	@echo "Début du build et génération du fichier exécutable ==> \"$(PROG)\" : "
	$(CC) $(SQLITE)

clean:
	@echo "Suppresion des fichiers .o, \"$(PROG)\" et \"$(ARCHIVE)\": "
	$(CLEAN) $(CLEAN_EXEC) $(CLEAN_ZIP)

zip:
	@echo "Génération du fichier archive \"$(ARCHIVE)\" : "
	$(ZIP)

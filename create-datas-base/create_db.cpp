#include <iostream>
#include <sqlite3.h>
#include <string>

#include "ManageProperties.hpp"

#include "Logger.hpp"

#include <chrono> //milliseconds
#include <thread> //sleep_for

using namespace std;
using namespace Manage;

static int callback(void *NotUsed, int argc, char **argv, char **szColName)
{
  return 0;
}

int main(int argc, char **argv)
{
        sqlite3 *db;
        char *errorMsg = 0;

        if(argc < 2)
        {
                Logger::log(2, "Le chemin vers le fichier ressources est obligatoire\n");
                return 1;
        }

        string properties_file = argv[1];
        if(properties_file.size() == 0)
	 {
                Logger::log(2,  "Le fichier ressources \"" + properties_file + "\" n'est pas renseigne, parametres manquants, connexion impossible" );
                return 1;
	 }
	 ManageProperties * manageProperties = new ManageProperties();
        manageProperties->read_contains_properties_file(properties_file, ':');
        if(manageProperties->size_map() == 0)
        {
                Logger::log(2,  "Aucun parametre trouve dans le fichier ressources, creation de la base de donnees impossible");
                return 1;
	 }

        string path_db =  manageProperties->get_value_by_key("url_data_base");
        const char * db_name = path_db.c_str();

        // open database
        int rc = sqlite3_open(db_name, &db);

        if (rc)
        {
                Logger::log(2,  "Can't open database");
        }
        else
        {
                Logger::log(1,  "Open database successfully");
        }

	 string sql_query_create_table =  manageProperties->get_value_by_key("request_create_table");

        // prepare our sql statements
        const char *pSQL = sql_query_create_table.c_str();

        // execute sql
        rc = sqlite3_exec(db, pSQL, callback, 0, &errorMsg);
        if (rc != SQLITE_OK)
        {
                Logger::log(2, "Can't create table inside database");
                Logger::log(2, "SQL Error :  ");
                Logger::log(2,  errorMsg  );
                sqlite3_free(errorMsg);
                if (db)
                {
                        sqlite3_close(db);
                }
                return 1;
        }

        // close database
        if (db)
        {
                Logger::log(1,  "Create table successfully");
                sqlite3_close(db);
        }

        delete manageProperties;
        manageProperties = nullptr;

        return 0;
}

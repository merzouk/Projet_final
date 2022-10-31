
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
        // Initiate logger (default name is 'log')
        LOG_INIT_CERR();
        sqlite3 *db;
        char *errorMsg = 0;

        if(argc < 2)
        {
                log(LOG_ERR) <<"Le chemin vers le fichier ressources est obligatoire\n";
                return 1;
        }

        string properties_file = argv[1];
        if(properties_file.size() == 0)
	 {
           log(LOG_ERR)  <<  "Le fichier ressources n'est pas renseigne, parametres manquants, connexion impossible : " + properties_file + "\n" ;
           return 1;
	 }
	 ManageProperties * manageProperties = new ManageProperties();
        manageProperties->read_contains_properties_file(properties_file, ':');
        if(manageProperties->size_map() == 0)
        {
                log(LOG_ERR)  <<   "Aucun parametre trouve dans le fichier ressources, connexion impossible\n";
                return 1;
	 }

        string path_db =  manageProperties->get_value_by_key("url_data_base");
        const char * db_name = path_db.c_str();

        // open database
        int rc = sqlite3_open(db_name, &db);

        if (rc)
        {
                log(LOG_ERR) << "Can't open database\n";
        }
        else
        {
                log(LOG_INFO) << "Open database successfully\n";
        }


	 string sql_query_create_table =  manageProperties->get_value_by_key("create_table");

	 cout <<"sql_query_create_table : " << sql_query_create_table << endl;

        // prepare our sql statements
        const char *pSQL = sql_query_create_table.c_str();
                        //"CREATE TABLE temp_datas(id INTEGER PRIMARY KEY AUTOINCREMENT, identite_capt varchar(50), temperature FLOAT, humidity FLOAT, pressure FLOAT, gyro_x FLOAT, gyro_y FLOAT, gyro_z FLOAT, accel_x FLOAT, accel_y FLOAT, accel_z FLOAT, seconde SMALLINT, minute SMALLINT, heure SMALLINT, jour SMALLINT, mois SMALLINT, annee SMALLINT)";

        // execute sql
        rc = sqlite3_exec(db, pSQL, callback, 0, &errorMsg);
        if (rc != SQLITE_OK)
        {
                log(LOG_ERR) << "Can't create table temp_datas inside database \n";
                log(LOG_ERR) << "SQL Error : "  +std::string(errorMsg) + "\n";
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
                log(LOG_INFO) << "Create temp_datas table successfully\n";
                sqlite3_close(db);
        }

        delete manageProperties;
        manageProperties = nullptr;

        return 0;
}

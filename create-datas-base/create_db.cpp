
#include <iostream>
#include <sqlite3.h>
#include <string>

#include "Logger.hpp"

#include <chrono> //milliseconds
#include <thread> //sleep_for

using namespace std;

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
                log(LOG_ERR) <<"Le chemin vers le dossier de la base de donnees est obligatoire\n" ;
                return 1;
        }
        string path_db = argv[1];
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

        // prepare our sql statements
        const char *pSQL =
                        "CREATE TABLE temp_datas(id INTEGER PRIMARY KEY AUTOINCREMENT, identite_capt varchar(50), temperature FLOAT, humidity FLOAT, pressure FLOAT, gyro_x FLOAT, gyro_y FLOAT, gyro_z FLOAT, accel_x FLOAT, accel_y FLOAT, accel_z FLOAT, seconde SMALLINT, minute SMALLINT, heure SMALLINT, jour SMALLINT, mois SMALLINT, annee SMALLINT)";

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

        return 0;
}

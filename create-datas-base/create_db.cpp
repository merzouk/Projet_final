
#include <iostream>
#include <sqlite3.h>

using namespace std;

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
                cout <<"Le chemin vers le dossier de la base de donnees est obligatoire" << endl;
                return 1;
        }
        string path_db = argv[1];
        const char * db_name = path_db.c_str();

        // open database
        int rc = sqlite3_open(db_name, &db);

        if (rc)
        {
                std::cout << "Can't open database" << endl;
        }
        else
        {
                std::cout << "Open database successfully" << endl;
        }

        // prepare our sql statements
        const char *pSQL =
                        "CREATE TABLE temp_datas(id INTEGER PRIMARY KEY AUTOINCREMENT, identite_capt varchar(50), temperature FLOAT, humidity FLOAT, pressure FLOAT, gyro_x FLOAT, gyro_y FLOAT, gyro_z FLOAT, accel_x FLOAT, accel_y FLOAT, accel_z FLOAT, seconde SMALLINT, minute SMALLINT, heure SMALLINT, jour SMALLINT, mois SMALLINT, annee SMALLINT)";

        // execute sql
        rc = sqlite3_exec(db, pSQL, callback, 0, &errorMsg);
        if (rc != SQLITE_OK)
        {
                std::cout << "Can't create table temp_datas inside database " << endl;
                std::cout << "SQL Error: " << errorMsg << std::endl;
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
                std::cout << "Create temp_datas table successfully" << endl;
                sqlite3_close(db);
        }

        return 0;
}

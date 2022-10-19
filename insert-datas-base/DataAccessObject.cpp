#include "DataAccessObject.hpp"

#include <sqlite3.h>
#include <exception>

using namespace std;

namespace DataAccess
{
       static int callback(void *NotUsed, int argc, char **argv, char **szColName)
       {
         return 0;
       }

       string build_query(string sql_insert, DatasCapteur* data)
       {
                sql_insert += data->get_identite_capt()+ "',";
                sql_insert += to_string(data->get_temperature())+",";
                sql_insert += to_string(data->get_humidity())+",";
                sql_insert += to_string(data->get_pressure())+",";

                sql_insert += to_string(data->get_gyro_x())+",";
                sql_insert += to_string(data->get_gyro_y())+",";
                sql_insert += to_string(data->get_gyro_z())+",";

                sql_insert += to_string(data->get_accel_x())+",";
                sql_insert += to_string(data->get_accel_y())+",";
                sql_insert += to_string(data->get_accel_z())+",";

                sql_insert += to_string(data->get_seconde())+",";
                sql_insert += to_string(data->get_minute())+",";
                sql_insert += to_string(data->get_heure())+",";
                sql_insert += to_string(data->get_jour())+",";
                sql_insert += to_string(data->get_mois())+",";
                sql_insert += to_string(data->get_annee())+")";
                return sql_insert;
       }

       int insert_data(string sql_insert, const char * path_data_base, DatasCapteur* data)
       {
         sqlite3 *db;
         char *errorMsg = 0;

         // open database
         int rc = sqlite3_open(path_data_base, &db);

         if(rc)
         {
           std::cout << "Can't open database\n";
           return 1;
         }
         else
         {
           //std::cout << "Open database successfully" << endl;
         }
         sql_insert = build_query(sql_insert, data);
         // prepare our sql statements
         const char *pSQL = sql_insert.c_str();
        // execute sql
         rc = sqlite3_exec(db, pSQL, callback, 0, &errorMsg);
         if(rc != SQLITE_OK)
         {
             std::cout << "SQL Error: " << errorMsg << std::endl;
             sqlite3_free(errorMsg);
             if(db)
             {
                     sqlite3_close(db);
             }
             return 1;
         }
         // close database
         if(db)
         {
           sqlite3_close(db);
         }
         return 0;
       }

       void DataAccessObject::insert_data_into_table(DatasCapteur* data, const char * path_data_base)
       {
             try
             {
                     int res = insert_data(this->constantes->get_query_insert(), path_data_base, data);
                     if(res == 1) cout << "Insertion terminee en echec " << data->get_identite_capt() << endl;
             }
             catch(exception& e)
             {
                     cout << "Erreur pendant la tentative d'insertion en base : " << e.what() << endl;
             }
       }

       void DataAccessObject::insert_datas_into_table(std::vector<DatasCapteur *> datas_capteur, const char * path_data_base)
       {
              for(DatasCapteur * data : datas_capteur)
                   this->insert_data_into_table(data, path_data_base);
       }
}

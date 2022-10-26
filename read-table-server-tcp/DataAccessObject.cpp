#include <vector>
#include "DatasCapteur.hpp"
#include "DataAccessObject.hpp"
#include <sqlite3.h>

using namespace Datas;

namespace DataAccess
{
              vector<DatasCapteur *> datas;
              // This is the callback function to display the select data in the table
              static int callback(void *NotUsed, int argc, char **argv, char **szColName)
              {
                DatasCapteur * data = new DatasCapteur();
                for(int i = 0; i < argc; i++)
                {
                  switch(i)
                  {
                     case 0 :
                            data->set_id(atoi(argv[i]));
                            break;
                     case 1 :
                            data->set_identite_capt(argv[i]);
                            break;
                     case 2 :
                            data->set_temperature(atof(argv[i]));
                            break;
                     case 3 :
                            data->set_humidity(atof(argv[i]));
                            break;
                     case 4 :
                            data->set_pressure(atof(argv[i]));
                            break;
                     case 5 :
                            data->set_gyro_x(atof(argv[i]));
                            break;
                     case 6 :
                            data->set_gyro_y(atof(argv[i]));
                            break;
                     case 7 :
                            data->set_gyro_z(atof(argv[i]));
                            break;
                     case 8 :
                            data->set_accel_x(atof(argv[i]));
                            break;
                     case 9 :
                            data->set_accel_y(atof(argv[i]));
                            break;
                     case 10 :
                            data->set_accel_z(atof(argv[i]));
                            break;
                     case 11 :
                            data->set_seconde(atoi(argv[i]));
                            break;
                     case 12 :
                            data->set_minute(atoi(argv[i]));
                            break;
                     case 13 :
                            data->set_heure(atoi(argv[i]));
                            break;
                     case 14 :
                            data->set_jour(atoi(argv[i]));
                            break;
                     case 15 :
                            data->set_mois(atoi(argv[i]));
                            break;
                     case 16 :
                            data->set_annee(atoi(argv[i]));
                            break;
                  }
                }
                datas.push_back(data);
                return 0;
              }

              vector<DatasCapteur *> load_datas_capteur(const char * path_data_base, const char *sql_query)
              {
                sqlite3 *db;
                char *errorMsg = 0;
                datas.clear();

                // open database
                int rc = sqlite3_open(path_data_base, &db);

                if(rc)
                {
                  std::cout << "Can't open database" << endl;;
                }
                else
                {
                  //std::cout << "Open database successfully" << endl;
                }

                rc = sqlite3_exec(db, sql_query, callback, 0, &errorMsg);
                if(rc != SQLITE_OK)
                {
                    std::cout << "SQL Error: " << errorMsg << std::endl;
                    sqlite3_free(errorMsg);
                     if(db)
                       {
                         sqlite3_close(db);
                       }
                       return datas;
                }
                // close database
                if(db)
                {
                  sqlite3_close(db);
                }
                return datas;
              }

              vector<DatasCapteur*> DataAccessObject::load_datas(const char * path_data_base, const char *sql_query)
              {
                      datas.clear();
                      return load_datas_capteur(path_data_base, sql_query);
              }

              string DataAccessObject::load_details_capteur(string id_capteur)
              {
                     string str_capteur;

                     return str_capteur;
              }
}

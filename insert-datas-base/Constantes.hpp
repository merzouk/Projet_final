
#ifndef CONST_H_FILE
#define CONST_H_FILE


#include <string>


using namespace std;

namespace Manage
{
              class Constantes
              {
                     private:
                           string sql_insert = "INSERT INTO temp_datas(identite_capt, temperature, humidity, pressure , "+
                                               "gyro_x, gyro_y, gyro_z, accel_x, accel_y, accel_z, "+
                                               "seconde, minute, heure, jour, mois, annee) VALUES ('";
                     public:
                            Constantes(){}
                            ~Constantes(){}
                            string get_query_insert()
                            {
                                   return this->sql_insert;
                            }
              };
}

#endif // CONST_H_FILE

#ifndef CONST_H_FILE
#define CONST_H_FILE


#include <string>


using namespace std;

namespace Manage
{
              class Constantes
              {
              private:
                     const char * url_data_base = "/usr/local/db/meteo.db";
                     const char *sql_query = "SELECT * FROM temp_datas";
                     string sql_by_id = "SELECT * FROM temp_datas where id = ";
                     string sql_by_cpt_id = "SELECT * FROM temp_datas where identite_capt = '";
                     string sql_by_day = "SELECT * FROM temp_datas where jour = ";
                     string sql_by_hour = "SELECT * FROM temp_datas where heure = ";
              public:
                     Constantes(){}
                     ~Constantes(){}
                     const char * get_url_db()
                     {
                            return this->url_data_base;
                     }
                     const char * get_query_all()
                     {
                            return this->sql_query;
                     }
                     string get_query_by_id()
                     {
                            return this->sql_by_id;
                     }
                     string get_query_by_capt_id()
                     {
                            return this->sql_by_cpt_id;
                     }
                     string get_query_by_day()
                     {
                            return this->sql_by_day;
                     }
                     string get_query_by_hour()
                     {
                            return this->sql_by_hour;
                     }
              };
}

#endif // CONST_H_FILE

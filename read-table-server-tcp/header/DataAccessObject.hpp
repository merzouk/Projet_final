#ifndef DTO_H_FILE
#define DTO_H_FILE
#include <vector>
#include "DatasCapteur.hpp"

#include <iostream>
#include <sqlite3.h>

using namespace Datas;

namespace DataAccess
{

       class DataAccessObject
       {
              private:
                     vector<DatasCapteur *> datas;
              public:
                     DataAccessObject(){};
                     ~DataAccessObject(){}
                     vector<DatasCapteur *> load_datas(const char * path_data_base, const char *sql_query);
                     string load_details_capteur(string id_capteur);
       };
}

#endif // DTO_H_FILE

#ifndef DTO_H_FILE
#define DTO_H_FILE

#include "DatasCapteur.hpp"
#include "Constantes.hpp"
#include <vector>

using namespace Datas;
using namespace Manage;

namespace DataAccess
{
       class DataAccessObject
       {
              private:
                     Constantes * constantes;
              public:
                     DataAccessObject(){this->constantes = new Constantes();}
                     ~DataAccessObject(){delete this->constantes; this->constantes = nullptr;}
                     void insert_data_into_table(DatasCapteur * data, const char * path_data_base);
                     void insert_datas_into_table(std::vector<DatasCapteur *> datas_capteur, const char * path_data_base);
       };
}

#endif // DTO_H_FILE

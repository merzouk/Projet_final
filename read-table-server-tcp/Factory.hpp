#ifndef FACTORY_H_FILE
#define FACTORY_H_FILE

#include "DatasCapteur.hpp"
#include "DataAccessObject.hpp"
#include "Utils.hpp"
#include "Constantes.hpp"

#include <vector>

#include <fstream>
using namespace Datas;
using namespace DataAccess;

namespace Manage
{

       class Factory
       {
              private:
                     DataAccessObject * dataAccessObject;
                     Utils * utils;
                     Constantes * constantes;

              public:
                     Factory(){ dataAccessObject = new DataAccessObject(); utils = new Utils(); constantes = new Constantes();}
                     ~Factory(){ delete dataAccessObject; dataAccessObject = nullptr; delete utils; utils = nullptr;}
                     vector<DatasCapteur *> load_all_datas();
                     vector<DatasCapteur *> load_data_by_id(int id);
                     vector<DatasCapteur *> load_data_by_capteur_name(string capteur_id);
                     vector<DatasCapteur *> load_data_by_date(int day, int month, int year);
                     vector<DatasCapteur *> load_data_by_hour(int minute, int hour);
                     vector<std::string> convert_object_to_json_string(vector<DatasCapteur *> vect_datas);
       };
}
#endif // FACTORY_H_FILE

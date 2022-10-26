#ifndef CONSOLE_H_FILE
#define CONSOLE_H_FILE

#include "DatasCapteur.hpp"
#include "Display.hpp"
#include "Utils.hpp"
#include "Constantes.hpp"
#include "BoostTools.hpp"
#include "JsonTools.hpp"

#include <vector>

using namespace Datas;

namespace Manage
{

       class Console
       {
              private:
                     Display * display;
                     Utils * utils;
                     Constantes * constantes;
                     JsonTools * jsonTools;
                     int port;
                     string ip_address;
                     BoostTools *boostTools;

              public:
                     Console(int port, string ip_address)
                            :port(port), ip_address(ip_address)
                            {
                                   display = new Display();
                                   utils = new Utils();
                                   constantes = new Constantes();
                                   boostTools = new BoostTools();
                                   jsonTools = new JsonTools();
                            }
                     ~Console()
                            {
                                   delete display;
                                   display = nullptr;
                                   delete utils;
                                   utils = nullptr;
                                   delete boostTools;
                                   boostTools = nullptr;
                                   delete constantes;
                                   constantes = nullptr;
                                   delete jsonTools;
                                   jsonTools = nullptr;
                             }
                     void load_all_datas();
                     void load_data_by_id();
                     void load_data_by_capteur_name();
                     void load_data_by_date();
                     void load_data_by_hour();
                     void load_data_by_day_month();
                     void read_datas_convert_to_object(std::string path_to_file);
                     vector<DatasCapteur *> convert_list_json_object (vector<string> json_string);
                     vector<string> split (string s, string delimiter);
       };
}
#endif // CONSOLE_H_FILE

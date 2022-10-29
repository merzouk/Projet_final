#ifndef DISPLAY_H_FILE
#define DISPLAY_H_FILE

#include "DatasCapteur.hpp"
#include <vector>

using namespace Datas;

namespace Manage
{

       class Display
       {
              public:
                     Display(){}
                     ~Display(){}
                     string build_date(DatasCapteur * data);
                     string build_hour(DatasCapteur * data);
                     void print_list_data(vector<DatasCapteur *> datas);
                     void print_details_capteur(string capteur_details);
       };
}
#endif // DISPLAY_H_FILE

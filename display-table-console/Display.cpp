#include "Display.hpp"
#include "DatasCapteur.hpp"

using namespace Datas;
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include <sstream>
#include <bits/stdc++.h>



namespace Manage
{
       string Display::build_date(DatasCapteur * data)
       {
              string str_date = to_string(data->get_jour())
                                +"/"+
                                to_string(data->get_mois())
                                +"/"+
                                to_string(data->get_annee());
              return str_date;
       }

       string Display::build_hour(DatasCapteur * data)
       {
              string str_hour = to_string(data->get_heure())
                                +":"+
                                to_string(data->get_minute())
                                +":"+
                                to_string(data->get_seconde());
              return str_hour;
       }

       void Display::print_list_data(vector<DatasCapteur *> datas)
       {
                     cout.fill(' ');
                     if(datas.size() == 0)
                     {
                           cout <<endl << "Aucune donnee trouvee pour les criteres choisis " << endl;
                           return;
                     }
                     cout << endl     << endl;
                     cout << setw(7)  << "Id"          <<"|"
                          << setw(20) << "Capteur"     <<"|"
                          << setw(13) << "Temperature" <<"|"
                          << setw(10) << "Humidity"    <<"|"
                          << setw(10) << "Pressure"    <<"|"

                          << setw(10) << "Gyro_X"      <<"|"
                          << setw(10) << "Gyro_Y"      <<"|"
                          << setw(10) << "Gyro_Z"      <<"|"

                          << setw(10) << "Accel_X"     <<"|"
                          << setw(10) << "Accel_Y"     <<"|"
                          << setw(10) << "Accel_Z"     <<"|"

                          << setw(15) << "Date"        <<"|"
                          << setw(10) << "Heure"       <<"|"
                                      << endl;

                 for(DatasCapteur *data : datas)
                 {
                     cout << setw(7)  << data->get_id()            <<"|"
                          << setw(20) << data->get_identite_capt() <<"|"
                          << setw(13) << data->get_temperature()   <<"|"
                          << setw(10) << data->get_humidity()      <<"|"
                          << setw(10) << data->get_pressure()      <<"|"

                          << setw(10) << data->get_gyro_x()        <<"|"
                          << setw(10) << data->get_gyro_y()        <<"|"
                          << setw(10) << data->get_gyro_z()        <<"|"

                          << setw(10) << data->get_accel_x()       <<"|"
                          << setw(10) << data->get_accel_y()       <<"|"
                          << setw(10) << data->get_accel_z()       <<"|"

                          << setw(15) << build_date(data)          <<"|"
                          << setw(10) << build_hour(data)          <<"|"
                                                                   << endl;
                 }
       }


       void Display::print_details_capteur(string capteur_details)
       {

       }
}

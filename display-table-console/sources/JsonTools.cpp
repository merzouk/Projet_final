#include "../header/JsonTools.hpp"

namespace Manage
{
       string build_date(DatasCapteur * data)
       {
                     string str_date = to_string(data->get_jour())
                                       +"/"+
                                       to_string(data->get_mois())
                                       +"/"+
                                       to_string(data->get_annee());
                     return str_date;
       }

       string build_hour(DatasCapteur * data)
       {
                     string str_hour = to_string(data->get_heure())
                                       +":"+
                                       to_string(data->get_minute())
                                       +":"+
                                       to_string(data->get_seconde());
                     return str_hour;
       }

       std::string JsonTools::read_json_file_contains(string path_to_file)
       {
           std::string line;
           std::string datas;
           try
           {
              std::ifstream jsonfile(path_to_file);
              if(!jsonfile)
              {
                      std::cout << "Erreur d'ouverture du fichier : " << path_to_file << std::endl;
                      system("pause");
                      return datas;
              }
              while (std::getline(jsonfile, line))
              {
                 int len = (int)line.size();
                 if(len == 0) continue;
                 datas += line;
              }
           }
           catch(exception& e)
           {
               cout << "Erreur pendant la tentative d'ouverture du fichier json : "
                    << path_to_file << " : "<< e.what() << endl;
               return datas;
           }
           return datas;
       }

       void JsonTools::print_list_data(DatasCapteur * data)
       {
                     cout.fill(' ');
                     if(!data)
                     {
                           cout <<endl << "Aucune donnee trouvee pour les criteres choisis " << endl;
                           return;
                     }
                     cout << endl << endl;
                     cout << setw(7)  << "Id" <<"|"
                          << setw(20) << "Capteur" <<"|"
                          << setw(13) << "Temperature" <<"|"
                          << setw(10) << "Humidity" <<"|"
                          << setw(10) << "Pressure" <<"|"

                          << setw(10) << "Gyro_X" <<"|"
                          << setw(10) << "Gyro_Y" <<"|"
                          << setw(10) << "Gyro_Z" <<"|"

                          << setw(10) << "Accel_X" <<"|"
                          << setw(10) << "Accel_Y" <<"|"
                          << setw(10) << "Accel_Z" <<"|"

                          << setw(15) << "Date" <<"|"
                          << setw(10) << "Heure" <<"|"
                                       << endl;


                     cout << setw(7)  << data->get_id() <<"|"
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

       void JsonTools::print_list_data(vector<DatasCapteur *> datas)
       {
                     cout.fill(' ');
                     if(datas.size() == 0)
                     {
                           cout <<endl << "Aucune donnee trouvee pour les criteres choisis " << endl;
                           return;
                     }
                     cout << endl << endl;
                     cout << setw(7)  << "Id" <<"|"
                          << setw(20) << "Capteur" <<"|"
                          << setw(13) << "Temperature" <<"|"
                          << setw(10) << "Humidity" <<"|"
                          << setw(10) << "Pressure" <<"|"

                          << setw(10) << "Gyro_X" <<"|"
                          << setw(10) << "Gyro_Y" <<"|"
                          << setw(10) << "Gyro_Z" <<"|"

                          << setw(10) << "Accel_X" <<"|"
                          << setw(10) << "Accel_Y" <<"|"
                          << setw(10) << "Accel_Z" <<"|"

                          << setw(15) << "Date" <<"|"
                          << setw(10) << "Heure" <<"|"
                                       << endl;

                  for(DatasCapteur * data : datas)
                  {
                     cout << setw(7)  << data->get_id() <<"|"
                          << setw(20) << data->get_identite_capt() <<"|"
                          << setw(13) << data->get_temperature() <<"|"
                          << setw(10) << data->get_humidity() <<"|"
                          << setw(10) << data->get_pressure() <<"|"

                          << setw(10) << data->get_gyro_x() <<"|"
                          << setw(10) << data->get_gyro_y() <<"|"
                          << setw(10) << data->get_gyro_z() <<"|"

                          << setw(10) << data->get_accel_x() <<"|"
                          << setw(10) << data->get_accel_y() <<"|"
                          << setw(10) << data->get_accel_z() <<"|"

                          << setw(15) << build_date(data)    <<"|"
                          << setw(10) << build_hour(data)    <<"|"
                                                             << endl;
                  }
       }

       void extract_date_infos(DatasCapteur * datasCapteur, string date_str, char delimiter)
       {
             stringstream inputString(date_str);
             string str_annee;
             string str_mois;
             string str_jour;
             getline(inputString, str_annee, delimiter);
             getline(inputString, str_mois, delimiter);
             getline(inputString, str_jour, delimiter);
             int annee = stoi(str_annee);
             datasCapteur->set_annee(annee);
             int mois = stoi(str_mois);
             datasCapteur->set_mois(mois);
             int jour = stoi(str_jour);
             datasCapteur->set_jour(jour);
       }

       void extract_hour_infos(DatasCapteur * datasCapteur, string hour_str, char delimiter)
       {

             stringstream inputString(hour_str);

             string str_hour;
             string str_minute;
             string str_seconde;
             getline(inputString, str_hour, delimiter);
             getline(inputString, str_minute, delimiter);
             getline(inputString, str_seconde, delimiter);

             int hour = stoi(str_hour);
             datasCapteur->set_heure(hour);
             int minute = stoi(str_minute);
             datasCapteur->set_minute(minute);
             int seconde = stoi(str_seconde);
             datasCapteur->set_seconde(seconde);
       }

       string extract_str_date(string str_date)
       {
              string d = "";
              for(int i = 0 ; i < 11 ; i++) d = d + str_date[i];
              return d;

       }

       string extract_str_hour(string str_date)
       {
              string h = "";
              for(int i = 11 ; i < int (str_date.size()) ; i++) h = h + str_date[i];
              return h;

       }

       void convert_time_and_extract_infos(DatasCapteur * datasCapteur, string str_date)
       {
          string date_str = extract_str_date(str_date);
          extract_date_infos(datasCapteur, date_str, '/');
          string hour_str = extract_str_hour(str_date);
          extract_hour_infos(datasCapteur, hour_str, ':');
       }

       DatasCapteur * JsonTools::build_object_from_json(string json_string)
       {
           RSJresource  resource (json_string); // RSJ parser (delayed parser)

           DatasCapteur * datasCapteur = new DatasCapteur();

           string id_capteur = resource["capteur"]["sensor_id"].as<std::string>("unknown_id_capteur");
           if(id_capteur == "unknown_id_capteur")
           {
                   datasCapteur->set_id(-1);
                   datasCapteur->set_identite_capt("unknown_id_capteur");
                   return datasCapteur;
           }

           datasCapteur->set_id(resource["capteur"]["id"].as<int>(0));
           datasCapteur->set_identite_capt(id_capteur);
           datasCapteur->set_temperature(resource["capteur"]["temperature"].as<double>(0));
           datasCapteur->set_humidity(resource["capteur"]["humidity"].as<double>(0));
           datasCapteur->set_pressure(resource["capteur"]["pressure"].as<double>(0));

           datasCapteur->set_gyro_x(resource["capteur"]["gyro_x"].as<double>(0));
           datasCapteur->set_gyro_y(resource["capteur"]["gyro_y"].as<double>(0));
           datasCapteur->set_gyro_z(resource["capteur"]["gyro_z"].as<double>(0));

           datasCapteur->set_accel_x(resource["capteur"]["accel_x"].as<double>(0));
           datasCapteur->set_accel_y(resource["capteur"]["accel_y"].as<double>(0));
           datasCapteur->set_accel_z(resource["capteur"]["accel_z"].as<double>(0));

           string str_date = resource["capteur"]["str_date"].as<std::string>("str_date");
           convert_time_and_extract_infos(datasCapteur, str_date);
           return datasCapteur;
       }
}

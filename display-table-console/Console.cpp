#include "Console.hpp"
#include "JsonTools.hpp"


namespace Manage
{
       void Console::read_datas_convert_to_object(std::string path_to_file)
       {
             std::vector<std::string> vect_string = this->utils->read_file_json(path_to_file);
             vector<DatasCapteur *> vect_datas = this->utils->convert_datas_json_to_object(vect_string);
             this->display->print_list_data(vect_datas);
       }

       void Console::load_all_datas()
       {
             string datas =  this->boostTools->load_datas(this->port, this->ip_address, "{datas:{choix:1}}\n" );
             this->display->print_list_data(convert_list_json_object(split(datas, "#")));
       }

        void Console::load_data_by_id()
        {
             int id;

             do
             {
                    cout << "Veuillez saisir un Id positif : ";
                    cin.clear();
                    cin>>id;
             }while(this->utils->validate_id(id) != 0);
             string datas =  this->boostTools->load_datas(this->port, this->ip_address, "{datas:{choix:2, id:"+to_string(id)+"}}\n" );
            this->display->print_list_data(convert_list_json_object(split(datas, "#")));
        }

        void Console::load_data_by_capteur_name()
        {
             string capteur_id;

             do
             {
                    cout << "Veuillez saisir le nom du capteur : ";
                    cin.ignore();
                    getline(cin, capteur_id);
             }while(this->utils->validate_string(capteur_id) != 0);
             string datas =  this->boostTools->load_datas(this->port, this->ip_address, "{datas:{choix:3, sensor_id:\""+capteur_id+"\"}}\n" );
             this->display->print_list_data(convert_list_json_object(split(datas, "#")));
        }

       void Console::load_data_by_date()
       {
              int day;
              int month;
              int year;

             do
             {
                    cout << "Veuillez saisir la valeur du jour valide : ";
                    cin.clear();
                    cin>>day;
             }while(this->utils->validate_day(day) != 0);

             do
             {
                    cout << "Veuillez saisir la valeur du mois valide : ";
                    cin.clear();
                    cin>>month;
             }while(this->utils->validate_month(month) != 0);
             do
             {
                    cout << "Veuillez saisir la valeur de l'annee valide : ";
                    cin.clear();
                    cin>>year;
             }while(this->utils->validate_year(year) != 0);
             string datas =  this->boostTools->load_datas(this->port, this->ip_address,"{datas:{choix:4, day:"+to_string(day)+", month:"+to_string(month)+", year:"+to_string(year)+"}}\n" );
             this->display->print_list_data(convert_list_json_object(split(datas, "#")));
       }

       void Console::load_data_by_hour()
       {
              int hour;
              int minute;

             do
             {
                    cout << "Veuillez saisir la valeur de l'heure valide : ";
                    cin.clear();
                    cin>>hour;
             }while(this->utils->validate_hour(hour) != 0);

             do
             {
                    cout << "Veuillez saisir la valeur de la minute valide : ";
                    cin.clear();
                    cin>>minute;
             }while(this->utils->validate_minute(minute) != 0);
             string datas =  this->boostTools->load_datas(this->port, this->ip_address,"{datas:{choix:5, minute:"+to_string(minute) +", hour:"+to_string(hour)+"}}\n" );
             this->display->print_list_data(convert_list_json_object(split(datas, "#")));
       }

       vector<DatasCapteur *> Console::convert_list_json_object (vector<string> json_string)
       {
              vector<DatasCapteur *> datas;
              if(json_string.size() == 0) return datas;
              for(string str_json : json_string)
              {
                    DatasCapteur * data = this->jsonTools->build_object_from_json(str_json);
                    if(data->get_identite_capt() == "unknown_id_capteur" || data->get_id() == -1) continue;
                    datas.push_back(data);
              }
              return datas;
       }

       vector<string> Console::split (string s, string delimiter) {
           size_t pos_start = 0, pos_end, delim_len = delimiter.length();
           string token;
           vector<string> res;

           while ((pos_end = s.find (delimiter, pos_start)) != string::npos) {
               token = s.substr (pos_start, pos_end - pos_start);
               pos_start = pos_end + delim_len;
               res.push_back (token);
           }

           res.push_back (s.substr (pos_start));
           return res;
       }

}

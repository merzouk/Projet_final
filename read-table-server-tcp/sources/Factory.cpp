#include "../header/Factory.hpp"
#include "../header/Parser.hpp"

#include <iostream>

#include <string>

namespace Manage
{

       vector<DatasCapteur *> Factory::load_all_datas()
       {
                string sql = manageProperties->get_value_by_key("sql_query");
                const char *sql_query = sql.c_str();
                vector<DatasCapteur *> vect_datas = this->dataAccessObject->load_datas(this->manageProperties->get_value_by_key("url_data_base").c_str(), sql_query);
                return vect_datas;
       }

        vector<DatasCapteur *> Factory::load_data_by_id(int id)
        {
             string query = this->manageProperties->get_value_by_key("sql_by_id");
             this->utils->replace_str(query, "#1", to_string(id));
             //cout <<"query ===> " << query << endl;
             const char *sql_query = query.c_str();
             vector<DatasCapteur *> vect_datas = this->dataAccessObject->load_datas(this->manageProperties->get_value_by_key("url_data_base").c_str(), sql_query);
             return vect_datas;
        }

        vector<DatasCapteur *> Factory::load_data_by_capteur_name(string capteur_id )
        {
             string query = this->manageProperties->get_value_by_key("sql_by_cpt_id");
             this->utils->replace_str(query, "#1", capteur_id);
             //cout <<"query ===> " << query << endl;
             const char *sql_query = query.c_str();
             vector<DatasCapteur *> vect_datas = this->dataAccessObject->load_datas(this->manageProperties->get_value_by_key("url_data_base").c_str(), sql_query);
             return vect_datas;
        }

       vector<DatasCapteur *>  Factory::load_data_by_date(int day, int month, int year)
       {
             string query = this->manageProperties->get_value_by_key("sql_by_day_month_year");
             this->utils->replace_str(query, "#1", to_string(day));
             this->utils->replace_str(query, "#2", to_string(month));
             this->utils->replace_str(query, "#3", to_string(year));

             //cout <<"query ===> " << query << endl;
             const char *sql_query = query.c_str();
             vector<DatasCapteur *> vect_datas = this->dataAccessObject->load_datas(this->manageProperties->get_value_by_key("url_data_base").c_str(), sql_query);
             return vect_datas;
       }

       vector<DatasCapteur *> Factory::load_data_by_hour(int minute, int hour)
       {
             string query = this->manageProperties->get_value_by_key("sql_by_hour_minute");

             this->utils->replace_str(query, "#1", to_string(hour));
             this->utils->replace_str(query, "#2", to_string(minute));

             //cout << "query ===> " << query << endl;
             const char *sql_query = query.c_str();
             vector<DatasCapteur *> vect_datas = this->dataAccessObject->load_datas(this->manageProperties->get_value_by_key("url_data_base").c_str(), sql_query);
             return vect_datas;
       }

       vector<std::string> Factory::convert_object_to_json_string(vector<DatasCapteur *> vect_datas)
       {
              vector<std::string> json_string_vect;
              if(vect_datas.size() == 0)
                     return json_string_vect;
              for(DatasCapteur * data : vect_datas)
              {
                     std::string json_str = data->build_json_from_object();
                     json_string_vect.push_back(json_str);
              }
              return json_string_vect;
       }


       std::string Factory::traitment_loading_datas(int choix, int id,
                string capteur_name, int minute, int hour, int day, int month,
                int year)
       {
               vector<DatasCapteur*> vect_datas;
               vect_datas.clear();
               if(choix == 1)
               {
                       vect_datas = load_all_datas();
               }
               else if (choix == 2)
               {
                       vect_datas = load_data_by_id(id);
               }
               else if(choix == 3)
               {
                       vect_datas = load_data_by_capteur_name(capteur_name);
               }
               else if(choix == 4)
               {
                       vect_datas = load_data_by_date(day, month, year);
               }
               else if(choix == 5)
               {
                       vect_datas = load_data_by_hour(minute, hour);
               }
               std::vector < std::string > json_string_vect =
                               convert_object_to_json_string(vect_datas);

               std::string json_string = "";
               if (json_string_vect.size() == 0)
                       return json_string;
               int i = 0;
               for (std::string str : json_string_vect)
               {
                       if(i == 0)
                       {
                            i++;
                            json_string += str;
                       }
                       else
                       {
                            json_string += "#" + str;
                       }
               }
               return json_string;
       }

       std::string Factory::load_message_response(std::string msg_request)
       {
               RSJresource  resource (msg_request); // RSJ parser (delayed parser)
               int choix = resource["datas"]["choix"].as<int>(0);
               string json_response = "";
               if (choix == 1)
               {
                       json_response = traitment_loading_datas(choix, 0, "", 0, 0, 0, 0, 0);
               }
               else if (choix == 2)
               {
                       int id = resource["datas"]["id"].as<int>(0);
                       json_response = traitment_loading_datas(choix, id, "", 0, 0, 0, 0, 0);
               }
               else if (choix == 3)
               {
                       string id_capteur = resource["datas"]["sensor_id"].as<std::string>("uknows_sensor");
                       json_response = traitment_loading_datas(choix, 0, id_capteur, 0, 0, 0, 0, 0);
               }
               else if (choix == 4)
               {
                       int day   = resource["datas"]["day"].as<int>(0);
                       int month = resource["datas"]["month"].as<int>(0);
                       int year  = resource["datas"]["year"].as<int>(0);
                       json_response = traitment_loading_datas(choix, 0, "", 0, 0, day, month, year);
               }
               else if (choix == 5)
               {
                       int minute    = resource["datas"]["minute"].as<int>(0);
                       int hour      = resource["datas"]["hour"].as<int>(0);
                       json_response = traitment_loading_datas(choix, 0, "", minute, hour, 0, 0, 0);
               }
               return json_response;
    }
}

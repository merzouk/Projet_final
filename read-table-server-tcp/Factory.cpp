#include "Factory.hpp"
#include "Parser.hpp"

namespace Manage
{
       vector<DatasCapteur *> Factory::load_all_datas()
       {
                const char *sql_query = this->constantes->get_query_all();
                vector<DatasCapteur *> vect_datas = this->dataAccessObject->load_datas(this->constantes->get_url_db(), sql_query);
                return vect_datas;
       }

        vector<DatasCapteur *> Factory::load_data_by_id(int id)
        {
             string sql = this->constantes->get_query_by_id() + to_string(id);
             const char *sql_query = sql.c_str();
             vector<DatasCapteur *> vect_datas = this->dataAccessObject->load_datas(this->constantes->get_url_db(), sql_query);
             return vect_datas;
        }

        vector<DatasCapteur *> Factory::load_data_by_capteur_name(string capteur_id)
        {
             string sql =  this->constantes->get_query_by_capt_id() +capteur_id+"'";
             const char *sql_query = sql.c_str();
             vector<DatasCapteur *> vect_datas = this->dataAccessObject->load_datas(this->constantes->get_url_db(), sql_query);
             return vect_datas;
        }

       vector<DatasCapteur *>  Factory::load_data_by_date(int day, int month, int year)
       {
             string sql = this->constantes->get_query_by_day() + to_string(day)+" and mois = "+to_string(month)+ " and annee = "+to_string(year);
             const char *sql_query = sql.c_str();
             vector<DatasCapteur *> vect_datas = this->dataAccessObject->load_datas(this->constantes->get_url_db(), sql_query);
             return vect_datas;
       }

       vector<DatasCapteur *> Factory::load_data_by_hour(int minute, int hour)
       {
             string sql = this->constantes->get_query_by_hour() + to_string(hour)+" and minute = "+to_string(minute);
             const char *sql_query = sql.c_str();
             vector<DatasCapteur *> vect_datas = this->dataAccessObject->load_datas(this->constantes->get_url_db(), sql_query);
             return vect_datas;
       }

       vector<std::string> Factory::convert_object_to_json_string(vector<DatasCapteur *> vect_datas)
       {
              vector<std::string> json_string_vect;
              if(vect_datas.size() == 0)
                     return json_string_vect;
              for(DatasCapteur * data : vect_datas)
              {
                     string json_str = "{capteur:{ id: "+to_string(data->get_id()) +", ";
                     json_str += "str_date: '"+ to_string(data->get_jour())+"/"+ to_string(data->get_mois())+"/"+ to_string(data->get_annee())+" ";
                     json_str += to_string(data->get_heure())+":"+ to_string(data->get_minute())+":"+ to_string(data->get_seconde())+"', ";
                     json_str +=" sensor_id: '" +data->get_identite_capt()+ "', ";
                     json_str +=" temperature: " + to_string(data->get_temperature())+ ", ";
                     json_str +=" humidity: " + to_string(data->get_temperature())+ ", ";
                     json_str +=" pressure: " + to_string(data->get_temperature())+ ", ";
                     json_str +=" gyro_x: " + to_string(data->get_temperature())+ ", ";
                     json_str +=" gyro_y: " + to_string(data->get_temperature())+ ", ";
                     json_str +=" gyro_z: " + to_string(data->get_temperature())+ ", ";
                     json_str +=" accel_x: " + to_string(data->get_temperature())+ ", ";
                     json_str +=" accel_y: " + to_string(data->get_temperature())+ ", ";
                     json_str +=" accel_z: " + to_string(data->get_temperature())+ "}}";
                     json_string_vect.push_back(json_str);
              }
              return json_string_vect;
       }


       std::string Factory::traitment_loading_datas(int choix, int id,
                string capteur_name, int minute, int hour, int day, int month,
                int year) {
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
               for (std::string str : json_string_vect)
               {
                       json_string += str + "#";
               }
               return json_string;
       }

       std::string Factory::load_message_response(std::string msg_request)
       {
        RSJresource  resource (msg_request); // RSJ parser (delayed parser)
        int choix = resource["datas"]["choix"].as<int>(0);
        string json_response = "";
        if (choix == 1) {
                json_response = traitment_loading_datas(choix, 0, "", 0, 0, 0, 0, 0);
        } else if (choix == 2) {
                int id = resource["datas"]["id"].as<int>(0);
                json_response = traitment_loading_datas(choix, id, "", 0, 0, 0, 0, 0);
        } else if (choix == 3) {
                string id_capteur = resource["datas"]["sensor_id"].as<std::string>("uknows_sensor");
                json_response = traitment_loading_datas(choix, 0, id_capteur, 0, 0, 0, 0, 0);
        } else if (choix == 4) {
                int day = resource["datas"]["day"].as<int>(0);
                int month = resource["datas"]["month"].as<int>(0);
                int year = resource["datas"]["year"].as<int>(0);
                json_response = traitment_loading_datas(choix, 0, "", 0, 0, day, month, year);
        } else if (choix == 5) {
                int minute = resource["datas"]["minute"].as<int>(0);
                int hour   = resource["datas"]["hour"].as<int>(0);
                json_response = traitment_loading_datas(choix, 0, "", minute, hour, 0, 0, 0);
        }
        return json_response;
    }
}

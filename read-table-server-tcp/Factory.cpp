#include "Factory.hpp"
#include "Parser.hpp"

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

#include <iostream>

#include <string>

using namespace rapidjson;

namespace Manage
{
       std::string get_date(DatasCapteur * data)
       {
              return std::to_string(data->get_jour())+"/" +std::to_string(data->get_mois())+"/" +std::to_string(data->get_annee())+" "+std::to_string(data->get_heure())+":"+std::to_string(data->get_minute())+":"+std::to_string(data->get_seconde());
       }

       std::string build_json(DatasCapteur * data)
       {
              std::string str = "{ \"sensor_id\": \""
                                +data->get_identite_capt()
                                +"\", \"id\": 0, \"str_date\": \""
                                +get_date(data)
                                +"\", \"temperature\": 0,  \"humidity\": 0,  \"pressure\": 0,  \"gyro_x\": 0,  \"gyro_y\": 0, \"gyro_z\": 0,  \"accel_x\": 0, \"accel_y\": 0,  \"accel_z\": 0}";
              return str;
       }

       std::string build_json_from_object(DatasCapteur * data)
       {
         std::string str1 =  build_json(data); ;
         const char * json = str1.c_str();
         Document d;
         d.Parse(json);

         Value& id = d["id"];
         id.SetInt(data->get_id());

         Value& temperature= d["temperature"];
         temperature.SetDouble(data->get_temperature());
         Value& humidity= d["humidity"];
         humidity.SetDouble(data->get_humidity());
         Value& pressure= d["pressure"];
         pressure.SetDouble(data->get_pressure());

         Value& gyro_x= d["gyro_x"];
         gyro_x.SetDouble(data->get_gyro_x());
         Value& gyro_y= d["gyro_y"];
         gyro_y.SetDouble(data->get_gyro_y());
         Value& gyro_z= d["gyro_z"];
         gyro_z.SetDouble(data->get_gyro_z());

         Value& accel_x= d["accel_x"];
         accel_x.SetDouble(data->get_accel_x());
         Value& accel_y= d["accel_y"];
         accel_y.SetDouble(data->get_accel_y());
         Value& accel_z= d["accel_z"];
         accel_z.SetDouble(data->get_accel_z());

          // 3. Stringify the DOM
           StringBuffer buffer;
           Writer<StringBuffer> writer(buffer);
           d.Accept(writer);

           // Output {datas:{"project":"Mon Projet","stars":11}}
           std::string str = buffer.GetString();

            str = "{capteur:"+str+"}";

            return str;
       }

       vector<DatasCapteur *> Factory::load_all_datas()
       {
                string sql = manageProperties->get_value_by_key("sql_query");
                const char *sql_query = sql.c_str();
                vector<DatasCapteur *> vect_datas = this->dataAccessObject->load_datas(this->manageProperties->get_value_by_key("url_data_base").c_str(), sql_query);
                return vect_datas;
       }

        vector<DatasCapteur *> Factory::load_data_by_id(int id)
        {
             string sql = this->manageProperties->get_value_by_key("sql_by_id") +to_string(id);
             const char *sql_query = sql.c_str();
             vector<DatasCapteur *> vect_datas = this->dataAccessObject->load_datas(this->manageProperties->get_value_by_key("url_data_base").c_str(), sql_query);
             return vect_datas;
        }

        vector<DatasCapteur *> Factory::load_data_by_capteur_name(string capteur_id )
        {
             string sql = this->manageProperties->get_value_by_key("sql_by_cpt_id") +capteur_id+"'";
             const char *sql_query = sql.c_str();
             vector<DatasCapteur *> vect_datas = this->dataAccessObject->load_datas(this->manageProperties->get_value_by_key("url_data_base").c_str(), sql_query);
             return vect_datas;
        }

       vector<DatasCapteur *>  Factory::load_data_by_date(int day, int month, int year)
       {
             string sql = this->manageProperties->get_value_by_key("sql_by_day") + to_string(day)+" and mois = "+to_string(month)+ " and annee = "+to_string(year);
             //cout <<"sql ===> " << sql << endl;
             const char *sql_query = sql.c_str();
             vector<DatasCapteur *> vect_datas = this->dataAccessObject->load_datas(this->manageProperties->get_value_by_key("url_data_base").c_str(), sql_query);
             return vect_datas;
       }

       vector<DatasCapteur *> Factory::load_data_by_hour(int minute, int hour)
       {
             string sql = this->manageProperties->get_value_by_key("sql_by_hour") + to_string(hour)+" and minute = "+to_string(minute);
             //cout << "sql => " << sql << endl;
             const char *sql_query = sql.c_str();
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
                     /*
                     string json_str = "{capteur:{ id: "+to_string(data->get_id()) +", ";
                     json_str += "str_date: '"+ to_string(data->get_jour())+"/"+ to_string(data->get_mois())+"/"+ to_string(data->get_annee())+" ";
                     json_str += to_string(data->get_heure())+":"+ to_string(data->get_minute())+":"+ to_string(data->get_seconde())+"', ";
                     json_str +=" sensor_id: '" +data->get_identite_capt()+ "', ";
                     json_str +=" temperature: " + to_string(data->get_temperature())+ ", ";
                     json_str +=" humidity: " + to_string(data->get_humidity())+ ", ";
                     json_str +=" pressure: " + to_string(data->get_pressure())+ ", ";
                     json_str +=" gyro_x: " + to_string(data->get_gyro_x())+ ", ";
                     json_str +=" gyro_y: " + to_string(data->get_gyro_y())+ ", ";
                     json_str +=" gyro_z: " + to_string(data->get_gyro_z())+ ", ";
                     json_str +=" accel_x: " + to_string(data->get_accel_x())+ ", ";
                     json_str +=" accel_y: " + to_string(data->get_accel_y())+ ", ";
                     json_str +=" accel_z: " + to_string(data->get_accel_z())+ "}}";
                     json_string_vect.push_back(json_str);
                     */
                     std::string json_str = build_json_from_object(data);
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
               if (choix == 1) {
                       json_response = traitment_loading_datas(choix, 0, "", 0, 0, 0, 0, 0);
               } else if (choix == 2) {
                       int id = resource["datas"]["id"].as<int>(0);
                       json_response = traitment_loading_datas(choix, id, "", 0, 0, 0, 0, 0);
               } else if (choix == 3) {
                       string id_capteur = resource["datas"]["sensor_id"].as<std::string>("uknows_sensor");
                       json_response = traitment_loading_datas(choix, 0, id_capteur, 0, 0, 0, 0, 0);
               } else if (choix == 4) {
                       int day   = resource["datas"]["day"].as<int>(0);
                       int month = resource["datas"]["month"].as<int>(0);
                       int year  = resource["datas"]["year"].as<int>(0);
                       json_response = traitment_loading_datas(choix, 0, "", 0, 0, day, month, year);
               } else if (choix == 5) {
                       int minute    = resource["datas"]["minute"].as<int>(0);
                       int hour      = resource["datas"]["hour"].as<int>(0);
                       json_response = traitment_loading_datas(choix, 0, "", minute, hour, 0, 0, 0);
               }
               return json_response;
    }
}

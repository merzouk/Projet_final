#include "Factory.hpp"


namespace Manage
{
       vector<DatasCapteur *> Factory::load_all_datas()
       {
                cout << "Load all data " << endl;
                const char *sql_query = this->constantes->get_query_all();
                vector<DatasCapteur *> vect_datas = this->dataAccessObject->load_datas(this->constantes->get_url_db(), sql_query);
                return vect_datas;
       }

        vector<DatasCapteur *> Factory::load_data_by_id(int id)
        {
             cout << "id = " << id <<endl;
             string sql = this->constantes->get_query_by_id() + to_string(id);
             const char *sql_query = sql.c_str();
             vector<DatasCapteur *> vect_datas = this->dataAccessObject->load_datas(this->constantes->get_url_db(), sql_query);
             return vect_datas;
        }

        vector<DatasCapteur *> Factory::load_data_by_capteur_name(string capteur_id)
        {
             cout << "capteur_id = " << capteur_id << endl;
             string sql =  this->constantes->get_query_by_capt_id() +capteur_id+"'";
             const char *sql_query = sql.c_str();
             vector<DatasCapteur *> vect_datas = this->dataAccessObject->load_datas(this->constantes->get_url_db(), sql_query);
             return vect_datas;
        }

       vector<DatasCapteur *>  Factory::load_data_by_date(int day, int month, int year)
       {
             cout << "day = " << day << "month = "<< month << "year = " << year <<endl;
             string sql = this->constantes->get_query_by_day() + to_string(day)+" and mois = "+to_string(month)+ " and annee = "+to_string(year);
             const char *sql_query = sql.c_str();
             vector<DatasCapteur *> vect_datas = this->dataAccessObject->load_datas(this->constantes->get_url_db(), sql_query);
             return vect_datas;
       }

       vector<DatasCapteur *> Factory::load_data_by_hour(int minute, int hour)
       {
             cout << "minute = " << minute << "hour = "<< hour  <<endl;
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
}

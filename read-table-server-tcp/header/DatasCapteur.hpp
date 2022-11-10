#ifndef DATAS_CAPTEUR_H_FILE
#define DATAS_CAPTEUR_H_FILE

#include <string.h>
#include <iostream>

#include "../rapidjson/document.h"
#include "../rapidjson/writer.h"
#include "../rapidjson/stringbuffer.h"


#include <string>

using namespace rapidjson;

using namespace std;
#include <string>

namespace Datas
{
       class DatasCapteur
       {
         private:
                int id; // id en base de donnees

                string identite_capt; // identite unique du capteur

                float temperature; // valeur de la temperature
                float humidity; // valeur de l'humidite
                float pressure; // valeur de la pression

                float gyro_x; // position x en coordonnees 3D de la position du capteur
                float gyro_y; // position y en coordonnees 3D de la position du capteur
                float gyro_z; // position z en coordonnees 3D de la position du capteur

                float accel_x; // triple axis-boussole magnetometre en x
                float accel_y; // triple axis-boussole magnetometre en y
                float accel_z; // triple axis-boussole magnetometre en z

                int seconde; // la seconde de l'acquisition des donnees
                int minute; // la minute de l'acquisition des donnees
                int heure; // heure de l'acquisition des donnees
                int jour; // jour de l'acquisition des donnees
                int mois; // mois de l'acquisition des donnees
                int annee; // annee de l'acquisition des donnees

         public:
              DatasCapteur(int id, string identite_capt, float temperature, float humidity, float pressure,
                          float gyro_x, float gyro_y, float gyro_z, float accel_x, float accel_y, float accel_z,
                          int seconde, int minute, int heure, int jour, int mois, int annee)
                     :id(id), identite_capt(identite_capt),
                     temperature(temperature), humidity(humidity),
                     pressure(pressure),
                     gyro_x(gyro_x), gyro_y(gyro_y), gyro_z(gyro_z),
                     accel_x(accel_x), accel_y(accel_y), accel_z(accel_z),
                     seconde(seconde), minute(minute),
                     heure(heure), jour(jour), mois(mois), annee(annee)
                     {
                     }
              DatasCapteur(){}
              ~DatasCapteur(){}

                int get_id(){ return this->id;}
                string get_identite_capt(){ return this->identite_capt;}

                float get_temperature(){ return this->temperature;}
                float get_humidity(){ return this->humidity;}
                float get_pressure(){ return this->pressure;}

                float get_gyro_x(){ return this->gyro_x;}
                float get_gyro_y(){ return this->gyro_y;}
                float get_gyro_z(){ return this->gyro_z;}

                float get_accel_x(){ return this->accel_x;}
                float get_accel_y(){ return this->accel_y;}
                float get_accel_z(){ return this->accel_z;}

                int get_seconde(){ return this->seconde;}
                int get_minute(){ return this->minute;}
                int get_heure(){ return this->heure;}
                int get_jour(){ return this->jour;}
                int get_mois(){ return this->mois;}
                int get_annee(){ return this->annee;}

                void set_id(int id){ this->id = id ; }
                void set_identite_capt(string identite_capt){  this->identite_capt = identite_capt ; }

                void set_temperature(float temperature){  this->temperature = temperature ; }
                void set_humidity(float humidity){  this->humidity = humidity; }
                void set_pressure(float pressure){  this->pressure = pressure ; }

                void set_gyro_x(float gyro_x){  this->gyro_x =  gyro_x; }
                void set_gyro_y(float gyro_y){  this->gyro_y =  gyro_y; }
                void set_gyro_z(float gyro_z){  this->gyro_z =  gyro_z; }

                void set_accel_x(float accel_x){  this->accel_x =  accel_x; }
                void set_accel_y(float accel_y){  this->accel_y =  accel_y; }
                void set_accel_z(float accel_z){  this->accel_z =  accel_z; }

                void set_seconde(int seconde){  this->seconde = seconde ; }
                void set_minute(int minute){  this->minute = minute ; }
                void set_heure(int heure){  this->heure =  heure; }
                void set_jour(int jour){  this->jour = jour ; }
                void set_mois(int mois){  this->mois = mois ; }
                void set_annee(int annee){  this->annee = annee ; }

                std::string get_date()
                {
                     return std::to_string(this->get_jour())
                                 +"/" +std::to_string(this->get_mois())
                                 +"/" +std::to_string(this->get_annee())
                                 +" " +std::to_string(this->get_heure())
                                 +":" +std::to_string(this->get_minute())
                                 +":" +std::to_string(this->get_seconde());
               }

               std::string build_json()
               {
                     std::string str = "{ \"sensor_id\": \""
                                       +this->get_identite_capt()
                                       +"\", \"id\": 0, \"str_date\": \""
                                       +this->get_date()
                                       +"\", \"temperature\": 0,  \"humidity\": 0,  "
                                       +"\"pressure\": 0,  \"gyro_x\": 0,  \"gyro_y\": 0, "
                                       +"\"gyro_z\": 0,  \"accel_x\": 0, \"accel_y\": 0,  \"accel_z\": 0}";
                     return str;
               }
               /**
                 * Convertit les donnees de l'objet au format JSON
                 *
                 */
               std::string build_json_from_object()
               {
                std::string str1 =  this->build_json(); ;
                const char * json = str1.c_str();
                Document d;
                d.Parse(json);

                Value& id = d["id"];
                id.SetInt(this->get_id());

                Value& temperature = d["temperature"];
                temperature.SetDouble(this->get_temperature());
                Value& humidity = d["humidity"];
                humidity.SetDouble(this->get_humidity());
                Value& pressure = d["pressure"];
                pressure.SetDouble(this->get_pressure());

                Value& gyro_x = d["gyro_x"];
                gyro_x.SetDouble(this->get_gyro_x());
                Value& gyro_y = d["gyro_y"];
                gyro_y.SetDouble(this->get_gyro_y());
                Value& gyro_z = d["gyro_z"];
                gyro_z.SetDouble(this->get_gyro_z());

                Value& accel_x = d["accel_x"];
                accel_x.SetDouble(this->get_accel_x());
                Value& accel_y = d["accel_y"];
                accel_y.SetDouble(this->get_accel_y());
                Value& accel_z = d["accel_z"];
                accel_z.SetDouble(this->get_accel_z());

                // 3. Stringify the DOM
                StringBuffer buffer;
                Writer<StringBuffer> writer(buffer);
                d.Accept(writer);

                std::string str = buffer.GetString();

                str = "{capteur:"+str+"}";

                return str;
              }
       };
}


#endif // DATAS_CAPTEUR_H_FILE

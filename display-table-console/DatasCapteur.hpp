#ifndef DATAS_CAPTEUR_H_FILE
#define DATAS_CAPTEUR_H_FILE

#include <string.h>
#include <iostream>

using namespace std;
#include <string>

namespace Datas
{
       class DatasCapteur
       {
         private:
                int id; // id en base de donnees
                string identite_capt; // identite unique du capteur qui procede a l'acquisition des donnees
                float temperature; // valeur de la temperature
                float humidity; // valeur de l'humidite
                float pressure; // valeur de la pression
                float gyro_x; // position x en coordonnees 3D de la position de l'acquisition des donnees
                float gyro_y; // position y en coordonnees 3D de la position de l'acquisition des donnees
                float gyro_z; // position z en coordonnees 3D de la position de l'acquisition des donnees
                float accel_x;
                float accel_y;
                float accel_z;
                int seconde;
                int minute; // la minute de l'acquisition des donnees
                int heure; // heure de l'acquisition des donnees
                int jour; // jour de l'acquisition des donnees
                int mois; // mois de l'acquisition des donnees
                int annee; //annee de l'acquisition des donnees

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
       };
}


#endif // DATAS_CAPTEUR_H_FILE

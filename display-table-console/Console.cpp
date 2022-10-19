#include "Console.hpp"


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

                 //ajouter appel boost choix = 1
                 //quand le retour est ok, on parse et affiche le fichier retourne datas.json
              string datas =  this->boostTools->load_datas(this->port, this->ip_address, "{datas:{choix:1}}\n" );
              cout << datas << endl;
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
            //ajouter appel boost choix = 2, id = ?
            //quand le retour est ok, on parse et affiche le fichier retourne datas.json
             string datas =  this->boostTools->load_datas(this->port, this->ip_address, "{datas:{choix:2, id:"+to_string(id)+"}}\n" );
             cout << datas << endl;

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
             //ajouter appel boost choix = 3, capteur_id = ""
             //quand le retour est ok, on parse et affiche le fichier retourne datas.json
             string datas =  this->boostTools->load_datas(this->port, this->ip_address, "{datas:{choix:3, sensor_id:\""+capteur_id+"\"}}\n" );
             cout << datas << endl;

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
            //ajouter appel boost choix = 4, day = ? month = ? year = ?
            //quand le retour est ok, on parse et affiche le fichier retourne datas.json
           string datas =  this->boostTools->load_datas(this->port, this->ip_address,"{datas:{choix:4, day:"+to_string(day)+", month:"+to_string(month)+", year:"+to_string(year)+"}}\n" );
             cout << datas << endl;
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
             //ajouter appel boost choix = 5, hour = ? minute = ?
             //quand le retour est ok, on parse et affiche le fichier retourne datas.json
             string datas =  this->boostTools->load_datas(this->port, this->ip_address,"{datas:{choix:5, minute:"+to_string(minute) +", hour:"+to_string(hour)+"}}\n" );
             cout << datas << endl;
       }

}

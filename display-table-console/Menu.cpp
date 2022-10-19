#include "Menu.hpp"

namespace Manage
{
       int Menu::check_input_value(int limit_inf, int limit_max)
       {
              int opc;
              bool aux = true;
              cin.exceptions(std::istream::failbit);
              do {
                     try
                     {
                            cout << "Veuillez saisir un entier compris entre " << limit_inf
                                          << " et " << limit_max << endl;
                            cin >> opc;
                            aux = true;
                     }
                     catch (std::ios_base::failure &fail)
                     {
                            aux = false;
                            cout << "Veuillez saisir une option valide." << endl;
                            cin.clear();
                            std::string tmp;
                            getline(cin, tmp);
                     }
              } while (aux == false || (limit_inf < opc && opc > limit_max));
              return opc;
       }

       void Menu::launch_programm_manage_temperature()
       {
              int menu = -1;
              do {
                     menu = -1;
                     cout << endl << " ----------------------- MENU -----------------------"
                                   << endl << endl;
                     cout << "1.  Charger toutes les donnees" << endl;
                     cout << "2.  Chercher Donnees par id" << endl;
                     cout << "3.  Chercher Donnees par nom du capteur" << endl;
                     cout << "4.  Chercher Donnees par date" << endl;
                     cout << "5.  Chercher Donnees par heure" << endl;
                     cout << "0.  Quitter" << endl;
                     cout << endl << "Votre choix : " << endl;

                     menu = check_input_value(1, 5);
                     cout << endl;

                     switch (menu)
                     {
                            case 0:
                                   break;
                            case 1:
                                   console->load_all_datas();
                                   break;
                            case 2:
                                   console->load_data_by_id();
                                   break;
                            case 3:
                                   console->load_data_by_capteur_name();
                                   break;
                            case 4:
                                   console->load_data_by_date();
                                   break;
                            case 5:
                                   console->load_data_by_hour();
                                   break;
                     }
              } while (menu != 0);
       }
}

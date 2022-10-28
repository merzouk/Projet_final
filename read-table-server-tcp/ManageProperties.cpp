#include "ManageProperties.hpp"

namespace Manage
{
       string ManageProperties::get_value_by_key(string key)
       {
              int len = int(key.length());
              if (len == 0)
              {
                     cout << "La cle : " << key << "n'est pas valide " << endl;
                     return " ";
              }
              map<string, string>::iterator it = this->map_properties.begin();
              for (; it != this->map_properties.end(); it++)
              {
                     if (key == it->first)
                            return it->second;
              }
              cout << "La cle " << key << " non trouve " << endl;
              return " ";
       }

       string ManageProperties::check_elt_by_key(string key)
       {
              int len = int(key.length());
              if (len == 0)
              {
                     cout << "La cle : " << key << "n'est pas valide " << endl;
                     return " ";
              }
              map<string, string>::iterator it = this->map_properties.begin();
              for (; it != this->map_properties.end(); it++)
              {
                     if (key == it->first)
                            return it->second;
              }
              return " ";
       }

       void ManageProperties::display_map_properties()
       {
              if (this->map_properties.size() == 0)
              {
                     return;
              }
              for (auto itr = this->map_properties.begin(); itr != this->map_properties.end(); ++itr)
              {
                     cout << endl << "key : " << itr->first << endl << "Value : "
                                   << itr->second << endl;
              }
       }

       void ManageProperties::delete_value_by_key(string key)
       {
              if (check_elt_by_key(key) != " ")
              {
                     this->map_properties.erase(key);
              }
              else
              {
                     cout << "Cle : " << key << endl;
                     cout << endl
                          << "Suppression impossible, la cle n'existe pas dans map_properties";
              }
       }

       void ManageProperties::add_new_elt(string key, string value)
       {
              if (key.length() == 0)
              {
                     cout << endl << "Ajout impossible, la cle n'est n'est pas renseignee : "
                                   << key << endl;
                     return;
              }
              if (value.length() == 0)
              {
                     cout << endl
                                   << "Ajout impossible, la valeur n'est n'est pas renseignee : "
                                   << value << endl;
                     return;
              }

              if (check_elt_by_key(key) == " ")
              {
                     this->map_properties[key] = value;
              }
              else
              {
                     cout << "Cle " << key << endl;
                     cout << "Ajout impossible, la cle existe dans map_properties " << key
                                   << endl;
              }
       }

       void ManageProperties::tokenize(std::string const &key_value, const char delimiter)
       {
              size_t start;
              size_t end = 0;
              int i = 0;
              string key = "";
              string value = "";
              while ((start = key_value.find_first_not_of(delimiter, end)) != std::string::npos)
              {
                     end = key_value.find(delimiter, start);
                     if (i == 0)
                     {
                            key = key_value.substr(start, end - start);
                            i++;
                     }
                     else
                     {
                            value = key_value.substr(start, end - start);
                     }
              }
              add_new_elt(key, value);
       }

       void ManageProperties::read_contains_properties_file(std::string file_name, const char delimiter)
       {
              try
              {
                     std::ifstream properties(file_name);
                     if (properties.is_open())
                     {
                            std::string line;
                            while (std::getline(properties, line))
                            {
                                   tokenize(line, delimiter);
                            }
                            properties.close();
                     }
                     else
                     {
                            cout << "erreur pendant la tentative d'ouverture du fichier : "
                                          << file_name << endl;
                     }
              }
              catch(exception &ex)
              {
                   log(LOG_ERR) << "Erreur durant l'ouverture du fichier :  "+file_name+"  : "+ std::string(ex.what()) + "\n";
              }
       }
}

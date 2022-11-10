#include "JsonTools.hpp"
#include "ManageProperties.hpp"

#include <exception>

#include <chrono> //milliseconds
#include <thread> //sleep_for
#include <string>


using namespace Manage;


int main(int argc, char *argv[])
{
    if(argc == 3)
    {
              try
              {
                     string path_to_json_file = argv[1];
                     string properties_file = argv[2];
                     if(properties_file.size() == 0)
                     {
                            Logger::log(2, "Le fichier ressources \"" +properties_file +"\" n'est pas renseigne, parametres manquants, connexion impossible");
                            return 1;
                     }
                     ManageProperties * manageProperties = new ManageProperties();
                     manageProperties->read_contains_properties_file(properties_file, ':');
                     if(manageProperties->size_map() == 0)
                     {
                            Logger::log(2,"Aucun parametre trouve dans le fichier ressources, connexion impossible");
                            return 1;
                     }
                     string path_db =  manageProperties->get_value_by_key("url_data_base");
                     const char * path_data_base = path_db.c_str();

                     JsonTools * jsonTools = new JsonTools(manageProperties);
                     int res = jsonTools->build_Object_from_json_save(path_to_json_file, path_data_base);
                     delete jsonTools;
                     jsonTools = nullptr;
                     delete manageProperties;
                     manageProperties = nullptr;
                     Logger::log(1, "Insertion en base de donnees s'est achevee avec succes") ;
              }
              catch(exception & ex)
              {
                   Logger::log(2, "Erreur pendant l'insertion en base de donnees ");
                   Logger::log(2, ex.what());
                   return 1;
              }
    }
    else
    {
              Logger::log(2, "Le fichier source au format json n'est pas renseigne") ;
              return 1;
    }
    return 0;
}


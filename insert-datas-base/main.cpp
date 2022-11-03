#include "JsonTools.hpp"
#include "ManageProperties.hpp"


#include "Logger.hpp"
#include <exception>

#include <chrono> //milliseconds
#include <thread> //sleep_for
#include <string>


using namespace Manage;
using namespace ManageLog;

int main(int argc, char *argv[])
{
    // Initiate logger (default name is 'log')
    LOG_INIT_CERR();
    if(argc == 3)
    {
              try
              {
                     string path_to_json_file = argv[1];
                     string properties_file = argv[2];
                     if(properties_file.size() == 0)
                     {
                            log(LOG_ERR) << "Le fichier ressources n'est pas renseigne, parametres manquants, connexion impossible :\n";
                            return 1;
                     }
                     ManageProperties * manageProperties = new ManageProperties();
                     manageProperties->read_contains_properties_file(properties_file, ':');
                     if(manageProperties->size_map() == 0)
                     {
                            log(LOG_ERR) << "Aucun parametre trouve dans le fichier ressources, connexion impossible : \n";
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
                     log(LOG_INFO) << "Insertion en base de donnees s'est achevee avec succes\n" ;
              }
              catch(exception & ex)
              {
                   log(LOG_ERR) << "Erreur pendant l'insertion en base de donnees " << std::string(ex.what())  << "\n";
                   return 1;
              }
    }
    else
    {
              log(LOG_ERR) << "Le fichier source au format json n'est pas renseigne\n" ;
              return 1;
    }
    return 0;
}


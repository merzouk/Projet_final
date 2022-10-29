#include "JsonTools.hpp"
#include "ManageProperties.hpp"


#include "Logger.hpp"

#include <chrono> //milliseconds
#include <thread> //sleep_for
#include <string>


using namespace Manage;

int main(int argc, char *argv[])
{
    // Initiate logger (default name is 'log')
    LOG_INIT_CERR();
    if(argc == 4)
    {
       string path_to_json_file = argv[1];
       const char * path_data_base = argv[2];
       string properties_file = argv[3];
       if(properties_file.size() == 0)
	{
              log(LOG_ERR) << "Le fichier ressources n'est pas renseigne, parametres manquants, connexion impossible : " + std::to_string(port) + "\n";
		return 1;
	}
       ManageProperties * manageProperties = new ManageProperties();
       manageProperties->read_contains_properties_file(properties_file, ':');
	if(manageProperties->size_map() == 0)
	{
              log(LOG_ERR) << "Aucun parametre trouve dans le fichier ressources, connexion impossible : " + std::to_string(port) + "\n";
              return 1;
	}
       JsonTools * jsonTools = new JsonTools(manageProperties);
       int res = jsonTools->build_Object_from_json_save(path_to_json_file, path_data_base);
       delete jsonTools;
       jsonTools = nullptr;
    }
    else
    {
        log(LOG_ERR) << "Le fichier source au format json n'est pas renseigne\n" ;
        return 1;
    }
    return 0;
}


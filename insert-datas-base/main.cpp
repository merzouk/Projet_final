#include "JsonTools.hpp"

using namespace Manage;

int main(int argc, char *argv[])
{
    if(argc == 3)
    {
       JsonTools * jsonTools = new JsonTools();
       string path_to_json_file = argv[1];
       const char * path_data_base = argv[2];
       int res = jsonTools->build_Object_from_json_save(path_to_json_file, path_data_base);
       delete jsonTools;
       jsonTools = nullptr;
    }
    else
    {
       cout << "Le fichier source au format json n'est pas renseigne" << endl;
       return 1;
    }

}


#ifndef JSON_H_FILE
#define JSON_H_FILE

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <sstream>
#include <bits/stdc++.h>
#include "DatasCapteur.hpp"
#include "DataAccessObject.hpp"
#include "ManageProperties.hpp"


using namespace Datas;

using namespace DataAccess;

// RSJP header:
#include "Parser.hpp"


using namespace std;

namespace Manage
{
       class JsonTools
       {
              private:
                     ManageProperties * manageProperties;
              public:
                     JsonTools(ManageProperties * manageProperties):manageProperties(manageProperties){}
                     ~JsonTools(){delete manageProperties; manageProperties = nullptr;}
                     DatasCapteur * build(string str);
                     void print_list_data(DatasCapteur * data);
                     std::string read_json_file_contains(string path_to_file);
                     int build_Object_from_json_save(string path_to_file, const char * path_data_base);
       };
}

#endif // JSON_H_FILE

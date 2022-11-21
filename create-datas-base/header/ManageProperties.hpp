
#ifndef PROPERTIER_H_FILE
#define PROPERTIER_H_FILE

using namespace std;

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include <sstream>
#include <cstring>
#include <bits/stdc++.h>
#include <map>
#include "Logger.hpp"

namespace Manage
{
       class ManageProperties
       {
              private:
                     map<std::string, std::string> map_properties;

              public:
                     ManageProperties(){}
                     ~ManageProperties(){map_properties.clear();}
                     string check_elt_by_key(string key);
                     string get_value_by_key(string key);
                     void display_map_properties();
                     void delete_value_by_key(string key);
                     void add_new_elt(string key, string value);
                     void tokenize(std::string const &key_value, const char delimiter);
                     void read_contains_properties_file(std::string file_name, const char delimiter);
                     int size_map() { return map_properties.size();}
       };
}
#endif // PROPERTIER_H_FILE

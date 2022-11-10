#ifndef UTILS_H_FILE
#define UTILS_H_FILE

#include <stdlib.h>


#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include <sstream>
#include <cstring>
#include <bits/stdc++.h>
#include "JsonTools.hpp"


using namespace std;

namespace Manage
{

      class Utils
      {
              private:
                     JsonTools * jsonTools;

              public:
                     Utils(){jsonTools = new JsonTools();}
                     ~Utils(){delete jsonTools; jsonTools = nullptr;}
                      char* to_char(std::string s, char *ptr);
                      int str_to_int(std::string s);
                      bool validate_id(int id);
                      bool validate_day(int day);
                      bool validate_month(int month);
                      bool validate_year(int year);
                      bool validate_hour(int hour);
                      bool validate_minute(int minute);
                      bool validate_string(string s);
                      std::vector<std::string> read_file_json(string path_file_json);
                      std::vector<DatasCapteur *> convert_datas_json_to_object(std::vector<std::string> vect_string);
      };
}


#endif // UTILS_H_FILE


#ifndef UTILS_H_FILE
#define UTILS_H_FILE

#include <iostream>
#include <stdlib.h>
#include <string>


using namespace std;

namespace Manage
{

      class Utils
      {
              public:
                     Utils(){}
                     ~Utils(){}
                      char* to_char(std::string s, char *ptr);
                      int str_to_int(std::string s);
                      bool validate_id(int id);
                      bool validate_day(int day);
                      bool validate_month(int month);
                      bool validate_year(int year);
                      bool validate_hour(int hour);
                      bool validate_minute(int minute);
                      bool validate_string(string s);
                      bool replace_str(std::string& str, const std::string& from, const std::string& to);
      };
}


#endif // UTILS_H_FILE


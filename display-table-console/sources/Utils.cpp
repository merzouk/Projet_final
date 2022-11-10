using namespace std;
#include <iostream>
#include <stdlib.h>
#include <string>
#include <regex>
#include "../header/Utils.hpp"


using namespace std;

namespace Manage
{

       char* Utils::to_char(std::string s, char *ptr)
	{
		int n = s.length();
		ptr = (char*) malloc((n + 1) * sizeof(char));
		for (int i = 0; i < n; i++)
		{
			*(ptr + i) = s[i];
		}
		*(ptr + n) = '\0';
		return ptr;
	}

	int Utils::str_to_int(std::string s)
	{
		try
		{
			return stoi(s.c_str());
		}
		catch (...)
		{
			std::cout << "Erreur de conversion string vers int " << s << std::endl;
		}
		return -1;
	}


       bool Utils::validate_id(int id)
       {
              if(id > 0) return 0;
              return 1;
       }

       bool Utils::validate_string(string s)
       {
              int n = s.length();
              if(n > 3)
                     return 0;
              return 1;
       }

       bool Utils::validate_day(int day)
       {
              if(day > 0 && day < 32) return 0;
              return 1;
       }
       bool Utils::validate_month(int month)
       {
              if(month > 0 && month < 13) return 0;
              return 1;
       }
       bool Utils::validate_year(int year)
       {
              if(year >= 2022) return 0;
              return 1;
       }

       bool Utils::validate_hour(int hour)
       {
            if(hour >= 0 && hour < 24) return 0;
            return 1;
       }

       bool Utils::validate_minute(int minute)
       {
            if(minute >= 0 && minute < 60) return 0;
            return 1;
       }

       std::vector<std::string> Utils::read_file_json(string path_file_json)
       {
              ifstream inputFile;
              std::vector<std::string> vect_string;
              try
              {
                     inputFile.open(path_file_json);
              }
              catch (const ifstream::failure& e)
              {
                      cout << "Echec lors de la tentative d'ouverture du fichier json " <<  path_file_json <<" : "<< e.what() << endl;
                      return vect_string;
              }
              catch(const exception & ex)
              {
                     cout << "Echec lors de la tentative d'ouverture du fichier json " << path_file_json << " : " << ex.what() << endl;
                     return vect_string;
              }
              catch(...)
              {
                     cout << "Echec lors de la tentative d'ouverture du fichier json " << path_file_json << endl;
                     return vect_string;
              }
              string line = "";
              while (getline(inputFile, line))
              {
                     if (line.size() == 0)
                            continue;
                     vect_string.push_back(line);
              }
              inputFile.close();
              return vect_string;
       }

        std::vector<DatasCapteur *> Utils::convert_datas_json_to_object(std::vector<std::string> vect_string)
        {
               std::vector<DatasCapteur *> vect_datas;
               if(vect_string.size() == 0)
                     return vect_datas;
               for(std::string json_string : vect_string)
               {
                   DatasCapteur * data = this->jsonTools->build_object_from_json(json_string);
                   if(data->get_identite_capt() == "unknown_id_capteur" || data->get_id() == -1) continue;
                   vect_datas.push_back(data);
               }
               return vect_datas;
        }
}

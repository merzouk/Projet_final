#include <iostream>
#include <stdlib.h>
#include <string>
#include <regex>
#include "Utils.hpp"

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
}

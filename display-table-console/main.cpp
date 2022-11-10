#include "Menu.hpp"
#include "Logger.hpp"

#include <chrono> //milliseconds
#include <thread> //sleep_for
#include <string>

#include <regex>




using namespace Manage;

bool validate_ip_address(const std::string& ip_address)
{
   const regex pattern("\\d{1,3}\\.\\d{1,3}\\.\\d{1,3}\\.\\d{1,3}");
   return regex_match(ip_address, pattern);
}

int main(int argc, char ** argv)
{

       if(argc < 3)
       {
             Logger::log(2, "Entree du programme attend trois arguments exec, port et addresse ip du server");
             return 1;
       }

       int port =  0;
       try
       {
              port = atoi(argv[1]);
       }
       catch(std::exception const & ex)
       {
             string p = argv[1];
             Logger::log(2, "Le numero de port est au format entier : " +p);
             Logger::log(2, ex.what());
             Logger::log(2,  "\nconnexion impossible");
             return 1;
       }
	string ip_address = argv[2];

	if(port == 0)
       {
              string p = argv[1];
              Logger::log(2,  "Le numero de port non renseigne, connexion impossible : " + p);
              return 1;
       }
       if(port < 0) port *=-1;

       if(ip_address.size() == 0)
       {
               Logger::log(2, "L'addresse ip du server non renseigne, connexion impossible : " +ip_address );
               return 1;
       }

       if(validate_ip_address(ip_address) == 0)
       {
               Logger::log(2, "Le format de l'addresse ip du server n'est pas correcte, connexion impossible : " + ip_address );
               return 1;
       }

       Menu * menu = new Menu(port, ip_address);
       menu->launch_programm_manage_temperature();

       delete menu;
       menu = nullptr;
       return 0;
}

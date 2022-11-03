#include "Menu.hpp"
#include "Logger.hpp"

#include <chrono> //milliseconds
#include <thread> //sleep_for
#include <string>

#include <regex>




using namespace Manage;
using namespace ManageLog;

bool validate_ip_address(const std::string& ip_address)
{
   const regex pattern("\\d{1,3}\\.\\d{1,3}\\.\\d{1,3}\\.\\d{1,3}");
   return regex_match(ip_address, pattern);
}

int main(int argc, char ** argv)
{
       // Initiate logger (default name is 'log')
       LOG_INIT_CERR();

       if(argc < 3)
       {
             log(LOG_ERR)  << "Entree du programme attend trois arguments exec, port et addresse ip du server\n";
             return 1;
       }

       int port = atoi(argv[1]);
	string ip_address = argv[2];

	if(port == 0)
       {
              log(LOG_ERR)  << "Le numero de port n'est pas renseigne, connexion impossible : " << port  << "\n";
              return 1;
       }
       if(port < 0) port *=-1;

       if(ip_address.size() == 0)
       {
              log(LOG_ERR)  << "L'addresse ip du server non renseigne, connexion impossible : " << ip_address << "\n";
              return 1;
       }

       if(validate_ip_address(ip_address) == 0)
       {
              log(LOG_ERR)  << "Le format de l'addresse ip du server n'est pas correcte, connexion impossible : " << ip_address << "\n";
              return 1;
       }

       Menu * menu = new Menu(port, ip_address);
       menu->launch_programm_manage_temperature();

       delete menu;
       menu = nullptr;
       return 0;
}

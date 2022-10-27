#include "Menu.hpp"
#include <regex>
#include "ManageProperties.hpp"

using namespace Manage;


bool validate_ip_address(const std::string& ip_address)
{
   const regex pattern("\\d{1,3}\\.\\d{1,3}\\.\\d{1,3}\\.\\d{1,3}");
   return regex_match(ip_address, pattern);
}

int main(int argc, char ** argv)
{
       int port = atoi(argv[1]);
	string ip_address = argv[2];
	if(port == 0)
       {
              cout << "Le numero de port n'est pas renseigne, connexion impossible : " << port << endl;
              return 1;
       }
       if(port < 0) port *=-1;

       if(ip_address.size() == 0)
       {
              cout << "L'addresse ip du server non renseigne, connexion impossible : " <<ip_address << endl;
              return 1;
       }
       if(validate_ip_address(ip_address) == 0)
       {
             cout << "Le format de l'addresse ip du server n'est pas correcte, connexion impossible : " << ip_address << endl;
              return 1;
       }
       Menu * menu = new Menu(port, ip_address);
       menu->launch_programm_manage_temperature();

       delete menu;
       menu = nullptr;
       return 0;
}

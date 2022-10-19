#include "Menu.hpp"

using namespace Manage;

int main(int argc, char ** argv)
{
       int port = atoi(argv[1]);
	string ip_address = argv[2]; //"51.68.86.120";
	if(port == 0)
       {

       }
       Menu * menu = new Menu(port, ip_address);
       menu->launch_programm_manage_temperature();
       return 0;
}

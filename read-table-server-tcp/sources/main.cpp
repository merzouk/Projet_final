#include "../header/Factory.hpp"
#include "../header/Parser.hpp"
#include <iostream>
#include <boost/asio.hpp>
#include "../header/ManageProperties.hpp"

using namespace boost::asio;
using ip::tcp;
using std::string;
using std::cout;
using std::endl;

#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include <sstream>
#include <cstring>
#include <bits/stdc++.h>

#include <chrono> //milliseconds
#include <thread> //sleep_for
#include "../header/Logger.hpp"

using namespace Manage;

string read_(tcp::socket &socket)
{
        boost::asio::streambuf buf;
        boost::asio::read_until(socket, buf, "\n");

        string data = boost::asio::buffer_cast<const char*>(buf.data());
        return data;
}

void send_(tcp::socket &socket, const string &message)
{
        const string msg = message + "\n";
        boost::asio::write(socket, boost::asio::buffer(message));
}


int main(int argc, char ** argv)
{
       if(argc < 3)
       {
            Logger::log(2,  "Entree du programme attend trois arguments exec, port et et path vers le fichier de resources");
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
            Logger::log(2,  "Le numero de port est au format entier : " +p);
            Logger::log(2,  ex.what());
            Logger::log(2,  "connexion impossible");
            return 1;
       }

       std::string properties_file = argv[2];

       if(port == 0)
       {
              string p = argv[1];
              Logger::log(2, "Le numero de port \"" +p+"\" n'est pas renseigne, connexion impossible") ;
              return 1;
       }
       if(properties_file.size() == 0)
	{
           Logger::log(2, "Le fichier ressources \"" + properties_file +"\"n'est pas renseigne, parametres manquants, connexion impossible : ") ;
           return 1;
	}
       if(port < 0) port *=-1;
       boost::asio::io_service io_service;

       ManageProperties * manageProperties = new ManageProperties();
       manageProperties->read_contains_properties_file(properties_file, ':');
       if(manageProperties->size_map() == 0)
	{
	     Logger::log(2, "Aucun parametre trouve dans le fichier ressources, connexion impossible");
            return 1;
	}

       Factory *factory = new Factory(manageProperties);
       while (1)
       {
              try
              {
                tcp::acceptor acceptor_(io_service, tcp::endpoint(tcp::v4(), port));

                tcp::socket socket_(io_service);

                acceptor_.accept(socket_);

                string message_request = read_(socket_);
                std::cout << std::endl << std::endl;
                Logger::log(1, "message request : "+ message_request);

                string message_response = factory->load_message_response(message_request);
                std::cout << std::endl << std::endl;
                 Logger::log(1, "message response : \n" + message_response);

                send_(socket_, message_response);
                std::cout << std::endl << std::endl;
                 Logger::log(1,  "Server TCP : sent response to client successfully !");
              }
              catch(exception & ex)
              {
                     Logger::log(2,  "Erreur durant le traitement de la requete : ");
                     Logger::log(2,  ex.what() );
                     Logger::log(2,  "Server TCP : sent response to client faillures ") ;
              }
        }
        delete factory;
        factory = nullptr;

        delete manageProperties;
        manageProperties = nullptr;

        return 0;
}



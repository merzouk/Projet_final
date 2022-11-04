#include "Factory.hpp"
#include "Parser.hpp"
#include <iostream>
#include <boost/asio.hpp>
#include "ManageProperties.hpp"

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

#include "Logger.hpp"

#include <chrono> //milliseconds
#include <thread> //sleep_for

using namespace Manage;
using namespace ManageLog;

string read_(tcp::socket &socket) {
        boost::asio::streambuf buf;
        boost::asio::read_until(socket, buf, "\n");

        string data = boost::asio::buffer_cast<const char*>(buf.data());
        return data;
}

void send_(tcp::socket &socket, const string &message) {
        const string msg = message + "\n";
        boost::asio::write(socket, boost::asio::buffer(message));
}


int main(int argc, char ** argv)
{
       // Initiate logger (default name is 'log')
       LOG_INIT_CERR();

       if(argc < 3)
       {
            log(LOG_ERR)  << "Entree du programme attend trois arguments exec, port et et path vers le fichier de resources\n";
            return 1;
       }

       int port =  0;
       try
       {
              port = atoi(argv[1]);
       }
       catch(std::exception const & ex)
       {
            log(LOG_ERR)  << "Le numero de port est au format entier : " << argv[1] << ex.what() << "\nconnexion impossible\n";
            return 1;
       }

       std::string properties_file = argv[2];

       if(port == 0)
       {
              log(LOG_ERR)  <<  "Le numero de port \"" << argv[1] <<"\" n'est pas renseigne, connexion impossible" << "\n" ;
              return 1;
       }
       if(properties_file.size() == 0)
	{
           log(LOG_ERR)  <<  "Le fichier ressources \"" << properties_file <<"\"n'est pas renseigne, parametres manquants, connexion impossible : "  << "\n" ;
           return 1;
	}
       if(port < 0) port *=-1;
       boost::asio::io_service io_service;

       ManageProperties * manageProperties = new ManageProperties();
       manageProperties->read_contains_properties_file(properties_file, ':');
       if(manageProperties->size_map() == 0)
	{
	     log(LOG_ERR)  <<   "Aucun parametre trouve dans le fichier ressources, connexion impossible\n";
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
                log(LOG_INFO) << "message request : " << message_request << "\n";

                string message_response = factory->load_message_response(message_request);
                std::cout << std::endl << std::endl;
                log(LOG_INFO) << "message response : \n" << message_response << "\n";

                send_(socket_, message_response);
                std::cout << std::endl << std::endl;
                log(LOG_INFO) << "Server TCP : sent response to client successfully !\n";
              }
              catch(exception & ex)
              {
                     log(LOG_ERR)  << "Erreur durant le traitement de la requete : " << ex.what() << "\n";
                     log(LOG_ERR)  << "Server TCP : sent response to client faillures !\n" ;
              }
        }
        delete factory;
        factory = nullptr;

        delete manageProperties;
        manageProperties = nullptr;

        return 0;
}



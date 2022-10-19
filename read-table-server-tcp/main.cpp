#include "Factory.hpp"
#include "Parser.hpp"
#include <iostream>
#include <boost/asio.hpp>

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

using namespace Manage;

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

       int port =  atoi(argv[1]);
       if(port == 0)
       {
              cout << "Le numero de port n'est pas renseigne, connexion impossible : " << port << endl;
              return 1;
       }
       if(port < 0) port *=-1;
       boost::asio::io_service io_service;
       Factory *factory = new Factory();

       while (1)
       {
                tcp::acceptor acceptor_(io_service, tcp::endpoint(tcp::v4(), port));

                tcp::socket socket_(io_service);

                acceptor_.accept(socket_);

                string message_request = read_(socket_);

                cout <<"message request : " << message_request << endl;
                string message_response = factory->load_message_response(message_request);

                cout << "message response : " << endl << message_response << endl;

                send_(socket_, message_response);

                cout << "Server TCP : sent response to client successfully !" << endl;
        }
        delete factory;
        factory = nullptr;
        return 0;
}



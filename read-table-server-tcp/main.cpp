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

std::string traitement_chargement_donnees(int choix, int id,
                string capteur_name, int minute, int hour, int day, int month,
                int year) {
        Factory *factory = new Factory();
        vector<DatasCapteur*> vect_datas;
        vect_datas.clear();
        if(choix == 1)
        {
                vect_datas = factory->load_all_datas();
        }
        else if (choix == 2)
        {
                vect_datas = factory->load_data_by_id(id);
        }
        else if(choix == 3)
        {
                vect_datas = factory->load_data_by_capteur_name(capteur_name);
        }
        else if(choix == 4)
        {
                vect_datas = factory->load_data_by_date(day, month, year);
        }
        else if(choix == 5)
        {
                vect_datas = factory->load_data_by_hour(minute, hour);
        }
        std::vector < std::string > json_string_vect =
                        factory->convert_object_to_json_string(vect_datas);
        delete factory;
        factory = nullptr;
        std::string json_string = "";
        if (json_string_vect.size() == 0)
                return json_string;
        for (std::string str : json_string_vect)
       {
                json_string += str + "\n";
        }
        return json_string;
}

std::string parser_message_request(std::string msg_request)
{

        RSJresource  resource (msg_request); // RSJ parser (delayed parser)
        int choix = resource["datas"]["choix"].as<int>(0);
        string json_response = "";
        if (choix == 1) {

                json_response = traitement_chargement_donnees(choix, 0, "", 0, 0, 0, 0, 0);
        } else if (choix == 2) {
                int id = resource["datas"]["id"].as<int>(0);
                json_response = traitement_chargement_donnees(choix, id, "", 0, 0, 0, 0, 0);
        } else if (choix == 3) {
                string id_capteur = resource["datas"]["sensor_id"].as<std::string>("uknows_sensor");
                json_response = traitement_chargement_donnees(choix, 0, id_capteur, 0, 0,
                                0, 0, 0);
        } else if (choix == 4) {

                int day = resource["datas"]["day"].as<int>(0);
                int month = resource["datas"]["month"].as<int>(0);
                int year = resource["datas"]["year"].as<int>(0);

                json_response = traitement_chargement_donnees(choix, 0, "", 0, 0, day,
                                month, year);
        } else if (choix == 5) {
                int minute = resource["datas"]["minute"].as<int>(0);
                int hour   = resource["datas"]["hour"].as<int>(0);
                json_response = traitement_chargement_donnees(choix, 0, "", minute, hour, 0,
                                0, 0);
        }
        return json_response;
}

int main(int argc, char ** argv)
{

       int port =  atoi(argv[1]);
        boost::asio::io_service io_service;
        while (1)
       {
                tcp::acceptor acceptor_(io_service, tcp::endpoint(tcp::v4(), port));

                tcp::socket socket_(io_service);

                acceptor_.accept(socket_);

                string message_request = read_(socket_);

                cout <<"message request : " << message_request << endl;
                string message_response = parser_message_request(message_request);

                cout << "message response : " << endl << message_response << endl;

                send_(socket_, message_response);

                cout << "Server TCP : sent response to client successfully !" << endl;
        }
        return 0;
}



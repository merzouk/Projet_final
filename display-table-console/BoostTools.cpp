#include "BoostTools.hpp"

namespace Manage
{
       string BoostTools::load_datas(int port, std::string ip_address, const std::string msg)
       {
                boost::asio::io_service io_service;
                tcp::socket socket(io_service);

                socket.connect( tcp::endpoint( boost::asio::ip::address::from_string(ip_address), port ) );

                boost::system::error_code error;
                boost::asio::write( socket, boost::asio::buffer(msg), error );

                if( !error )
                {
                  //cout << "Client sent request!" << endl;
                }
                else
                {
                  cout << "send request failed: " << error.message() << endl;
                }

                boost::asio::streambuf receive_buffer;
                boost::asio::read(socket, receive_buffer, boost::asio::transfer_all(), error);

                if( error && error != boost::asio::error::eof )
                {
                  cout << "receive request failed: " << error.message() << endl;
                  return "";
                }
                else
                {
                  std::string datas = boost::asio::buffer_cast<const char*>(receive_buffer.data());
                  return datas;
                }
       }
}



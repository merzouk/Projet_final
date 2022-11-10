#ifndef BOOST_TOOLS_H_FILE
#define BOOST_TOOLS_H_FILE

#include <string>
using namespace std;

#include <iostream>
#include <boost/asio.hpp>

using namespace boost::asio;
using ip::tcp;
using std::string;
using std::cout;
using std::endl;

namespace Manage
{

       class BoostTools
       {
              public:
                     BoostTools(){}
                     ~BoostTools(){}
                     string load_datas(int port, std::string ip_address, const std::string msg) ;
       };
}
#endif // BOOST_TOOLS_H_FILE

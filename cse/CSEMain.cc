/*
 * CSE-main.cc
 *
 *  Created on: 2015年7月19日
 *      Author: weimi_000
 */

#include <stdexcept>
#include <stdlib.h>
#include <iostream>
#include <fstream>

#include "CSEBase.h"
#include "CSEHandler.h"
#include "NSEBase.h"

using namespace MicroWireless::OneM2M;

/*
class CSEServer
{
public:
  /// Construct the server to listen on the specified TCP address and port, and
  /// serve up files from the given directory.
  CSEServer(const std::string& address, const std::string& port, CSEBase& cse);

  /// Run the server's io_service loop.
  void run();

private:
  CSEHandler cse_hdl_;
};

CSEServer::CSEServer(const std::string& ip, const std::string& port,
		CSEBase& cse) : cse_hdl_(cse) {

	NSEBase nse_(ip, port);
	cse_hdl_ = CSEHandler(nse_, cse);
	nse_.setRequestHandler(cse_hdl_);
}

void CSEServer::run() {
	cse_hdl_.nse_.run();
}
*/
int main(int argc, char* argv[])
{

  const char * cse_fn = DEFAULT_CSEBASE_FN;

  // Check command line arguments.
  switch (argc)
  {
  case 3: break;
  case 4: cse_fn = argv[3];
  	  	  break;
  default:
    std::cerr << "Usage: http_server <address> <port> [<CSE resource file>]\n";
    std::cerr << "  For IPv4, try:\n";
    std::cerr << "    receiver 0.0.0.0 80 .\n";
    std::cerr << "  For IPv6, try:\n";
    std::cerr << "    receiver 0::0 80 .\n";
    return 1;
  }

  if (!std::ifstream(cse_fn).good()) {
	std::cerr << "CSE resource file not valid: " << cse_fn << std::endl;
	return 1;
  }

  try
  {
	CSEBase cse_;
	if (!cse_.setCSEBase(cse_fn)) {
		throw runtime_error("CSE set resource file error: " + string(cse_fn));
	}

	NSEBase nse_(argv[1], argv[2]);
	CSEHandler cse_hdl_(nse_, cse_);
	nse_.setRequestHandler(cse_hdl_);

	cse_hdl_.run();
  }
  catch (std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << "\n";
  }

  return 0;
}


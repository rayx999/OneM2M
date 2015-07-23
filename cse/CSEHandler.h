/*
 * CSEHandler.h
 *
 *  Created on: 2015年7月21日
 *      Author: weimi_000
 */

#ifndef CSE_CSEHANDLER_H_
#define CSE_CSEHANDLER_H_

#include "CommonTypes.h"
#include "RequestHandler.h"

namespace MicroWireless {
namespace OneM2M {

using namespace MicroWireless::OneM2M;

class NSEBase;
class CSEBase;
class Request;
class Response;

class CSEHandler : public RequestHandler {

public:
	CSEHandler(NSEBase& nse, CSEBase& cse)
		: RequestHandler(nse), cse_(cse) {};

	void handleRequest(Request& request);

private:
	bool buildResponse(Operation op, Response& rsp);

private:
	CSEBase& cse_;
};

}	// OneM2M

}	// MicroWireless

#endif /* CSE_CSEHANDLER_H_ */

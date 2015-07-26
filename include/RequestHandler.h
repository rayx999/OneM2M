/*
 * RequestHandler.h
 *
 *  Created on: 2015年7月21日
 *      Author: weimi_000
 */

#ifndef INCLUDE_REQUESTHANDLER_H_
#define INCLUDE_REQUESTHANDLER_H_

#include <string>

#include "CommonTypes.h"

namespace MicroWireless {
namespace OneM2M {

using namespace MicroWireless::OneM2M;

class Request;
class CSEBase;
class NSEBase;

class RequestHandler {
public:
	RequestHandler(NSEBase& nse) : nse_(nse),
		domain_(), csi_(), fr_(), to_() {};

	virtual ~RequestHandler() {};

	virtual void handleRequest(Request& request);

protected:
	ResponseStatusCode isForMe(Request& req, CSEBase& cse);
	bool isResourceValid();

protected:
	NSEBase& nse_;

	std::string domain_, csi_, fr_, to_;
};

}	// OneM2M
}	// MicroWireless

#endif /* INCLUDE_REQUESTHANDLER_H_ */

/*
 * RequestHandler.cc
 *
 *  Created on: 2015年7月22日
 *      Author: weimi_000
 */

#include <string>

#include "RequestHandler.h"
#include "NSEBase.h"

namespace MicroWireless {
namespace OneM2M {

using namespace MicroWireless::OneM2M;

void RequestHandler::handleRequest(Request& req) {
	//req.getCommonAttr(to_, fr_, domain_, csi_);
}

ResponseStatusCode RequestHandler::isForMe(Request& req, CSEBase& cse) {
	ResponseStatusCode rsc_ = RSC_OK;
/*
	if (req.isValid()) {
		if (domain_.compare(cse.getDomain()) != 0) {
			rsc_ = RSC_ACCESS_DENIED;
		}

	} else {
		rsc_ = RSC_BAD_REQUEST;
	}
*/
	return rsc_;
}

bool RequestHandler::isResourceValid() {
	return true;
}

}	// OneM2M
}	// MicroWireless

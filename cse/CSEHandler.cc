/*
 * CSEHandler.cc
 *
 *  Created on: 2015年7月21日
 *      Author: weimi_000
 */

#include <string>

#include "Request.h"
#include "Response.h"
//#include "RequestHandler.h"
#include "CSEHandler.h"
#include "NSEBase.h"

namespace MicroWireless {
namespace OneM2M {

using namespace MicroWireless::OneM2M;

void CSEHandler::handleRequest(Request& req) {
	RequestHandler::handleRequest(req);
	ResponseStatusCode _rsc = isForMe(req, cse_);

	if (_rsc == RSC_OK) {
		switch (req.getOperation()) {
		case OPERATION_CREATE:
			break;
		case OPERATION_RETRIEVE:
			if (!isResourceValid()) {
				_rsc = RSC_NOT_FOUND;
			}
			break;
		case OPERATION_UPDATE:
			break;
		case OPERATION_DELETE:
			break;
		case OPERATION_NOTIFY:
			break;
		default:
			break;
		}
	} else {
		_rsc = RSC_BAD_REQUEST;
	}

	Response _rsp(&req, _rsc, req.getRequestId());	// FIX ME: remove rqi
	nse_.send(_rsp);
}

}	// OneM2M

}	// MicroWireless

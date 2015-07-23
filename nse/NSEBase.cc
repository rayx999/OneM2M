/*
 * NSEBase.cc
 *
 *  Created on: 2015年7月22日
 *      Author: weimi_000
 */

#include <iostream>

#include "NSEBase.h"
#include "Response.h"

using namespace MicroWireless::OneM2M;

namespace MicroWireless {

namespace OneM2M {

void NSEBase::setRequestHandler(RequestHandler & req_hdl) {
//	request_handler_ = req_hdl;
}

void NSEBase::send(Response& rsp) {
	std::cout << "Send response:" << std::endl;
	std::cout << rsp.getJson() << std::endl;
}

void NSEBase::run() {
}

}	// OneM2M
}	// MicroWireless


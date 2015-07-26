/*
 * CSEServer.cc
 *
 *  Created on: 2015年7月25日
 *      Author: weimi_000
 */

#include "CommonTypes.h"
#include "CSEBase.h"
#include "NSEBase.h"
#include "CSEHandler.h"
#include "CSEServer.h"

using namespace MicroWireless::OneM2M;

CSEServer::CSEServer(CSEBase& cse, NSEBase& nse, CSEHandler& hdl) :
	cse_(cse),
	nse_(nse),
	hdl_(hdl)
{
	nse_.setRequestHandler(hdl_);
}

void CSEServer::run() {
	nse_.run();
}



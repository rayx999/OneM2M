/*
 * CSEServer.h
 *
 *  Created on: 2015年7月25日
 *      Author: weimi_000
 */

#ifndef CSE_CSESERVER_H_
#define CSE_CSESERVER_H_


#include "CommonTypes.h"
#include "CSEBase.h"
#include "NSEBase.h"
#include "CSEHandler.h"

using namespace MicroWireless::OneM2M;

class CSEServer
{
public:
	CSEServer(CSEBase& cse, NSEBase& nse, CSEHandler& hdl);

	void run();

private:
	CSEBase& cse_;
	NSEBase& nse_;
	CSEHandler& hdl_;
};

#endif /* CSE_CSESERVER_H_ */

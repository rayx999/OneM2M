/*
 * Response.h
 *
 *  Created on: 2015年7月18日
 *      Author: weimi_000
 */

#ifndef INCLUDE_RESPONSE_H_
#define INCLUDE_RESPONSE_H_

#include "Response.pb.h"
#include "CommonTypes.h"
#include "CommonUtils.h"
#include "Request.h"

using namespace std;
using namespace MicroWireless::OneM2M;

class Response
{
public:
	Response(Request * p_request, string &json);
	Response(Request * p_request, ResponseStatusCode rsc, string & rqi);

	ResponseStatusCode getResponseStatusCode();
	const string & getRequestId();

	bool setContent(string & pc);
	const string & getContent();

	bool setTo(string & to);
	const string & getTo();

	bool setFrom(string & fr);
	const string & getFrom();

	bool setOriginatingTimestamp(TimeStamp &ot);
	bool getOriginatingTimestamp(TimeStamp &ot);

	bool setResultExpireTimestamp(TimeStamp &rset);
	bool getResultExpireTimestamp(TimeStamp &rset);

	bool setEventCat(EventCat ec);
	EventCat getEventCat();

	bool isValid(ValidateType vt = VALIDATE_COMMON);
	string getJson();

	~Response();

private:
	Request * p_request_;		// matching request.
	pb::Response response_pb_;
};

#endif /* INCLUDE_RESPONSE_H_ */

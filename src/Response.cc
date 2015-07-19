/*
 * Response.cc
 *
 *  Created on: 2015年7月18日
 *      Author: weimi_000
 */

#include <stdexcept>
#include <iostream>
#include <sstream>
#include <json2pb.h>

#include "Response.pb.h"
#include "Response.h"

using namespace std;
using namespace MicroWireless::OneM2M;


Response::Response(Request *p_request, string &json) {
	// keep original request reference
	if (p_request == NULL || !p_request->isValid()) {
		throw runtime_error("Matching request is invalid!");
	}
	p_request_ = p_request;

	// parse to PB buffer
	json2pb(response_pb_, json.c_str(), json.length());

	if (!isValid()) {
		throw runtime_error("Response in JSON not valid!");
	}
}

Response::Response(Request *p_request, ResponseStatusCode rsc, string & rqi){
	if (rqi.empty()) {
		throw runtime_error("Response mandatory field: requestId missing!");
	}
	// keep original request reference
	if (p_request == NULL || !p_request->isValid()) {
		throw runtime_error("Matching request is invalid!");
	}
	p_request_ = p_request;
	// Mandatory fields
	response_pb_.set_rsc(static_cast<pb::CommonTypes_ResponseStatusCode>(rsc));
	if (!setString(rqi, &pb::Response::set_allocated_rqi)) {
		throw runtime_error("Response(status_code, req_id) failed.");
	}
}

ResponseStatusCode Response::getResponseStatusCode() {
	return static_cast<ResponseStatusCode>(response_pb_.rsc());
}

bool Response::setContent(string & pc) {
	return setString(pc, &pb::Response::set_allocated_pc);
}

const string & Response::getContent() {
	return response_pb_.pc();
}

bool Response::setTo(string & to) {
	return setString(to, &pb::Response::set_allocated_to);
}

const string & Response::getTo() {
	return response_pb_.to();
}

bool Response::setFrom(string & fr) {
	return setString(fr, &pb::Response::set_allocated_fr);
}

const string & Response::getFrom() {
	return response_pb_.fr();
}

bool Response::setOriginatingTimestamp(TimeStamp &ot){  }
bool Response::getOriginatingTimestamp(TimeStamp &ot){  }

bool Response::setResultExpireTimestamp(TimeStamp &rset){  }
bool Response::getResultExpireTimestamp(TimeStamp &rset){  }

bool Response::setEventCat(EventCat ec){  }
EventCat Response::getEventCat(){  }

bool Response::isValid(ValidateType vt) {

	if (getResponseStatusCode() == RSC_NONE ||
		response_pb_.rqi().empty()) {
		cerr << "Request miss request id or response status code." << endl;
		return false;
	}

	if (vt == VALIDATE_COMMON) {
		return true;
	}

	switch (p_request_->getOperation()) {
	case OPERATION_CREATE:
		break;
	case OPERATION_RETRIEVE:
		if (response_pb_.pc().empty()) {
			cerr << "Request miss content." << endl;
			return false;
		}
		break;
	case OPERATION_UPDATE:
		break;
	case OPERATION_DELETE:
		break;
	case OPERATION_NOTIFY:
		break;
	default:
		cerr << "Invalid response operation: " << p_request_->getOperation() << endl;
		return false;
	}

	return true;
}

string Response::getJson(){  }

Response::~Response() {
/*	if (p_request_ != NULL) {
		delete p_request_;
		p_request_ = NULL;
	} */
}

bool Response::setString(string & s, void (pb::Response::*setter)(string *)) {
	string * _p = new string(s);

	if (_p == NULL) {
		cerr << "Can't allocate. new(" << s << ") failed." << endl;
		return false;
	} else {
		(response_pb_.*setter)(_p);
		return true;
	}
}



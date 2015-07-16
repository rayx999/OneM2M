/*
 * CSEBase.cc
 *
 *  Created on: 2015年7月15日
 *      Author: weimi_000
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <json2pb.h>

#include "CommonTypes.pb.h"
#include "CSEBase.pb.h"
#include "CSEBase.h"

using namespace std;
using namespace MicroWireless::OneM2M::pb;

namespace MicroWireless {

namespace OneM2M {

CSEBase::CSEBase() {
	// set create time
	TimeStamp _ct;
	gettimeofday(&_ct, NULL);

	setCreateTimestamp(_ct);
}

bool CSEBase::setCSEBase(const char * fn) {
	bool _ret = false;
    fstream ins(fn, ios::in | ios::binary);

    if (!ins) {
        cout << "Can't open resource file " << fn << endl;
    } else if (!cse_base_.ParseFromIstream(&ins)) {
        cerr << "Failed to parse resource file " << fn << endl;
    } else {
    	_ret = true;
    }

    return _ret;
}

bool CSEBase::setCSEBase(stringstream &sbuf) {
	string bstr = sbuf.str();
	pb::CSEBase _cse_base;

	// parse to PB buffer
	json2pb(_cse_base, bstr.c_str(), bstr.length());

	// need to keep original create time if Json file
	// doesn't have create time set up
	TimeStamp _ct;
	bool _ct_set = true;
	if (!_cse_base.has_ct()) {
		getCreateTimestamp(_ct);
		_ct_set = false;
	}
	cse_base_ = _cse_base;
	if (!_ct_set) {
		setCreateTimestamp(_ct);
	}
}

const string& CSEBase::getCSEId() {
	return cse_base_.csi();
}

CSEType CSEBase::getCSEType() {
	return (CSEType)cse_base_.ty();
}

const string& CSEBase::getResourceId() {
	return cse_base_.ri();
}

const string& CSEBase::getResourceName() {
	return cse_base_.rn();
}

bool CSEBase::getCreateTimestamp(TimeStamp &ct) {
	if (cse_base_.has_ct()) {
		const google::protobuf::Timestamp &_ct =
				cse_base_.ct();
		ct.tv_sec = _ct.seconds();
		ct.tv_usec = _ct.nanos() / 1000;
		return true;
	}
	return false;
}

bool CSEBase::getLastModifiedTimestamp(TimeStamp &lt) {
	if (cse_base_.has_lt()) {
		const google::protobuf::Timestamp &_lt =
				cse_base_.lt();
		lt.tv_sec = _lt.seconds();
		lt.tv_usec = _lt.nanos() / 1000;
		return true;
	}
	return false;
}

bool CSEBase::setCreateTimestamp(TimeStamp &ct) {
	google::protobuf::Timestamp * _ts =
			new(google::protobuf::Timestamp);

	if (_ts != NULL) {
		_ts->set_seconds(ct.tv_sec);
		_ts->set_nanos(ct.tv_usec * 1000);
		cse_base_.set_allocated_ct(_ts);
		return true;
	} else {
		cerr << "Can't allocate pb::Timestamp." << endl;
		return false;
	}
}

bool CSEBase::setLastModifiedTimestamp(TimeStamp &lt) {
	google::protobuf::Timestamp * _ts =
			new(google::protobuf::Timestamp);

	if (_ts != NULL) {
		_ts->set_seconds(lt.tv_sec);
		_ts->set_nanos(lt.tv_usec * 1000);
		cse_base_.set_allocated_lt(_ts);
		return true;
	} else {
		cerr << "Can't allocate pb::Timestamp." << endl;
		return false;
	}
}

int CSEBase::getSupportedResource(ResourceType *&rt) {
	google::protobuf::RepeatedField<int> * _rt =
			cse_base_.mutable_srt();
    rt = (ResourceType *)_rt->mutable_data();
	return cse_base_.srt_size();
}

bool CSEBase::isResourceSupported(ResourceType rt) {
	google::protobuf::RepeatedField<int>::const_iterator _it;
	const google::protobuf::RepeatedField<int>& _srt =
			cse_base_.srt();
	for (_it = _srt.begin(); _it != _srt.end(); _it++) {
		if (*_it == rt) {
			return true;
		}
	}
	return false;
}

bool CSEBase::outToFile(const char * fn) {
	// update last_modified_time
	TimeStamp _lt;
	gettimeofday(&_lt, NULL);
	if (!setLastModifiedTimestamp(_lt)) {
		cerr << "Can't set last modified time." << endl;
		return false;
	}

    fstream ous(fn, ios::out | ios::trunc | ios::binary);
    if (!cse_base_.SerializeToOstream(&ous)) {
      cerr << "Failed to write " << fn << endl;
      return false;
    }
	return true;
}

string CSEBase::getJson() {
  	return pb2json(cse_base_);
}


}	// OneM2M

}	// MicroWireless




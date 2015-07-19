/*
 * test_Request.cc
 *
 *  Created on: 2015年7月17日
 *      Author: weimi_000
 */
#include <iostream>
#include <fstream>
#include <sstream>

#include "gtest/gtest.h"
#include "test_utils.h"
#include "Request.h"

using namespace MicroWireless::OneM2M;

class RequestTest : public ::testing::Test {
	protected:
	string request_json;
	Operation op_;
	string to_;
	string fr_;
	string rqi_;
	Request * p_request_;

	RequestTest() {
		request_json = string("{\"op\": 2, \"to\": \"//microwireless.com/IN-CSE-01\", \"rqi\": \"ab3f124a\", \"fr\": \"//microwireless.com/AE-01\"}");
		op_ = OPERATION_RETRIEVE;
		to_ = string("//microwireless.com/IN-CSE-01");
		fr_ = string("//microwireless.com/AE-01");
		rqi_ = string("ab3f124a");
		p_request_ = NULL;
	}

	virtual void SetUp() {
		p_request_ = new Request(request_json);
	}

	Operation getOperation() {
		return p_request_->getOperation();
	}

	const string & getTo() {
		return p_request_->getTo();
	}

	const string & getFrom() {
		return p_request_->getFrom();
	}

	const string & getRequestId() {
		return p_request_->getRequestId();
	}

	bool setResourceType(ResourceType ty) {
		return p_request_->setResourceType(ty);
	}

	ResourceType getResourceType() {
		return p_request_->getResourceType();
	}

	virtual void TearDown() {
		if (p_request_ == NULL) {
			delete p_request_;
			p_request_ = NULL;
		}
	}
};

TEST_F(RequestTest, FullCtor) {
	try {
		Request request_(op_, to_, fr_, rqi_);
	} catch (const exception &e) {
		ASSERT_TRUE(false);
	}
}

TEST_F(RequestTest, CtorNoTo) {
	string to_none;

	try {
		Request request_(op_, to_none, fr_, rqi_);
	} catch (const exception &e) {
		cout << "Expected exception:" << e.what() << endl;
		return;
	}
	ASSERT_TRUE(false);
}

TEST_F(RequestTest, CtorNoFr) {
	string rqi_none;

	try {
		Request request_(op_, to_, fr_, rqi_none);
	} catch (const exception &e) {
		cout << "Expecetd exception:" << e.what() << endl;
		return;
	}
	ASSERT_TRUE(false);
}

TEST_F(RequestTest, CtorNoRqi) {
	string fr_none;

	try {
		Request request_(op_, to_, fr_none, rqi_);
	} catch (const exception &e) {
		cout << "Expected exception:" << e.what() << endl;
		return;
	}
	ASSERT_TRUE(false);
}

TEST_F(RequestTest, JsonNormal) {
	try {
		Request request_(request_json);
	} catch (const exception &e) {
		cout << "exception:" << e.what() << endl;
		ASSERT_TRUE(false);
	}
}

TEST_F(RequestTest, JsonInvalidOpl) {
	string json("{\"op\": 10, \"to\": \"//microwireless.com/IN-CSE-01\", \"rqi\": \"ab3f124a\", \"fr\": \"//microwireless.com/AE-01\"}");

	try {
		Request request_(json);
	} catch (const exception &e) {
		cout << "Expected exception:" << e.what() << endl;
		return;
	}
	ASSERT_TRUE(false);
}

TEST_F(RequestTest, JsonNoTo) {
	string json("{\"op\": 2, \"rqi\": \"ab3f124a\", \"fr\": \"//microwireless.com/AE-01\"}");

	try {
		Request request_(json);
	} catch (const exception &e) {
		cout << "Expected exception:" << e.what() << endl;
		return;
	}
	ASSERT_TRUE(false);
}

TEST_F(RequestTest, JsonNoFr) {
	string json("{\"op\": 2, \"to\": \"//microwireless.com/IN-CSE-01\", \"rqi\": \"ab3f124a\"}");

	try {
		Request request_(json);
	} catch (const exception &e) {
		cout << "Expected exception:" << e.what() << endl;
		return;
	}
	ASSERT_TRUE(false);
}

TEST_F(RequestTest, JsonNoRqi) {
	string json("{\"op\": 2, \"to\": \"//microwireless.com/IN-CSE-01\", \"fr\": \"//microwireless.com/AE-01\"}");

	try {
		Request request_(json);
	} catch (const exception &e) {
		cout << "Expected exception:" << e.what() << endl;
		return;
	}
	ASSERT_TRUE(false);
}

TEST_F(RequestTest, RetrieveWithResourceType) {
	string json("{\"op\": 2, \"to\": \"//microwireless.com/IN-CSE-01\", \"rqi\": \"ab3f124a\", \"fr\": \"//microwireless.com/AE-01\", \"ty\": 1}");
	Request * pReq_ = NULL;
	try {
		pReq_ = new Request(json);
	} catch (const exception &e) {
		cout << "Exception:" << e.what() << endl;
		ASSERT_TRUE(false);
		return;
	}
	ASSERT_FALSE(pReq_->isValid(VALIDATE_ALL));
}

TEST_F(RequestTest, RetrieveWithName) {
	string json("{\"op\": 2, \"to\": \"//microwireless.com/IN-CSE-01\", \"rqi\": \"ab3f124a\", \"fr\": \"//microwireless.com/AE-01\", \"nm\": \"Name\" }");
	Request * pReq_ = NULL;
	try {
		pReq_ = new Request(json);
	} catch (const exception &e) {
		cout << "Exception:" << e.what() << endl;
		ASSERT_TRUE(false);
		return;
	}
	ASSERT_FALSE(pReq_->isValid(VALIDATE_ALL));
}

TEST_F(RequestTest, SetGetResourceType) {
	ASSERT_TRUE(setResourceType(NORMAL));
	ASSERT_EQ(getResourceType(), NORMAL);
}

TEST_F(RequestTest, GetAttributes) {
	ASSERT_EQ(getOperation(), OPERATION_RETRIEVE);
	ASSERT_STREQ(getTo().c_str(), to_.c_str());
	ASSERT_STREQ(getFrom().c_str(), fr_.c_str());
	ASSERT_STREQ(getRequestId().c_str(), rqi_.c_str());
}

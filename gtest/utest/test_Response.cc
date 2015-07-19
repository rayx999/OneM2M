/*
 * test_Response.cc
 *
 *  Created on: 2015年7月18日
 *      Author: weimi_000
 */
#include <iostream>
#include <fstream>
#include <sstream>

#include "gtest/gtest.h"
#include "test_utils.h"
#include "Response.h"

using namespace MicroWireless::OneM2M;

class ResponseTest : public ::testing::Test {
	protected:
	string request_json;
	Response * response_;
	Request * p_request_;

	ResponseTest() {
		request_json = string("{\"op\": 2, \"to\": \"//microwireless.com/IN-CSE-01\", \"rqi\": \"ab3f124a\", \"fr\": \"//microwireless.com/AE-01\"}");
		string response_json("{\"rsc\": 2000, \"rqi\": \"ab3f124a\"}");
		response_ = new Response(new Request(request_json), response_json);
		p_request_ = NULL;
	}

	virtual void SetUp() {
		p_request_ = new Request(request_json);
	}

	ResponseStatusCode getResponseStatusCode() {
		return response_->getResponseStatusCode();
	}

	bool setContent(string & pc) {
		return response_->setContent(pc);
	}

	const string & getContent() {
		return response_->getContent();
	}

	virtual void TearDown() {
		DeleteRequestPtr();
	}

	inline void DeleteRequestPtr() {
		if (p_request_ != NULL) {
			delete p_request_;
			p_request_ = NULL;
		}
	}
};

TEST_F(ResponseTest, FullCtor) {
	ResponseStatusCode rsc = RSC_OK;
	string rqi("ab3f124a");

	try {
		Response response_(p_request_, rsc, rqi);
	} catch (const exception &e) {
		cout << "Exception: " << e.what() << endl;
		ASSERT_TRUE(false);
	}
}

TEST_F(ResponseTest, CtorNoRqi) {
	ResponseStatusCode rsc = RSC_OK;
	string rqi;

	try {
		Response response_(p_request_, rsc, rqi);
	} catch (const exception &e) {
		cout << "Expected exception:" << e.what() << endl;
		return;
	}
	ASSERT_TRUE(false);
}

TEST_F(ResponseTest, JsonNormal) {
	string response_json("{\"rsc\": 2000, \"rqi\": \"ab3f124a\"}");

	try {
		Response response_(p_request_, response_json);
	} catch (const exception &e) {
		cout << "exception:" << e.what() << endl;
		ASSERT_TRUE(false);
	}
}

TEST_F(ResponseTest, JsonInvalidRsc) {
	string response_json("{\"rsc\": 10, \"rqi\": \"ab3f124a\"}");

	try {
		Response response_(p_request_, response_json);
	} catch (const exception &e) {
		cout << "Expected exception:" << e.what() << endl;
		return;
	}
	ASSERT_TRUE(false);
}

TEST_F(ResponseTest, JsonNoRsc) {
	string response_json("{\"rqi\": \"ab3f124a\"}");

	try {
		Response response_(p_request_, response_json);
	} catch (const exception &e) {
		cout << "Expected exception:" << e.what() << endl;
		return;
	}
	ASSERT_TRUE(false);
}

TEST_F(ResponseTest, JsonNoRqi) {
	string response_json("{\"rsc\": 2000");

	try {
		Response response_(p_request_, response_json);
	} catch (const exception &e) {
		cout << "Expected exception:" << e.what() << endl;
		return;
	}
	ASSERT_TRUE(false);
}
/*
TEST_F(ResponseTest, RetrieveWithResourceType) {
	string json("{\"op\": 2, \"to\": \"//microwireless.com/IN-CSE-01\", \"rqi\": \"ab3f124a\", \"fr\": \"//microwireless.com/AE-01\", \"ty\": 1}");
	Response * pReq_ = NULL;
	try {
		pReq_ = new Response(json);
	} catch (const exception &e) {
		cout << "Expected exception:" << e.what() << endl;
		return;
	}
	ASSERT_FALSE(pReq_->isValid());
}

TEST_F(ResponseTest, RetrieveWithName) {
	string json("{\"op\": 2, \"to\": \"//microwireless.com/IN-CSE-01\", \"rqi\": \"ab3f124a\", \"fr\": \"//microwireless.com/AE-01\", \"nm\": \"Name\" }");
	Response * pReq_ = NULL;
	try {
		pReq_ = new Response(json);
	} catch (const exception &e) {
		cout << "Expected exception:" << e.what() << endl;
		return;
	}
	ASSERT_FALSE(pReq_->isValid());
}
*/

TEST_F(ResponseTest, GetAttributes) {
	ASSERT_EQ(getResponseStatusCode(), RSC_OK);

}

TEST_F(ResponseTest, SetGetContent) {
	ASSERT_TRUE(setContent(request_json));
	ASSERT_STREQ(getContent().c_str(), request_json.c_str());
}

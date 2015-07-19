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
	Request * request_;

	RequestTest() {
		string json("{\"op\": 2, \"to\": \"//microwireless.com/IN-CSE-01\", \"rqi\": \"ab3f124a\", \"fr\": \"//microwireless.com/AE-01\"}");
		request_ = new Request(json);
	}

	virtual void SetUp() {
	}

	Operation getOperation() {
		return request_->getOperation();
	}

	bool setResourceType(ResourceType ty) {
		return request_->setResourceType(ty);
	}

	ResourceType getResourceType() {
		return request_->getResourceType();
	}
};

TEST_F(RequestTest, FullCtor) {
	Operation op = OPERATION_RETRIEVE;
	string to("//microwireless.com/IN-CSE-01");
	string fr("//microwireless.com/AE-01");
	string rqi("ab3f124a");

	try {
		Request request_(op, to, fr, rqi);
	} catch (const exception &e) {
		ASSERT_TRUE(false);
	}
}

TEST_F(RequestTest, CtorNoTo) {
	Operation op = OPERATION_RETRIEVE;
	string to;
	string fr("//microwireless.com/AE-01");
	string rqi("ab3f124a");

	try {
		Request request_(op, to, fr, rqi);
	} catch (const exception &e) {
		cout << "Expected exception:" << e.what() << endl;
		return;
	}
	ASSERT_TRUE(false);
}

TEST_F(RequestTest, CtorNoFr) {
	Operation op = OPERATION_RETRIEVE;
	string to("//microwireless.com/IN-CSE-01");
	string fr("//microwireless.com/AE-01");
	string rqi;

	try {
		Request request_(op, to, fr, rqi);
	} catch (const exception &e) {
		cout << "Expecetd exception:" << e.what() << endl;
		return;
	}
	ASSERT_TRUE(false);
}

TEST_F(RequestTest, CtorNoRqi) {
	Operation op = OPERATION_RETRIEVE;
	string to("//microwireless.com/IN-CSE-01");
	string fr;
	string rqi("ab3f124a");

	try {
		Request request_(op, to, fr, rqi);
	} catch (const exception &e) {
		cout << "Expected exception:" << e.what() << endl;
		return;
	}
	ASSERT_TRUE(false);
}

TEST_F(RequestTest, JsonNormal) {
	string json("{\"op\": 2, \"to\": \"//microwireless.com/IN-CSE-01\", \"rqi\": \"ab3f124a\", \"fr\": \"//microwireless.com/AE-01\"}");

	try {
		Request request_(json);
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
		cout << "Expected exception:" << e.what() << endl;
		return;
	}
	ASSERT_FALSE(pReq_->isValid());
}

TEST_F(RequestTest, RetrieveWithName) {
	string json("{\"op\": 2, \"to\": \"//microwireless.com/IN-CSE-01\", \"rqi\": \"ab3f124a\", \"fr\": \"//microwireless.com/AE-01\", \"nm\": \"Name\" }");
	Request * pReq_ = NULL;
	try {
		pReq_ = new Request(json);
	} catch (const exception &e) {
		cout << "Expected exception:" << e.what() << endl;
		return;
	}
	ASSERT_FALSE(pReq_->isValid());
}

TEST_F(RequestTest, SetGetResourceType) {
	ASSERT_TRUE(setResourceType(NORMAL));
	ASSERT_EQ(getResourceType(), NORMAL);
}

TEST_F(RequestTest, GetAttributes) {
	ASSERT_EQ(getOperation(), OPERATION_RETRIEVE);
}

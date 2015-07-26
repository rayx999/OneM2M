/*
 * NSEBase_mock.cc
 *
 *  Created on: 2015年7月24日
 *      Author: weimi_000
 */


//#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "CommonTypes.h"
#include "CSEBase.h"
#include "Request.h"
#include "Response.h"
#include "NSEBase_mock.h"
#include "CSEHandler.h"
#include "CSEServer.h"

using namespace MicroWireless::OneM2M;

using ::testing::Invoke;
using ::testing::Matcher;
using ::testing::Property;
using ::testing::Eq;

class NSEBaseMockTest : public ::testing::Test {
protected:
	static const std::string retrieve_json;
	Request * req_;
	Response * rsp_;
	CSEBase * cse_;
	NSEBaseMock * nse_;
	CSEHandler * hdl_;
	CSEServer * server_;

public:
    virtual void SetUp()
    {
        cse_ = new CSEBase(DEFAULT_CSEBASE_FN);
        nse_ = new NSEBaseMock("127.0.0.1", "1234");
        hdl_ = new CSEHandler(*nse_, *cse_);
        server_ = new CSEServer(*cse_, *nse_, *hdl_);
        req_ = NULL;
    }

    virtual void TearDown()
    {
        delete cse_;
        delete nse_;
        delete hdl_;
        delete server_;
        delete req_;
    }

    void handleRequest() {
    	req_ = new Request(retrieve_json);
    	hdl_->handleRequest(*req_);
    }

};

const string NSEBaseMockTest::retrieve_json("{\"op\": 2, \"to\": \"//microwireless.com/IN-CSE-01\", \"rqi\": \"ab3f124a\", \"fr\": \"//microwireless.com/AE-01\"}");

TEST_F(NSEBaseMockTest, RetrieveCSE) {

  EXPECT_CALL(*nse_, run())
  	  .WillOnce(Invoke(this, &NSEBaseMockTest::handleRequest));

//  Matcher<const Response&> m
//  	  = Property(&Response::getResponseStatusCode, 2000));
  ON_CALL(*nse_, send(Property(&Response::getResponseStatusCode, Eq(RSC_OK))));

  server_->run();

}
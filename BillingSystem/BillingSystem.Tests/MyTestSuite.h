#pragma once

#include "cxxtest/TestSuite.h"

#include "CommonUtils.h"
#include "PhoneNumber.h"
#include "Timestamp.h"
#include "Account.h"
#include "CallRecord.h"
#include "ReckoningModule.h"

class MyTestSuite : public CxxTest::TestSuite
{
public:
    void testPhoneNumber(void)
    {
		TS_ASSERT(BillingModule::PhoneNumber("050123").IsValid());
		TS_ASSERT(!BillingModule::PhoneNumber("05").IsValid());
    }

	void testTimestamp(void)
	{
		BillingModule::Timestamp timestamp;

		//date
		std::string testStr = "2018-02-20";
		timestamp.DateFromStr(testStr);
		TS_ASSERT(timestamp.IsValid());
		TS_ASSERT_EQUALS(timestamp.DateToStr(), testStr);
		

		timestamp.DateFromStr("2018-02-");
		TS_ASSERT(!timestamp.IsValid());


		//time
		testStr = "00:30:00";
		timestamp.TimeFromStr(testStr);
		TS_ASSERT(timestamp.IsValid());
		TS_ASSERT_EQUALS(timestamp.TimeToStr(), testStr);

		timestamp.TimeFromStr("00::00");
		TS_ASSERT(!timestamp.IsValid());

		testStr = "00:00:20";
		timestamp.TimeFromStr(testStr);
		TS_ASSERT_EQUALS(timestamp.GetTimestampInSeconds(), 20);
		TS_ASSERT_LESS_THAN(timestamp.GetTimestampInSeconds(), 30);


		//datetime
		timestamp.DateTimeFromStr("2018-01-01_16:22:00");
		TS_ASSERT(timestamp.IsValid());
		TS_ASSERT(!timestamp.IsWeekend());

		timestamp.DateTimeFromStr("2018-00-06_16:22:00");
		TS_ASSERT(timestamp.IsValid());
		TS_ASSERT(timestamp.IsWeekend());

		timestamp.TimeFromStr("2018-01-01_16::00");
		TS_ASSERT(!timestamp.IsValid());
	}

	void testAccount(void)
	{
		BillingModule::Timestamp freeTime, refillDate;
		freeTime.TimeFromStr("12:25:00");
		refillDate.DateFromStr("2018-02-20");

		TS_ASSERT(BillingModule::Account(BillingModule::PhoneNumber("050123"), freeTime, refillDate).IsValid());
		TS_ASSERT(!BillingModule::Account(BillingModule::PhoneNumber("1"), freeTime, refillDate).IsValid());
	}

	BillingModule::CallRecord GetInitedCallRecord()
	{
		BillingModule::PhoneNumber accNumber("0506");
		BillingModule::PhoneNumber incoming("1112");

		BillingModule::Timestamp callStarted, callFinished;
		callStarted.DateTimeFromStr("2018-01-01_16:22:00");
		callFinished.DateTimeFromStr("2018-01-01_16:24:01");

		return BillingModule::CallRecord(accNumber, incoming, callStarted, callFinished);
	}

	void testCallRecord(void)
	{
		BillingModule::Timestamp freeTime, refillDate;
		freeTime.TimeFromStr("12:25:00");
		refillDate.DateFromStr("2018-02-20");

		BillingModule::CallRecord cr = GetInitedCallRecord();

		TS_ASSERT(cr.IsValid());

		cr.m_CallFinished.DateTimeFromStr("2018-01-01_16:20:01");

		TS_ASSERT(!cr.IsValid());
	}

	void testCommonFunctions(void)
	{
		int64_t standard = 42;

		TS_ASSERT_LESS_THAN(standard, BillingModule::CommonUtils::StrToInt64("43"));
		TS_ASSERT_EQUALS(standard, BillingModule::CommonUtils::StrToInt64("42"));

		BillingModule::Timestamp callStarted, callFinished;
		callStarted.DateTimeFromStr("2018-02-11_16:22:00");
		callFinished.DateTimeFromStr("2018-02-11_16:22:42");
		TS_ASSERT_EQUALS(standard, BillingModule::CommonUtils::GetCallDuration(callFinished.GetTimestamp(), callStarted.GetTimestamp()));

		TS_ASSERT(!BillingModule::CommonUtils::IsGoneMoreThanNDays(callFinished.GetTimestamp(), callStarted.GetTimestamp(), 2));
	}

	void testReckoningModuleInitialization(void)
	{
		BillingModule::BillingValues billingValues;
		BillingModule::ReckoningModule reckoningModule;

		TS_ASSERT(!reckoningModule.IsInited());

		reckoningModule.InitReckoningModule(billingValues);

		TS_ASSERT(reckoningModule.IsInited());
	}

	BillingModule::BillingValues GetInitedBillingValues()
	{
		BillingModule::BillingValues billingValues;

		billingValues.m_ConnectionCost = 10;
		billingValues.m_CostInsideNetwork = 5;
		billingValues.m_CostOutsideNetwork = 25;
		billingValues.m_FreeTimeExpiryPeriod = 30;
		billingValues.m_FreeTimeInEachWeekendCall.TimeFromStr("00:10:00");
		billingValues.m_FreeTimeInNetwork.TimeFromStr("00:20:00");
		billingValues.m_StartMonetizationTime.TimeFromStr("00:00:05");

		return billingValues;
	}

	BillingModule::Account GetInitedAccount()
	{
		BillingModule::PhoneNumber accNumber("0506");

		BillingModule::Timestamp freeTime, refillDate;
		freeTime.TimeFromStr("12:25:00");
		refillDate.DateFromStr("2018-02-20");

		return BillingModule::Account(accNumber, freeTime, refillDate);
	}

	void testReckoningModuleCallOutside(void)
	{
		BillingModule::ReckoningModule reckoningModule;

		reckoningModule.InitReckoningModule(GetInitedBillingValues());

		std::unique_ptr<BillingModule::CallRecord> cr(new BillingModule::CallRecord(GetInitedCallRecord()));
		std::shared_ptr<BillingModule::Account> acc = std::make_shared<BillingModule::Account>(BillingModule::Account(GetInitedAccount()));

		TS_ASSERT_EQUALS(reckoningModule.GetCallCost(cr, acc), 60);
	}
	
	void testReckoningModuleCallOnWeekend(void)
	{
		BillingModule::ReckoningModule reckoningModule;

		reckoningModule.InitReckoningModule(GetInitedBillingValues());

		std::unique_ptr<BillingModule::CallRecord> cr(new BillingModule::CallRecord(GetInitedCallRecord()));
		std::shared_ptr<BillingModule::Account> acc = std::make_shared<BillingModule::Account>(BillingModule::Account(GetInitedAccount()));

		cr->m_CallStarted.DateTimeFromStr("2018-00-06_16:22:00");
		cr->m_CallFinished.DateTimeFromStr("2018-00-06_16:24:01");

		TS_ASSERT_EQUALS(reckoningModule.GetCallCost(cr, acc), 10);
	}

};

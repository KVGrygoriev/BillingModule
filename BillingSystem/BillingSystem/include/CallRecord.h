#pragma once

#include "Global.h"
#include "Account.h"
#include "PhoneNumber.h"

namespace BillingModule
{
	class CallRecord
	{
	public:
		PhoneNumber m_AccountNumber;
		PhoneNumber m_Interlocutors;
		Timestamp	m_CallStarted;
		Timestamp	m_CallFinished;

	public:
		CallRecord();
		CallRecord(const PhoneNumber & _AccountNumber, const PhoneNumber & _Interlocutors, const Timestamp & _CallStarted, const Timestamp & _CallFinished);
		~CallRecord();

		bool IsValid();
		void Print();
	};
}
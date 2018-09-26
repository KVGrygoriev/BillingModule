
#include "CallRecord.h"

using namespace BillingModule;

CallRecord::CallRecord() : m_AccountNumber()
						,m_Interlocutors()
						,m_CallStarted()
						,m_CallFinished()
{
}

CallRecord::CallRecord(const PhoneNumber & _AccountNumber, const PhoneNumber & _Interlocutors, const Timestamp & _CallStarted, const Timestamp & _CallFinished) : m_AccountNumber(_AccountNumber)
																																						,m_Interlocutors(_Interlocutors)
																																						,m_CallStarted(_CallStarted)
																																						,m_CallFinished(_CallFinished)
{
}

CallRecord::~CallRecord()
{
}

bool CallRecord::IsValid()
{
	if (m_AccountNumber.IsValid() 
		&& m_Interlocutors.IsValid() 
		&& m_CallStarted.IsValid()
		&& m_CallFinished.IsValid()
		&& CommonUtils::GetCallDuration(m_CallStarted.GetTimestamp(), m_CallFinished.GetTimestamp()) < 0)
		return true;

	return false;
}

void CallRecord::Print()
{
	std::cout << "Account " << m_AccountNumber.m_Number << std::endl;

	std::cout << "Interlocutors " << m_Interlocutors.m_Number << std::endl;

	std::cout << "Call Started Time ";
	m_CallStarted.Print();
	std::cout << std::endl;
	
	std::cout << "Call End Time ";
	m_CallFinished.Print();
	std::cout << std::endl << std::endl;
}
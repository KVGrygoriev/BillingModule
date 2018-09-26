#include "ReckoningModule.h"

using namespace BillingModule;
using namespace std;

ReckoningModule::ReckoningModule()
{
	m_IsInited = false;
}

ReckoningModule::~ReckoningModule()
{
}

bool ReckoningModule::InitReckoningModule(BillingValues _BillingValues)
{
	m_BillingValues = _BillingValues;

	m_IsInited = true;

	return true;
}

bool ReckoningModule::IsInited() const
{
	return m_IsInited;
}

unsigned int ReckoningModule::GetCallCost(const unique_ptr<CallRecord> & _CallRecord, shared_ptr<Account> & _Acc) const
{
	int payment = 0;
	int64_t callDurationInSeconds = 0;
	
	callDurationInSeconds = CommonUtils::GetCallDuration(_CallRecord->m_CallFinished.GetTimestamp(), _CallRecord->m_CallStarted.GetTimestamp());

	payment += m_BillingValues.m_ConnectionCost;

	if (_CallRecord->m_CallStarted.IsWeekend() && m_BillingValues.m_FreeTimeInEachWeekendCall.IsValid())
	{
		callDurationInSeconds -= m_BillingValues.m_FreeTimeInEachWeekendCall.GetTimestampInSeconds();

		if (callDurationInSeconds <= 0)
			return payment;
	}
	

	if (_CallRecord->m_Interlocutors.IsOwnNetwork())
	{
		bool IsGoneMoreThanNDays = CommonUtils::IsGoneMoreThanNDays(_CallRecord->m_CallStarted.GetTimestamp(), _Acc->m_RefillDate.GetTimestamp(), (size_t)m_BillingValues.m_FreeTimeExpiryPeriod);
		
		if (!IsGoneMoreThanNDays)
		{
			unsigned int freeTimeLeft = _Acc->m_FreeTimeLeft.GetTimestampInSeconds();

			if (callDurationInSeconds >= freeTimeLeft)
			{
				callDurationInSeconds -= freeTimeLeft;
				freeTimeLeft = 0;
				_Acc->m_FreeTimeLeft.SetTimestampInSeconds(freeTimeLeft);
			}
			
			if (callDurationInSeconds < freeTimeLeft)
			{
				freeTimeLeft -= (unsigned int)callDurationInSeconds;
				_Acc->m_FreeTimeLeft.SetTimestampInSeconds(freeTimeLeft);
				return payment;
			}
		}
	}
	

	int startMonetizationTime = m_BillingValues.m_StartMonetizationTime.GetTimestampInSeconds();

	int callDurationInFullMinutes = (int)(callDurationInSeconds / 60);
	int callDurationSecondsLeft = (int)(callDurationInSeconds % 60);

	int paidMinutes = callDurationInFullMinutes;

	if (callDurationSecondsLeft > startMonetizationTime)
		++paidMinutes;

	if (_CallRecord->m_Interlocutors.IsOwnNetwork())
		payment += paidMinutes * m_BillingValues.m_CostInsideNetwork;
	else
		payment += paidMinutes * m_BillingValues.m_CostOutsideNetwork;
	
	return payment;
}
#pragma once

#include "Global.h"
#include "Timestamp.h"

namespace BillingModule
{
	class BillingValues
	{
		public:
			unsigned int m_ConnectionCost;
			unsigned int m_CostInsideNetwork;
			unsigned int m_CostOutsideNetwork;
			unsigned int m_FreeTimeExpiryPeriod;

			Timestamp m_FreeTimeInNetwork;
			Timestamp m_FreeTimeInEachWeekendCall;
			Timestamp m_StartMonetizationTime;
			
	public:
		BillingValues()
		{
			m_ConnectionCost = m_CostInsideNetwork = m_CostOutsideNetwork = m_FreeTimeExpiryPeriod = 0;
			m_FreeTimeInNetwork = m_FreeTimeInEachWeekendCall = m_StartMonetizationTime = Timestamp();
		}
	};
}
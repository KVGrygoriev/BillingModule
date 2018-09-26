#pragma once 

#include "Global.h"
#include "BillingValues.h"
#include "CallRecord.h"

namespace BillingModule
{
	class ReckoningModule
	{
	private:
		BillingValues	m_BillingValues;
		bool			m_IsInited;

	public:
		ReckoningModule();
		~ReckoningModule();

		bool InitReckoningModule(BillingValues _BillingValues);

		bool IsInited() const;

		unsigned int GetCallCost(const std::unique_ptr<CallRecord> & _CallRecord, std::shared_ptr<Account> & _Acc) const;
		
	};
}
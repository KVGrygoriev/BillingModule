#pragma once

#include "Global.h"
#include "CallRecord.h"
#include "ReckoningModule.h"

namespace BillingModule
{
	typedef std::shared_ptr<Account> SharedPtrAccount;
	typedef std::unique_ptr<CallRecord> UniquePtrCallRecord;
	typedef std::pair<std::string, SharedPtrAccount> PhoneNumberAndSPtrAccount;
	typedef std::pair<std::string, UniquePtrCallRecord> PhoneNumberAndUPtrCallRecord;

	class ICallRecordManager
	{
	protected:
		std::map<std::string, SharedPtrAccount> m_AccountHolder;
		std::multimap<std::string, UniquePtrCallRecord> m_CrHolder;

		ReckoningModule m_ReckoningModule;

	public:
		ICallRecordManager()
		{};

		virtual ~ICallRecordManager()
		{};

		virtual bool InitReckoningModule(BillingValues _BillingValues)
		{
			return m_ReckoningModule.InitReckoningModule(_BillingValues);
		};

		virtual bool BillPlease()
		{
			if (!m_ReckoningModule.IsInited())
			{
				std::cout << "Error. ReckoningModule not inited." << std::endl;
				return false;
			}

			std::multimap<std::string, UniquePtrCallRecord>::const_iterator callRecordIt = m_CrHolder.begin();
			std::map<std::string, SharedPtrAccount>::iterator accIt;
			unsigned int callCost;

			for (; callRecordIt != m_CrHolder.end(); ++callRecordIt)
			{
				accIt = m_AccountHolder.find(callRecordIt->first);
				if (accIt == m_AccountHolder.end())
				{
					std::cout << "Warning. Account doesn't exist. Skip it." << std::endl;
					continue;
				}
				
				callCost =  m_ReckoningModule.GetCallCost(callRecordIt->second, accIt->second);
				std::cout << "Telephone conversation " << callRecordIt->second->m_AccountNumber.m_Number << " - "<< callRecordIt->second->m_Interlocutors.m_Number << " cost " << callCost << " cents" << std::endl;
			}
			
			return true;
		};

		virtual bool ImportData() = 0;
		virtual bool ExportData() = 0;
	};
}
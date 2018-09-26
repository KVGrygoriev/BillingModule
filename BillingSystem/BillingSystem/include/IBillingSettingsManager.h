#pragma once

#include "Global.h"
#include "BillingValues.h"

namespace BillingModule
{
	class IBillingSettingsManager
	{
	protected:
		bool m_isInitedSuccessfully;

		BillingValues m_BillingValues;

		std::vector<std::string> m_OwnNetworkCodes;


	protected:
		virtual bool LoadSettings() = 0;

	public:
		IBillingSettingsManager()
		{
			m_isInitedSuccessfully = false;
		}

		virtual ~IBillingSettingsManager()
		{};

		bool IsInitedSuccessfully() const
		{
			return m_isInitedSuccessfully;
		};

		BillingValues GetBillingValues() const
		{
			return m_BillingValues;
		};

		std::vector<std::string> GetOwnNetworkCodes() const
		{
			return m_OwnNetworkCodes;
		};
	};
}
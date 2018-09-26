#pragma once

#include "IBillingSettingsManager.h"
#include "CsvFilesHolder.h"

namespace BillingModule
{
	class CsvBillingSettingsManager : public IBillingSettingsManager
	{
	private:
		CsvFilesHolder m_CsvFilesHolder;

		static const char		m_Delimiter = '=';
		static const char		m_StrDelimiter = ';';

	private:
		CsvBillingSettingsManager();

		virtual bool LoadSettings();

		void ParseLineAndSetValue(const std::string & _cfgLine);


	public:
		~CsvBillingSettingsManager();

		static CsvBillingSettingsManager & GetInstance();

		CsvFilesHolder GetCsvFilesHolder() const;
	};
}
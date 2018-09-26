#pragma once

#include "Global.h"
#include "ICallRecordManager.h"
#include "CsvFilesHolder.h"

namespace BillingModule
{
	class CsvCallRecordManager : public ICallRecordManager
	{
	private:
		enum LogColumns
		{
			CALL_STARTED = 0,
			CALL_FINISHED,
			INTERLOCUTORS,
			ACC_PHONE_NUMBER,
			LAST_LOG_ROW,
		};

		enum AccInfoColumns
		{
			PHONE_NUMBER = 0,
			FREE_TIME_LEFT,
			REFILL_DATE,
			LAST_ACC_ROW,
		};

		static const char m_CsvDelimiter = ',';

		CsvFilesHolder m_CsvFilesHolder;

	public:
		CsvCallRecordManager(CsvFilesHolder _CsvFilesHolder);
		virtual ~CsvCallRecordManager();

		virtual bool ImportData();
		virtual bool ExportData();

	private:
		bool ImportAccountsInfoFromCsv();
		bool ExportAccountsInfoToCsv();

		bool ImportLogsFromCsv();

		void FillCallRecordsHolder(const std::string & _csvLine);
		void FillAccountHolder(const std::string & _csvLine);

		size_t FillCallRecord(LogColumns _rowIndex, const std::string & value, UniquePtrCallRecord & _src);
		size_t FillAccount(AccInfoColumns _rowIndex, const std::string & value, SharedPtrAccount & _src);
	};
}
#include "CsvCallRecordManager.h"
#include "CallRecord.h"

using namespace std;
using namespace BillingModule;

CsvCallRecordManager::CsvCallRecordManager(CsvFilesHolder _CsvFilesHolder) : m_CsvFilesHolder(_CsvFilesHolder)
{
}

CsvCallRecordManager::~CsvCallRecordManager()
{
}

bool CsvCallRecordManager::ImportData()
{
	bool accInfo = ImportAccountsInfoFromCsv();
	bool logs = ImportLogsFromCsv();

	if (!accInfo)
	{
		cout << "Error. Account info doesn't found" << endl;
		exit(EXIT_FAILURE);
	}

	if (!logs)
		cout << "Warning. Incoming logs doesn't found" << endl;

	return accInfo && logs;
}

bool CsvCallRecordManager::ExportData()
{
	bool accInfo = ExportAccountsInfoToCsv();

	if (!accInfo)
		cout << "Warning. Account info was not wrote to file" << endl;

	return accInfo;
}

bool CsvCallRecordManager::ImportLogsFromCsv()
{
	string line;

	ifstream inFile(m_CsvFilesHolder.m_IncomingLogFile);

	if (!inFile.is_open())
		return false;
	
	while (getline(inFile, line))
		FillCallRecordsHolder(line);

	return true;
}

bool CsvCallRecordManager::ImportAccountsInfoFromCsv()
{
	string line;
	
	ifstream inFile(m_CsvFilesHolder.m_IncomingAccInfoFile);

	if (!inFile.is_open())
		return false;
	
	while (getline(inFile, line))
		FillAccountHolder(line);

	inFile.close();

	return true;
}

bool CsvCallRecordManager::ExportAccountsInfoToCsv()
{
	ofstream outFile(m_CsvFilesHolder.m_OutcomingAccInfoFile);

	if (!outFile.is_open())
		return false;

	std::map<std::string, SharedPtrAccount>::const_iterator it = m_AccountHolder.begin();

	for (;it != m_AccountHolder.end(); ++it)
		outFile << it->second->m_Number.m_Number << "," << it->second->m_FreeTimeLeft.TimeToStr() << "," << it->second->m_RefillDate.DateToStr() << endl;

	outFile.close();

	return true;
}

void CsvCallRecordManager::FillAccountHolder(const string & _csvLine)
{
	string value;
	AccInfoColumns rowIndex = PHONE_NUMBER;
	
	SharedPtrAccount acc = make_shared<Account>(Account());

	size_t startPos = 0, delPos = _csvLine.find(m_CsvDelimiter);
	
	while (delPos != string::npos || rowIndex < LAST_ACC_ROW)
	{
		value = _csvLine.substr(startPos, delPos - startPos);
		rowIndex = (AccInfoColumns)FillAccount(rowIndex, value, acc);
		
		startPos = delPos + sizeof(m_CsvDelimiter);

		delPos = _csvLine.find(m_CsvDelimiter, startPos);

		if (delPos == string::npos && startPos != _csvLine.length())
		{
			value = _csvLine.substr(startPos);
			rowIndex = (AccInfoColumns)FillAccount(rowIndex, value, acc);
		}
	}
		
	if (acc->IsValid())
	{	
		m_AccountHolder.insert(PhoneNumberAndSPtrAccount(acc->m_Number.m_Number, move(acc)));
	}
	else
	{
		cout << "Warning. Invalid entry: " << endl;
		acc->Print();
	}
}

void CsvCallRecordManager::FillCallRecordsHolder(const string & _csvLine)
{
	string value;
	LogColumns rowIndex = CALL_STARTED;
	
	UniquePtrCallRecord cr(new CallRecord());
	
	size_t startPos = 0, delPos = _csvLine.find(m_CsvDelimiter);

	while (delPos != string::npos || rowIndex < LAST_LOG_ROW)
	{
		value = _csvLine.substr(startPos, delPos - startPos);
		rowIndex = (LogColumns)FillCallRecord(rowIndex, value, cr);
		
		startPos = delPos + sizeof(m_CsvDelimiter);

		delPos = _csvLine.find(m_CsvDelimiter, startPos);

		if (delPos == string::npos && startPos != _csvLine.length())
		{
			value = _csvLine.substr(startPos);
			rowIndex = (LogColumns)FillCallRecord(rowIndex, value, cr);
		}
	}

	if (cr->IsValid())
	{	
		m_CrHolder.insert(PhoneNumberAndUPtrCallRecord(cr->m_AccountNumber.m_Number, move(cr)));
	}
	else
	{
		cout << "Warning. Invalid entry: " << endl;
		cr->Print();
	}
}

size_t CsvCallRecordManager::FillCallRecord(LogColumns _rowIndex, const string & value, UniquePtrCallRecord & _src)
{
	switch(_rowIndex)
	{
		case CALL_STARTED:
			_src->m_CallStarted.DateTimeFromStr(value);
			break;

		case CALL_FINISHED:
			_src->m_CallFinished.DateTimeFromStr(value);
			break;

		case INTERLOCUTORS:
			_src->m_Interlocutors = value;
			break;

		case ACC_PHONE_NUMBER:
			_src->m_AccountNumber.m_Number = value;
			break;

		default: 
			break;
	}

	return _rowIndex + 1;
}

size_t CsvCallRecordManager::FillAccount(AccInfoColumns _rowIndex, const std::string & value, SharedPtrAccount & _src)
{
	switch(_rowIndex)
	{
		case PHONE_NUMBER:
			_src->m_Number = value;
			break;

		case FREE_TIME_LEFT:
			_src->m_FreeTimeLeft.TimeFromStr(value);
			break;

		case REFILL_DATE:
			_src->m_RefillDate.DateFromStr(value);
			break;

		default: 
			break;
	}

	return _rowIndex + 1;
}

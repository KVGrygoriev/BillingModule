#include "CsvBillingSettingsManager.h"
#include "CommonUtils.h"

using namespace BillingModule;
using namespace std;

CsvBillingSettingsManager & CsvBillingSettingsManager::GetInstance()
{
	static CsvBillingSettingsManager billingSettingsManager;

	return billingSettingsManager;
}

CsvBillingSettingsManager::CsvBillingSettingsManager()
{
	m_isInitedSuccessfully = LoadSettings();
}

CsvBillingSettingsManager::~CsvBillingSettingsManager()
{
}

bool CsvBillingSettingsManager::LoadSettings()
{
	string line;

	ifstream inFile(CFG_BILLING_SETTINGS);

	if (!inFile.is_open())
		return false;
	
	while (getline(inFile, line))
	{
		#ifdef __linux__
		line.erase(std::remove(line.begin(), line.end(), '\r'), line.end());
		#endif

		ParseLineAndSetValue(line);
	}

	return true;
}

void CsvBillingSettingsManager::ParseLineAndSetValue(const string & _cfgLine)
{
	if (_cfgLine.empty())
		return;

	size_t delPos = _cfgLine.find(m_Delimiter);

	if (delPos == string::npos)
	{
		cout << "Error. Wrong setting format" << endl;
		return;
	}

	string key = _cfgLine.substr(0, delPos);
	string value = _cfgLine.substr(delPos + sizeof(m_Delimiter));

	
	if (key == CFG_CONNECTION_COST)
		m_BillingValues.m_ConnectionCost = (unsigned int)CommonUtils::StrToInt64((char*)value.c_str());

	if (key == CFG_COST_INSIDE_NETWORK_CALLS)
		m_BillingValues.m_CostInsideNetwork = (unsigned int)CommonUtils::StrToInt64((char*)value.c_str());

	if (key == CFG_COST_OUTSIDE_NETWORK_CALLS)
		m_BillingValues.m_CostOutsideNetwork = (unsigned int)CommonUtils::StrToInt64((char*)value.c_str());
		
	if (key == CFG_OWN_OPERATOR_CODES && !value.empty())
	{
		size_t startStrPos = 0, strDelimiterPos = value.find(m_StrDelimiter);

		while(strDelimiterPos != std::string::npos)
		{
			m_OwnNetworkCodes.push_back(value.substr(startStrPos, OPERATOR_CODE_LENGTH));

			startStrPos = strDelimiterPos + sizeof(m_StrDelimiter);
			strDelimiterPos = value.find(m_StrDelimiter, startStrPos);

			if (strDelimiterPos == string::npos && startStrPos != value.length())
				m_OwnNetworkCodes.push_back(value.substr(startStrPos));
		}	
	}
	
	if (key == CFG_FREE_TIME_IN_NETWORK)
		m_BillingValues.m_FreeTimeInNetwork.TimeFromStr(value);

	if (key == CFG_FREE_TIME_IN_EACH_WEEKEND_CALL)
		m_BillingValues.m_FreeTimeInEachWeekendCall.TimeFromStr(value);

	if (key == CFG_MONETIZATION_TIME)
		m_BillingValues.m_StartMonetizationTime.TimeFromStr(value);

	if (key == CFG_FREE_TIME_EXPIRITY_PERIOD_IN_DAYS)
		m_BillingValues.m_FreeTimeExpiryPeriod = (unsigned int)CommonUtils::StrToInt64((char*)value.c_str());

	if (key == CFG_INCOMING_LOG_FILE)
		m_CsvFilesHolder.m_IncomingLogFile = value;

	if (key == CFG_INCOMING_ACC_INGO_FILE)
		m_CsvFilesHolder.m_IncomingAccInfoFile = value;

	if (key == CFG_OUTCOMING_ACC_INFO_FILE)
		m_CsvFilesHolder.m_OutcomingAccInfoFile = value;
}

CsvFilesHolder CsvBillingSettingsManager::GetCsvFilesHolder() const
{
	return m_CsvFilesHolder;
}

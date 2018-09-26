#include "PhoneNumber.h"
#include "CsvBillingSettingsManager.h"

using namespace BillingModule;

PhoneNumber::PhoneNumber()
{
	m_Number = "";
}

PhoneNumber::PhoneNumber(const std::string & _number) : m_Number(_number)
{
}

PhoneNumber::~PhoneNumber()
{
}

bool PhoneNumber::IsValid() const
{
	if (m_Number.length() > OPERATOR_CODE_LENGTH)
		return true;

	return false;
}

bool PhoneNumber::IsOwnNetwork() const
{
	std::vector<std::string> codes = CsvBillingSettingsManager::GetInstance().GetOwnNetworkCodes();

	bool result = std::any_of(codes.begin(), codes.end(), [this](const std::string & _code)
	{
		return _code == m_Number.substr(0, OPERATOR_CODE_LENGTH);
	});

	return result;
}

#include "Account.h"

using namespace BillingModule;

Account::Account() : m_Number()
{
}

Account::Account(const PhoneNumber & _Number) : m_Number(_Number)
{
}

Account::Account(const PhoneNumber & _Number, const Timestamp & _FreeTimeLeft, const Timestamp & _RefillDate) : m_Number(_Number)
																												, m_FreeTimeLeft(_FreeTimeLeft)
																												, m_RefillDate(_RefillDate)
{
}

Account::~Account()
{
}

bool Account::IsValid() const
{
	return m_Number.IsValid() && m_FreeTimeLeft.IsValid() && m_RefillDate.IsValid();
}

void Account::Print() const
{
	std::cout << "Account " << m_Number.m_Number << std::endl;

	std::cout << "TimeLeft ";
	m_FreeTimeLeft.Print();
	std::cout << std::endl;

	std::cout << "RefillDate ";
	m_RefillDate.Print();
	std::cout << std::endl;
}
#pragma once

#include "Global.h"
#include "PhoneNumber.h"
#include "Timestamp.h"

namespace BillingModule
{
	class Account
	{
	public:
		PhoneNumber m_Number;
		Timestamp	m_FreeTimeLeft;
		Timestamp	m_RefillDate;

	public:
		Account();
		Account(const PhoneNumber & _Number);
		Account(const PhoneNumber & _Number, const Timestamp & _FreeTimeLeft, const Timestamp & _RefillDate);
		~Account();

		bool IsValid() const;
		void Print() const;
	};
}
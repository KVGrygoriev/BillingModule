#pragma once

#include "Global.h"

namespace BillingModule
{
	class PhoneNumber
	{
	public:
		std::string m_Number;

	public:
		PhoneNumber();
		PhoneNumber(const std::string & _number);
		~PhoneNumber();

		bool IsValid() const;
		bool IsOwnNetwork() const;
	};
}
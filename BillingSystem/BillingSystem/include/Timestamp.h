#pragma once

#include "Global.h"

namespace BillingModule
{
	class Timestamp
	{
	private:
		struct tm m_Timestamp;
		bool	m_IsValid;

	public:
		Timestamp();
		Timestamp(const std::string & _value);
		~Timestamp();

		void TimeFromStr(const std::string & _value);
		void DateFromStr(const std::string & _value);
		void DateTimeFromStr(const std::string & _value);

		std::string TimeToStr() const;
		std::string DateToStr() const;

		struct tm	 GetTimestamp() const;
		unsigned int GetTimestampInSeconds() const;

		void	SetTimestampInSeconds(unsigned int _value);

		bool	IsWeekend() const;
		bool	IsValid() const;
		void	Print() const;
	};
}

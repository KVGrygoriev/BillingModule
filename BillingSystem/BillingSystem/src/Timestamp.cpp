#include "../include/Timestamp.h"

using namespace BillingModule;
using namespace std;

Timestamp::Timestamp()
{
	m_IsValid = true;

	struct tm when = {0};
	m_Timestamp = when;
}

Timestamp::Timestamp(const string & _value)
{
	m_IsValid = true;

	DateTimeFromStr(_value);
}
	
Timestamp::~Timestamp()
{
}

struct tm Timestamp::GetTimestamp() const
{
	return m_Timestamp;
}

unsigned int Timestamp::GetTimestampInSeconds() const
{
	unsigned int inSeconds = m_Timestamp.tm_sec;
	inSeconds += m_Timestamp.tm_min * SEC_IN_MIN;
	inSeconds += m_Timestamp.tm_hour * SEC_IN_MIN * MIN_IN_HOUR;

	return inSeconds;
}

void Timestamp::SetTimestampInSeconds(unsigned int _value)
{
	int hours = _value / MIN_IN_HOUR / SEC_IN_MIN;
	int minutes = _value / SEC_IN_MIN;
	int second = _value % MIN_IN_HOUR % SEC_IN_MIN;

	m_Timestamp.tm_hour = hours;
	m_Timestamp.tm_min = minutes;
	m_Timestamp.tm_sec = second;
}

void Timestamp::TimeFromStr(const std::string & _value)
{
	int hh, mm, ss;
	hh = mm = ss = -1;

	struct tm when = {0};

	sscanf(_value.c_str(), "%d:%d:%d", &hh, &mm, &ss);

	if (hh < 0
		|| mm < 0 
		|| ss < 0)
	{
		m_IsValid = false;
		m_Timestamp = when;

		cout << "Warning: Invalid time" << endl;

		return;
	}
	else
	{
		m_IsValid = true;
	}

	when.tm_hour = hh;
	when.tm_min = mm;
	when.tm_sec = ss;

	m_Timestamp = when;
}

void Timestamp::DateFromStr(const std::string & _value)
{
	int year, month, day;
	year = month = day = -1;
	struct tm when = {0};

	sscanf(_value.c_str(), "%d-%d-%d", &year, &month, &day);

	if (year < 0
		|| month < 0 
		|| day < 0)
	{
		m_IsValid = false;
		m_Timestamp = when;

		cout << "Warning: Invalid date" << endl;

		return;
	}
	else
	{
		m_IsValid = true;
	}
	
	when.tm_year = year;
	when.tm_mon = month;
	when.tm_mday = day;

	m_Timestamp = when;
}

void Timestamp::DateTimeFromStr(const string & _value)
{
	int year, month, day, hh, mm, ss;
	hh = mm = ss = year = month = day = -1;
	struct tm when = {0};

	sscanf(_value.c_str(), "%d-%d-%d_%d:%d:%d", &year, &month, &day, &hh, &mm, &ss);

	if (year < 0
		|| month < 0 
		|| day < 0
		|| hh < 0
		|| mm < 0 
		|| ss < 0)
	{
		m_IsValid = false;
		m_Timestamp = when;

		cout << "Warning: Invalid timestamp" << endl;

		return;
	}
	else
	{
		m_IsValid = true;
	}
	
	when.tm_year = year;
	when.tm_mon = month;
	when.tm_mday = day;

	when.tm_hour = hh;
	when.tm_min = mm;
	when.tm_sec = ss;

	m_Timestamp = when;
}

bool Timestamp::IsValid() const
{
	return m_IsValid;
}

bool Timestamp::IsWeekend() const
{
	struct tm tmp = m_Timestamp;
	tmp.tm_year -= 1900;

	time_t time_temp = mktime(&tmp);
	const tm * time_out = localtime(&time_temp);

	if (time_out->tm_wday == 0 || time_out->tm_wday == 6)
		return true;

	return false;
}

std::string Timestamp::TimeToStr() const
{
	stringstream buffer;

	buffer << (m_Timestamp.tm_hour < 10 ? "0" : "")
		<< m_Timestamp.tm_hour << ":"
		<< (m_Timestamp.tm_min < 10 ? "0" : "")
		<< m_Timestamp.tm_min << ":"
		<< (m_Timestamp.tm_sec < 10 ? "0" : "")
		<< m_Timestamp.tm_sec;

	return buffer.str();
}

std::string Timestamp::DateToStr() const
{
	stringstream buffer;

	buffer << m_Timestamp.tm_year << "-" 
		<< (m_Timestamp.tm_mon < 10 ? "0" : "")
		<< m_Timestamp.tm_mon << "-" 
		<< (m_Timestamp.tm_mday < 10 ? "0" : "")
		<< m_Timestamp.tm_mday;

	return buffer.str();
}

void Timestamp::Print() const
{
	cout << m_Timestamp.tm_year << "-" 
		<< (m_Timestamp.tm_mon < 10 ? "0" : "")
		<< m_Timestamp.tm_mon << "-" 
		<< (m_Timestamp.tm_mday < 10 ? "0" : "")
		<< m_Timestamp.tm_mday << "_" 
		<< (m_Timestamp.tm_hour < 10 ? "0" : "")
		<< m_Timestamp.tm_hour << ":"
		<< (m_Timestamp.tm_min < 10 ? "0" : "")
		<< m_Timestamp.tm_min << ":"
		<< (m_Timestamp.tm_sec < 10 ? "0" : "")
		<< m_Timestamp.tm_sec;
}

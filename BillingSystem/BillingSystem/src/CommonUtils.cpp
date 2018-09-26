#include "CommonUtils.h"

using namespace BillingModule;

int64_t CommonUtils::StrToInt64(char* _Str)
{
#ifdef __linux__
	return atoll(_Str);
#else
	return _atoi64(_Str);	
#endif
}

int64_t CommonUtils::GetDiffBetweenTimeInSeconds(const struct tm _l, const struct tm _r)
{
	struct tm startTimeStruct = _l;
	struct tm endTimeStruct = _r;

	startTimeStruct.tm_year -= 1900;
	endTimeStruct.tm_year -= 1900;

	time_t startTime = mktime(&startTimeStruct);
	time_t endTime = mktime(&endTimeStruct);

	return (int64_t)difftime(startTime, endTime);
}

int64_t CommonUtils::GetCallDuration(const struct tm _CallStartTime, const struct tm _CallFinishedTime)
{
	return GetDiffBetweenTimeInSeconds(_CallStartTime, _CallFinishedTime);
}

bool CommonUtils::IsGoneMoreThanNDays(const struct tm _From, const struct tm _To, size_t _DaysLeft)
{
	int64_t diffInSec = GetDiffBetweenTimeInSeconds(_From, _To);

	int64_t diffInDays = diffInSec / SEC_IN_MIN / MIN_IN_HOUR / HOURS_IN_DAY;

	return (diffInDays > _DaysLeft ? true : false);
}
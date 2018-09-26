#pragma once

#include "Global.h"

namespace BillingModule
{
	namespace CommonUtils
	{
		int64_t StrToInt64(char* _Str);

		int64_t GetDiffBetweenTimeInSeconds(const struct tm _l, const struct tm _r);

		int64_t GetCallDuration(const struct tm _CallStartTime, const struct tm _CallFinishedTime);

		bool IsGoneMoreThanNDays(const struct tm _From, const struct tm _To, size_t _DaysLeft);
	}
}
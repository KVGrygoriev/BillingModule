#pragma once

namespace BillingModule
{
	//config values
	#define CFG_BILLING_SETTINGS					"data/BillingSettings.csv"
	#define CFG_CONNECTION_COST						"Connection_Cost"
	#define CFG_COST_INSIDE_NETWORK_CALLS			"Cost_Inside_Network_Calls"
	#define CFG_COST_OUTSIDE_NETWORK_CALLS			"Cost_Outside_Network_Calls"
	#define CFG_FREE_TIME_IN_NETWORK				"Free_Time_In_Network"
	#define CFG_FREE_TIME_IN_EACH_WEEKEND_CALL		"Free_Time_In_Each_Weekend_Call"
	#define CFG_MONETIZATION_TIME					"Monetization_Time"
	#define CFG_OWN_OPERATOR_CODES					"Home_Operator_Codes"
	#define CFG_FREE_TIME_EXPIRITY_PERIOD_IN_DAYS	"Free_Time_Expiry_Period_In_Days"

	#define CFG_INCOMING_LOG_FILE					"Incoming_Log"

	#define CFG_INCOMING_ACC_INGO_FILE				"Incoming_Account_Info"
	#define CFG_OUTCOMING_ACC_INFO_FILE				"Outcoming_Account_Info"

	#define OPERATOR_CODE_LENGTH 3

	#define SEC_IN_MIN		60
	#define MIN_IN_HOUR		60
	#define HOURS_IN_DAY	24
}
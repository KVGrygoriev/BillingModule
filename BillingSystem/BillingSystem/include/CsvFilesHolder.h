#pragma once

namespace BillingModule
{
	class CsvFilesHolder
	{
		public:
			std::string m_IncomingLogFile;
			std::string m_IncomingAccInfoFile;
			std::string m_OutcomingAccInfoFile;

			CsvFilesHolder()
			{
				m_IncomingLogFile = m_IncomingAccInfoFile = m_OutcomingAccInfoFile = "";
			}
	};
}
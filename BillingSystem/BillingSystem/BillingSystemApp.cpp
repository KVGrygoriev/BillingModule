
#include "CsvBillingSettingsManager.h"
#include "CsvCallRecordManager.h"
#include "CsvFilesHolder.h"

using namespace BillingModule;

int main()
{
	if (!CsvBillingSettingsManager::GetInstance().IsInitedSuccessfully())
	{
		std::cout << "Error. Can't read config file!" << std::endl;
		return EXIT_FAILURE;
	}

	CsvFilesHolder csvFileHolder = CsvBillingSettingsManager::GetInstance().GetCsvFilesHolder();

	std::unique_ptr<ICallRecordManager> callRecordManager(new CsvCallRecordManager(csvFileHolder));
	
	callRecordManager->ImportData();

	callRecordManager->InitReckoningModule(CsvBillingSettingsManager::GetInstance().GetBillingValues());

	callRecordManager->BillPlease();

	callRecordManager->ExportData();

	return EXIT_SUCCESS;
}
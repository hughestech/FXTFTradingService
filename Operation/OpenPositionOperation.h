#if !defined OpenPositionOperation_H
#define OpenPositionOperation_H

#include "../FXTFTradingService/stdafx.h"
#include "../FXTFTradingService/MT4ManagerAPI.h"
#include "../Common/SingletonClass.h"
#include "../Model/OpenPositionModel.h"
#include <vector>

class OpenPositionOperation
{
private:
	CList<OpenPositionModel> mCListOpenPositionModel;

public:
	void ReadConfigFile();

	OpenPositionModel* UserLoginAndBalanceCheck(OpenPositionModel* lOpenPositionModel, CManagerInterface* lMT4ManagerInterface);
	void ReadDataFromCSVFile();
	void WriteDataToCSVFile(OpenPositionModel lOpenPositionModel);
	time_t ConvertDateStringToTime(LPCTSTR vUTCFormatted);
	OpenPositionModel OpenOrder( OpenPositionModel lOpenPositionModel, CManagerInterface* lMT4ManagerInterface);
	void OpenPositionToMT4TradingService(CManagerInterface* lMT4ManagerInterface);
};

#endif
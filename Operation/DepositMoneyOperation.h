#if !defined DepositMoneyOperation_H
#define DepositMoneyOperation_H

#include "../FXTFTradingService/stdafx.h"
#include "../FXTFTradingService/MT4ManagerAPI.h"
#include "../Common/SingletonClass.h"
#include "../Model/DepositMoneyModel.h"
#include <vector>

class DepositMoneyOperation
{
public:
	CList<DepositMoneyModel> mCListDepositMoneyModel;

public:
	DepositMoneyModel* UserLoginCheckAndDepositBalance(DepositMoneyModel* lDepositMoneyModel, CManagerInterface* lMT4ManagerInterface);
	void ReadDataFromCSVFile();
	void DepositMoneyToMT4TradingService(CManagerInterface* lMT4ManagerInterface);
};

#endif
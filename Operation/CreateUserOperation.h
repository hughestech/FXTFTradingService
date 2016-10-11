#if !defined CreateUserOperation_H
#define CreateUserOperation_H

#include "../FXTFTradingService/stdafx.h"
#include "../FXTFTradingService/MT4ManagerAPI.h"
#include "../Common/SingletonClass.h"
#include "../Model/CreateUserModel.h"
#include <vector>

class CreateUserOperation
{
public:
	CList<CreateUserModel> mCListCreateUserModel;

public:
	void CreateUserToMT4TradingService(CManagerInterface* lMT4ManagerInterface);
	CreateUserModel*  CreateNewUserToMT4(CreateUserModel *lCreateUserModel,CManagerInterface* lMT4ManagerInterface);
	void ReadDataFromCSVFile();
};
#endif
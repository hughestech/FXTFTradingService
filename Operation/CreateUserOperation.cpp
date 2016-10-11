#include "../Operation/CreateUserOperation.h"

CreateUserModel* CreateUserOperation::CreateNewUserToMT4(CreateUserModel *lCreateUserModel,CManagerInterface* lMT4ManagerInterface)
{
	int        lReturnErrorStatus =RET_ERROR;
    UserRecord lUserRecord={0};
    CString    lUserLoginID;

	//lUserRecord.login				=NULL;
	strcpy( lUserRecord.name,		lCreateUserModel->getUserName() );
	strcpy( lUserRecord.password,	lCreateUserModel->getUserPassword() );
	strcpy( lUserRecord.group,		lCreateUserModel->getUserGroup() );
	strcpy( lUserRecord.email,		lCreateUserModel->getUserEmail() );
	lUserRecord.leverage			=lCreateUserModel->getUserLeverage();
	lUserRecord.enable				=lCreateUserModel->getUserEnable();
	lUserRecord.send_reports		=lCreateUserModel->getUserSendReports();

    lReturnErrorStatus=lMT4ManagerInterface->UserRecordNew(&lUserRecord);

    if(lReturnErrorStatus!=RET_OK) 
	{ 
		SingletonClass::getInstance()->getFXTFLog()->LogOutLn( lMT4ManagerInterface->ErrorDescription(lReturnErrorStatus) );
		return 0; 
	}
	else
	{
		lUserLoginID.Format("New user login id: '%d' ('%s')",lUserRecord.login,lUserRecord.name);
		SingletonClass::getInstance()->getFXTFLog()->LogOutLn( lUserLoginID );
	}

return lCreateUserModel;

}

void CreateUserOperation::ReadDataFromCSVFile()
{	
	CStdioFile		lCreateUserInputCSVFile("CreateUserInputCSVFile.csv" , CFile::modeRead);
	CString			lCStringLine;
	vector<CString> lCreateUserRowWiseList;                // array of values for one lCStringLine only

    while ( lCreateUserInputCSVFile.ReadString(lCStringLine) )      // get next lCStringLine in file
    {
        lCreateUserRowWiseList.clear();

        TCHAR * lGetLenght = lCStringLine.GetBuffer( lCStringLine.GetLength() );
        TCHAR * lCharToken = _tcstok( lGetLenght, _T(",") );
        while( lCharToken != NULL )
        {
           lCreateUserRowWiseList.push_back(CString(lCharToken));
           lCharToken = _tcstok( NULL, _T(",") );
        }

        lCStringLine.ReleaseBuffer();
		CreateUserModel lCreateUserModel = CreateUserModel();
		try
		{
			if(lCreateUserRowWiseList[0])
			{
				lCreateUserModel.setUserName(lCreateUserRowWiseList[0]);
			}
			else
			{
				lCreateUserModel.setUserName(0);
			}

			if(lCreateUserRowWiseList[1])
			{
				lCreateUserModel.setUserPassword(lCreateUserRowWiseList[1]);
			}
			else
			{
				lCreateUserModel.setUserPassword(0);
			}

			if(lCreateUserRowWiseList[2])
			{
				lCreateUserModel.setUserGroup(lCreateUserRowWiseList[2]);
			}
			else
			{
				lCreateUserModel.setUserGroup(0);
			}

			if(lCreateUserRowWiseList[3])
			{
				lCreateUserModel.setUserEmail(lCreateUserRowWiseList[3]);
			}
			else
			{
				lCreateUserModel.setUserEmail(0);
			}

			if(lCreateUserRowWiseList[4])
			{
				lCreateUserModel.setUserLeverage(atoi(lCreateUserRowWiseList[4]));
			}
			else
			{
				lCreateUserModel.setUserLeverage(0);
			}

			if(lCreateUserRowWiseList[5])
			{
				lCreateUserModel.setUserEnable(lCreateUserRowWiseList[5]);
			}
			else
			{
				lCreateUserModel.setUserEnable(0);
			}

			if(lCreateUserRowWiseList[6])
			{
				lCreateUserModel.setUserSendReports(lCreateUserRowWiseList[6]);
			}
			else
			{
				lCreateUserModel.setUserSendReports(0);
			}
		}
		catch( std::exception aExceltion)
		{
			SingletonClass::getInstance()->getFXTFLog()->LogOutLn( lCreateUserModel.getUserName() + " -> Data read problem from input CSV files");
		}
		mCListCreateUserModel.AddTail(lCreateUserModel);
    }
}

void CreateUserOperation::CreateUserToMT4TradingService(CManagerInterface* lMT4ManagerInterface)
{
	ReadDataFromCSVFile();

	POSITION lPositionCList = mCListCreateUserModel.GetHeadPosition();
	for(int i = 0; i < mCListCreateUserModel.GetCount(); i++)
	{
		if (lMT4ManagerInterface->IsConnected())
		{
			CreateUserModel *lCreateUserModel = &(CreateUserModel&)mCListCreateUserModel.GetAt(lPositionCList);
			lCreateUserModel = CreateNewUserToMT4(lCreateUserModel,lMT4ManagerInterface);

			Sleep(100);
			mCListCreateUserModel.GetNext(lPositionCList);
		}else
		{
			SingletonClass::getInstance()->getFXTFLog()->LogOutLn( "***********MT4 Connection is failed going to reconnect ");
			//ConnectWithMT4Server();
			i--;
		}
	}
}
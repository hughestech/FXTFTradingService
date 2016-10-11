#include "DepositMoneyOperation.h"

DepositMoneyModel* DepositMoneyOperation::UserLoginCheckAndDepositBalance(DepositMoneyModel* lDepositMoneyModel, CManagerInterface* lMT4ManagerInterface)
{
	UserRecord	*lUserRecord = NULL;
	int			lUserLoginID = lDepositMoneyModel->getMT4LoginID();
	int			lTotal		 = 1;
	lUserRecord	= lMT4ManagerInterface->UserRecordsRequest(&lUserLoginID, &lTotal);
	
	TradeTransInfo lTradeTransDeposit = {0};

	CString lMT4LoginID = ""; lMT4LoginID.Format("%d", lDepositMoneyModel->getMT4LoginID() );

	if(lUserRecord != NULL )
	{
		lTradeTransDeposit.orderby	= lDepositMoneyModel->getMT4LoginID();
		lTradeTransDeposit.cmd		= OP_BALANCE;
		lTradeTransDeposit.type		= TT_BR_BALANCE;
		lTradeTransDeposit.price	= lDepositMoneyModel->getDepositBalance();
		strcpy( lTradeTransDeposit.comment, "Transfer from Kousoku to MT4" );
		CString lCurrentBalance = ""; lCurrentBalance.Format("%f", lUserRecord->balance);

		int lReturnTradeTransactionMessage = lMT4ManagerInterface->TradeTransaction(&lTradeTransDeposit);

		if( lReturnTradeTransactionMessage != RET_OK )
		{
			SingletonClass::getInstance()->getFXTFLog()->LogOutLn( lMT4LoginID + " -> MT4 Login ID is not valid Or negative balance" + lMT4ManagerInterface->ErrorDescription(lReturnTradeTransactionMessage) );
		}
		else
		{
			SingletonClass::getInstance()->getFXTFLog()->LogOutLn( lMT4LoginID + " -> MT4 Login ID is valid. Current Balance: " + lCurrentBalance );
		}
	}
	else
	{
		SingletonClass::getInstance()->getFXTFLog()->LogOutLn( lMT4LoginID + " -> MT4 Login ID is not valid");
	}

	return lDepositMoneyModel;
}

void DepositMoneyOperation::ReadDataFromCSVFile()
{	
	CStdioFile		lInputCSVFile("InputUserData_DepositMoney.csv" , CFile::modeRead);
	CString			lCStringLine;
	vector<CString> lVecRowWiseStringList;                // array of values for one lCStringLine only

    while ( lInputCSVFile.ReadString(lCStringLine) )      // get next lCStringLine in file
    {
        lVecRowWiseStringList.clear();

        TCHAR * lGetLenght = lCStringLine.GetBuffer( lCStringLine.GetLength() );
        TCHAR * lCharToken = _tcstok( lGetLenght, _T(",") );
        while( lCharToken != NULL )
        {
           lVecRowWiseStringList.push_back(CString(lCharToken));
           lCharToken = _tcstok( NULL, _T(",") );
        }

        lCStringLine.ReleaseBuffer();
		DepositMoneyModel lDepositMoneyModel = DepositMoneyModel();
		try
		{
			//@0. MT4LoginID  ( MT4LoginID get it from CRM DataBase )
			if(lVecRowWiseStringList[0])
			{
				lDepositMoneyModel.setMT4LoginID(atoi(lVecRowWiseStringList[0]));
			}
			else
			{
				lDepositMoneyModel.setMT4LoginID(0);
			}

			if(lVecRowWiseStringList[1])
			{
				lDepositMoneyModel.setDepositBalance(atof(lVecRowWiseStringList[1]));
			}
			else
			{
				lDepositMoneyModel.setDepositBalance(0);
			}
		}
		catch( std::exception aExceltion)
		{
			SingletonClass::getInstance()->getFXTFLog()->LogOutLn( lDepositMoneyModel.getMT4LoginID() + " -> Data read problem from input CSV files");
		}
		mCListDepositMoneyModel.AddTail(lDepositMoneyModel);
    }
}

void DepositMoneyOperation::DepositMoneyToMT4TradingService(CManagerInterface* lMT4ManagerInterface)
{
	ReadDataFromCSVFile();

	POSITION lPositionCList = mCListDepositMoneyModel.GetHeadPosition();
	for(int i = 0; i < mCListDepositMoneyModel.GetCount(); i++)
	{
		if (lMT4ManagerInterface->IsConnected())
		{
			DepositMoneyModel *lDepositMoneyModel = &(DepositMoneyModel&)mCListDepositMoneyModel.GetAt(lPositionCList);
			lDepositMoneyModel = UserLoginCheckAndDepositBalance(lDepositMoneyModel,lMT4ManagerInterface);

			Sleep(100);
			mCListDepositMoneyModel.GetNext(lPositionCList);
		}else
		{
			SingletonClass::getInstance()->getFXTFLog()->LogOutLn( "***********MT4 Connection is failed going to reconnect ");
			//ConnectWithMT4Server();
			i--;
		}
	}

}


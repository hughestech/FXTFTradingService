#include "OpenPositionOperation.h"

OpenPositionModel* OpenPositionOperation::UserLoginAndBalanceCheck(OpenPositionModel* lOpenPositionModel, CManagerInterface* lMT4ManagerInterface)
{
	UserRecord	*lUserRecord = NULL;
	int			lUserLoginID = lOpenPositionModel->getMT4LoginID();
	int			lTotal		 = 1;
	lUserRecord	= lMT4ManagerInterface->UserRecordsRequest(&lUserLoginID, &lTotal);


	CString lMT4LoginID = ""; lMT4LoginID.Format("%d", lOpenPositionModel->getMT4LoginID() );
	
	if(lUserRecord != NULL && lUserRecord->balance > 0 )
	{
		SingletonClass::getInstance()->getFXTFLog()->LogOutLn( lMT4LoginID + " -> MT4 Login ID is valid and balance doesn't empty.");

		CString lAccountGroup( lUserRecord->group );
		if( lAccountGroup.Find("-cd") != -1 )   // if match (-cd) then return +ve value otherwise return -1;
		{
			lOpenPositionModel->setAccountGroup(1); // countdown = 1
		}
		else 
		{
			lOpenPositionModel->setAccountGroup(0); // streaming = 0; 
		}
	}
	else
	{
		SingletonClass::getInstance()->getFXTFLog()->LogOutLn( lMT4LoginID + " -> MT4 Login ID is not valid Or negative balance");
	}

	return lOpenPositionModel;
}

void OpenPositionOperation::ReadDataFromCSVFile()
{	
	CStdioFile		lInputCSVFile("..\\FXTFTradingService\\InputUserData.csv" , CFile::modeRead);
	CString			lCStringLine;
	vector<CString> lVecRowWiseStringList;                // array of values for one lCStringLine only

    while ( lInputCSVFile.ReadString(lCStringLine) )      // get next lCStringLine in file
    {
        lVecRowWiseStringList.clear();

		/// Alternative Ways /
		///CString lInputStringLine = _T("one++three+four");
		//int nTokenPos = 0;
		//CString lStringToken = lInputStringLine.Tokenize(_T("+"), nTokenPos);
		//
		//while (!lStringToken.IsEmpty())
		//{
		//    // .....do something with lStringToken....
		//	lStringToken = lInputStringLine.Tokenize(_T("+"), nTokenPos);
		//}

        TCHAR * lGetLenght = lCStringLine.GetBuffer( lCStringLine.GetLength() );
        TCHAR * lCharToken = _tcstok( lGetLenght, _T(",") );
        while( lCharToken != NULL )
        {
           lVecRowWiseStringList.push_back(CString(lCharToken));
           lCharToken = _tcstok( NULL, _T(",") );
        }

        lCStringLine.ReleaseBuffer();
		OpenPositionModel lOpenPositionModel = OpenPositionModel();
		try
		{
			//　0. MT4LoginID  ( MT4LoginID get it from TechJini )
			if(lVecRowWiseStringList[0])
			{
				lOpenPositionModel.setMT4LoginID(atoi(lVecRowWiseStringList[0]));
			}
			else
			{
				lOpenPositionModel.setMT4LoginID(0);
			}
			// 1. 顧客/FXTFID
			if(lVecRowWiseStringList[1])
			{
				lOpenPositionModel.setFXTFID(lVecRowWiseStringList[1]);
			}
			else
			{
				lOpenPositionModel.setFXTFID("");
			}
			//2. 通貨ペア/Symbol
			if (lVecRowWiseStringList[2])
			{
				lOpenPositionModel.setSymbol(lVecRowWiseStringList[2]);
			}
			else
			{
				lOpenPositionModel.setSymbol("");
			}
			// 3. 取引数量/Volume 
			if(lVecRowWiseStringList[3])
			{
				lOpenPositionModel.setVolume(atoi(lVecRowWiseStringList[3]));
			}
			else
			{
				lOpenPositionModel.setVolume(0);
			}
			// 4. チケット番号/TicketNumber (KouSokuTIcketID)
			if(lVecRowWiseStringList[4])
			{
				lOpenPositionModel.setTicketID(lVecRowWiseStringList[4]);
			}
			else
			{
				lOpenPositionModel.setTicketID("");
			}
			// 5. 買/売/Buy-Sell(CMD) (B/S) 0/1
			if(lVecRowWiseStringList[5])
			{
				lOpenPositionModel.setCMD(lVecRowWiseStringList[5]);
			}
			else
			{
				lOpenPositionModel.setCMD(0);
			}
			// 6. 約定レート/Yakujo/OpenPrice
			if(lVecRowWiseStringList[6])
			{
				lOpenPositionModel.setOpenPrice(atof(lVecRowWiseStringList[6]));
			}
			else
			{
				lOpenPositionModel.setOpenPrice(0);
			}
			// 7. 逆指値注文/Gyaku Shinechumon (Stop/Loss) -> SL
			if(lVecRowWiseStringList[7])
			{
				lOpenPositionModel.setStopLoss(atof(lVecRowWiseStringList[7]));
			}
			else
			{
				lOpenPositionModel.setStopLoss(0);
			}
			// 8. 指値注文/Shinechūmon (Take/Profit) -> TP
			if(lVecRowWiseStringList[8])
			{
				lOpenPositionModel.setTakeProfit(atof(lVecRowWiseStringList[8]));
			}
			else
			{
				lOpenPositionModel.setTakeProfit(0);
			}
			// 9. 成立日時/Seiritsu nichiji (Date) 
			if(lVecRowWiseStringList[9])
			{
				lOpenPositionModel.setOpenTimeDate(lVecRowWiseStringList[9]);
			}
			else
			{
				lOpenPositionModel.setOpenTimeDate("");
			}
			// 10. 成立日時/Seiritsu nichiji (Time)
			if(lVecRowWiseStringList[10])
			{
				lOpenPositionModel.setOpenTimeHour(lVecRowWiseStringList[10]);
			}
			else
			{
				lOpenPositionModel.setOpenTimeHour("");
			}
			// 11. CurrentBalance get it from TechJini
			if(lVecRowWiseStringList[11])
			{
				lOpenPositionModel.setCurrentBalance(lVecRowWiseStringList[11]);
			}
			else
			{
				lOpenPositionModel.setCurrentBalance("");
			}
		}
		catch( std::exception aExceltion)
		{
			SingletonClass::getInstance()->getFXTFLog()->LogOutLn( lOpenPositionModel.getMT4LoginID() + " -> Data read problem from input CSV files");
		}
		mCListOpenPositionModel.AddTail(lOpenPositionModel);
    }
}

void OpenPositionOperation::WriteDataToCSVFile(OpenPositionModel lOpenPositionModel)
{
	TCHAR* pWriteFileName = _T("..\\FXTFTradingService\\OutputUserData.csv");
	CStdioFile lOutputCSVFile;
	if( lOutputCSVFile.Open(pWriteFileName,CFile::modeWrite|CFile::modeNoTruncate) )
	{
		lOutputCSVFile.SeekToEnd();
	}
	else
	{
		AfxMessageBox("File access failed, please check file is open or correct the right path");
	}

	try
	{
		if( to_string(lOpenPositionModel.getMT4LoginID()).c_str() )
		{
			lOutputCSVFile.WriteString(_T( to_string(lOpenPositionModel.getMT4LoginID()).c_str() ));
		}
		else
		{
			lOutputCSVFile.WriteString(_T( "NULL" ));
		}
		lOutputCSVFile.WriteString(_T( "," ));	
		if( lOpenPositionModel.getFXTFID() )
		{
			lOutputCSVFile.WriteString(_T( lOpenPositionModel.getFXTFID() ));
		}
		else
		{
			lOutputCSVFile.WriteString(_T( "NULL" ));
		}	
		lOutputCSVFile.WriteString(_T( "," ));
		if( lOpenPositionModel.getSymbol() )
		{
			lOutputCSVFile.WriteString(_T( lOpenPositionModel.getSymbol() ));
		}
		else
		{
			lOutputCSVFile.WriteString(_T( "NULL" ));
		}	
		lOutputCSVFile.WriteString(_T( "," ));
		
		if( to_string(lOpenPositionModel.getVolume()).c_str() )
		{
			lOutputCSVFile.WriteString(_T( to_string(lOpenPositionModel.getVolume()).c_str() ));
		}
		else
		{
			lOutputCSVFile.WriteString(_T( "NULL" ));
		}	
		lOutputCSVFile.WriteString(_T( "," ));
		if( lOpenPositionModel.getTicketID() )
		{
			lOutputCSVFile.WriteString(_T( lOpenPositionModel.getTicketID() ));
		}
		else
		{
			lOutputCSVFile.WriteString(_T( "NULL" ));
		}	
		lOutputCSVFile.WriteString(_T( "," ));			
		if( lOpenPositionModel.getCMD() )
		{
			lOutputCSVFile.WriteString(_T( lOpenPositionModel.getCMD() ));
		}
		else
		{
			lOutputCSVFile.WriteString(_T( "NULL" ));
		}	
		lOutputCSVFile.WriteString(_T( "," ));			
		if( to_string(lOpenPositionModel.getOpenPrice()).c_str() )
		{
			lOutputCSVFile.WriteString(_T( to_string(lOpenPositionModel.getOpenPrice()).c_str() ));
		}
		else
		{
			lOutputCSVFile.WriteString(_T( "NULL" ));
		}	
		lOutputCSVFile.WriteString(_T( "," ));
		if( to_string(lOpenPositionModel.getStopLoss()).c_str() )
		{
			lOutputCSVFile.WriteString(_T( to_string(lOpenPositionModel.getStopLoss()).c_str() ));
		}
		else
		{
			lOutputCSVFile.WriteString(_T( "NULL" ));
		}	
		lOutputCSVFile.WriteString(_T( "," ));
		if( to_string(lOpenPositionModel.getTakeProfit()).c_str() )
		{
			lOutputCSVFile.WriteString(_T( to_string(lOpenPositionModel.getTakeProfit()).c_str() ));
		}
		else
		{
			lOutputCSVFile.WriteString(_T( "NULL" ));
		}	
		lOutputCSVFile.WriteString(_T( "," ));
		if( lOpenPositionModel.getOpenTimeDate() )
		{
			lOutputCSVFile.WriteString(_T( lOpenPositionModel.getOpenTimeDate() ));
		}
		else
		{
			lOutputCSVFile.WriteString(_T( "NULL" ));
		}	
		lOutputCSVFile.WriteString(_T( "," ));
		if( lOpenPositionModel.getOpenTimeHour() )
		{
			lOutputCSVFile.WriteString(_T( lOpenPositionModel.getOpenTimeHour() ));
		}
		else
		{
			lOutputCSVFile.WriteString(_T( "NULL" ));
		}	
		lOutputCSVFile.WriteString(_T( "," ));
		if( lOpenPositionModel.getCurrentBalance() )
		{
			lOutputCSVFile.WriteString(_T( lOpenPositionModel.getCurrentBalance() ));
		}
		else
		{
			lOutputCSVFile.WriteString(_T( "NULL" ));
		}	
		lOutputCSVFile.WriteString(_T( "," ));
		if( lOpenPositionModel.getOrderID() >= 0 )
		{
			lOutputCSVFile.WriteString(_T( to_string(lOpenPositionModel.getOrderID()).c_str() ));
		}
		else
		{
			lOutputCSVFile.WriteString(_T( "NULL" ));
		}
		
		lOutputCSVFile.WriteString(_T( "\n" ));
	}
	catch( std::exception aException )
	{
		SingletonClass::getInstance()->getFXTFLog()->LogOutLn( lOpenPositionModel.getMT4LoginID() + " -> Data writing problem into the OutPut CSV files");
	}

	lOutputCSVFile.Close();
}

time_t OpenPositionOperation::ConvertDateStringToTime(LPCTSTR vUTCFormatted)
{
  COleDateTime DateTime;
  time_t TimeT = 0;
  if( DateTime.ParseDateTime( vUTCFormatted ) )
  {
    TimeT = ((double) DateTime * 86400) - 2209161600;
  }
  return TimeT;
}

 OpenPositionModel OpenPositionOperation::OpenOrder( OpenPositionModel lOpenPositionModel, CManagerInterface* lMT4ManagerInterface)
{
   //--- Opening a trade into MT4 Trade Server
   CString lMT4LoginID = ""; lMT4LoginID.Format("%d", lOpenPositionModel.getMT4LoginID() );
   //SingletonClass::getInstance()->getFXTFLog()->LogOutLn( lMT4LoginID + " -> Order opening operation has been processing. KouSoku ID:" + lOpenPositionModel.getTicketID() + "");

   TradeTransInfo info = {0};
   int  lTotal = 1, res = RET_ERROR;

   try
   {
	   info.orderby	= lOpenPositionModel.getMT4LoginID();				// order, order by, login
	   info.type = TT_BR_ORDER_OPEN;								// trade transaction type
	   if( lOpenPositionModel.getCMD() == "B")
	   {
		   info.cmd = 0;
	   }
	   if( lOpenPositionModel.getCMD() == "S" )
	   {
		   info.cmd = 1;
	   }
	   if( lOpenPositionModel.getAccountGroup() == 0 )					 // streaming = 0; 
	   {
		   strcpy(info.symbol, lOpenPositionModel.getSymbol());		 // trade symbol - streaming
	   }
	   if( lOpenPositionModel.getAccountGroup() == 1 )					 // countdown = 1；
	   {
		   strcpy(info.symbol, lOpenPositionModel.getSymbol() + "-cd"); // trade symbol - countdown
	   }
	   //Volume calculation on MT4 API; Streaming (1 lot = 10,000)  MT4 100 = 1   lot
	   if( lOpenPositionModel.getAccountGroup() == 0 )
	   {
		   //int lStreamingLot = 10000/100;
		   info.volume = ( lOpenPositionModel.getVolume() )/100;
	   }
	   //Volume calculation on MT4 API; Countdown (1 lot = 100,000) MT4 100  = 1 lot
	   if( lOpenPositionModel.getAccountGroup() == 1 )
	   {
		   //int lCountdownLot = 100000/1000;
		   info.volume = ( lOpenPositionModel.getVolume() )/1000;
	   }
	   info.price = lOpenPositionModel.getOpenPrice();					// trade price
	   strcpy(info.comment, "KouSoku_" + lOpenPositionModel.getTicketID() );
	   if( lOpenPositionModel.getStopLoss() != 0 )
	   {
		   info.sl = lOpenPositionModel.getStopLoss();					// stoploss
	   }
	   if(lOpenPositionModel.getTakeProfit() != 0)
	   {
		   info.tp = lOpenPositionModel.getTakeProfit();				// takeprofit
	   }
   }
   catch( std::exception aException )
   {
	   CString lLogMessage  = lMT4LoginID + " -> Order opening operation has failed due to in-sufficient information. KouSokuID: " + lOpenPositionModel.getTicketID();
	   SingletonClass::getInstance()->getFXTFLog()->LogOutLn( lLogMessage );
   }

   if( ( res=lMT4ManagerInterface->TradeTransaction(&info) ) != RET_OK )
   {
	   CString lLogMessage = lMT4LoginID + " -> Order opening operation has failed. KouSokuID: " + lOpenPositionModel.getTicketID() + " Reason: " + lMT4ManagerInterface->ErrorDescription(res) ;
	   SingletonClass::getInstance()->getFXTFLog()->LogOutLn( lLogMessage );
   }
   else
   {
	   lOpenPositionModel.setOrderID( info.order );
	   CString lOrderID = ""; lOrderID.Format( "%d", lOpenPositionModel.getOrderID() );
	   SingletonClass::getInstance()->getFXTFLog()->LogOutLn( lMT4LoginID +  " -> Order has been created successfully, KouSokuID: " + lOpenPositionModel.getTicketID() + " OrderID: " +  lOrderID );

	   TradeRecord  *lTradeRecord	= NULL;
	   try{
		   int lOrderID					= info.order;
		   lTradeRecord = lMT4ManagerInterface->TradeRecordsRequest(&lOrderID, &lTotal);
		   //Calculate the Opening hour to UTC fromat and update this info to OpenTrade;
		   CString lInputTime			= lOpenPositionModel.getOpenTimeDate() +" "+ lOpenPositionModel.getOpenTimeHour();
		   lInputTime.Replace("/","-");
		   __time32_t lTargatedTimeUTC	= ConvertDateStringToTime( lInputTime ) + 13*60*60 - 6*60*60;
		   lTradeRecord->open_time		= lTargatedTimeUTC;
	   }
	   catch( std::exception aException )
	   {
		   CString lLogMessage = lMT4LoginID + " -> Order UTC time convertion failed due to mis-calculation. KouSokuID: " + lOpenPositionModel.getTicketID();
		   SingletonClass::getInstance()->getFXTFLog()->LogOutLn( lLogMessage );
	   }

	   int lTradeRecordModifyStatus = lMT4ManagerInterface->AdmTradeRecordModify(lTradeRecord);
	   int lLogin = lOpenPositionModel.getMT4LoginID();
	   
	   if(lTradeRecordModifyStatus == RET_OK)
	   {
	      BalanceDiff *lBalanceDiff = NULL;
	      lBalanceDiff = lMT4ManagerInterface->AdmBalanceCheck(&lLogin, &lTotal); 
	      if( lBalanceDiff )
	      {
			  SingletonClass::getInstance()->getFXTFLog()->LogOutLn("No need to FIX the balance.");
	      }
	      else
	      {
			  int lBalanceFixStatus = lMT4ManagerInterface->AdmBalanceFix(&lLogin, lTotal);
	      }
	      UserRecord *lUserRecord = new UserRecord();
	      lUserRecord=lMT4ManagerInterface->UserRecordsRequest(&lLogin, &lTotal);
	      //SingletonClass::getInstance()->getFXTFLog()->LogOutLn(lUserRecord->balance);
	   }
	   else
	   {
		  CString lLogMessage = lMT4LoginID + "OpenDate modification of this order has been failed. KouSokuID: " + lOpenPositionModel.getTicketID();
	      SingletonClass::getInstance()->getFXTFLog()->LogOutLn( lLogMessage );
	   }
   }

   return lOpenPositionModel;
}

void OpenPositionOperation::OpenPositionToMT4TradingService(CManagerInterface* lMT4ManagerInterface)
{
	ReadDataFromCSVFile();

	POSITION lPositionCList = mCListOpenPositionModel.GetHeadPosition();
	for(int i = 0; i < mCListOpenPositionModel.GetCount(); i++)
	{
		if( lMT4ManagerInterface->IsConnected() )
		{
			OpenPositionModel *lOpenPositionModel = &(OpenPositionModel&)mCListOpenPositionModel.GetAt(lPositionCList);
			lOpenPositionModel = UserLoginAndBalanceCheck(lOpenPositionModel,lMT4ManagerInterface);
			if(lOpenPositionModel!=NULL)
			{
				OpenPositionModel llOpenPositionModel = OpenOrder(*lOpenPositionModel,lMT4ManagerInterface);
				WriteDataToCSVFile(llOpenPositionModel);
			}

			Sleep(1000);
			mCListOpenPositionModel.GetNext(lPositionCList);
		}
		else
		{
			SingletonClass::getInstance()->getFXTFLog()->LogOutLn( "***********MT4 Connection Failed going To Reconnect***********");
			//ConnectAndLoginToMT4Server();
			i--;
		}
	}

}

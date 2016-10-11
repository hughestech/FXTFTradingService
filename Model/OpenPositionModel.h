#if !defined OpenPositionModel_H
#define OpenPositionModel_H

#include "../FXTFTradingService/stdafx.h"
#include "afxdialogex.h"

using namespace std;

class OpenPositionModel
{
private:
	int mMT4LoginID;
	CString mFXTFID;
	CString mTicketID;
	CString mSymbol;
	CString mOpenTimeDate;
	CString mOpenTimeHour;
	double mOpenPrice;
	double mStopLoss;
	double mTakeProfit;
	CString mCMD;
	int mVolume;
	CString mCurrentBalance;
	int mAccountGroup;
	int mOrderID;

public:
	OpenPositionModel();
	~OpenPositionModel();

	int getMT4LoginID(){return mMT4LoginID;}
	void setMT4LoginID(int aMT4LoginID){mMT4LoginID=aMT4LoginID;}
	
	CString getFXTFID(){return mFXTFID;}
	void setFXTFID(CString aFXTFID){mFXTFID=aFXTFID;}
	
	CString getTicketID(){return mTicketID;}
	void setTicketID(CString aTicketID){mTicketID=aTicketID;}
	
	CString getSymbol(){return mSymbol;}
	void setSymbol(CString aSymbol){mSymbol=aSymbol;}

	CString getOpenTimeDate(){return mOpenTimeDate;}
	void setOpenTimeDate(CString aOpenTimeDate){mOpenTimeDate=aOpenTimeDate;}

	CString getOpenTimeHour(){return mOpenTimeHour;}
	void setOpenTimeHour(CString aOpenTimeHour){mOpenTimeHour=aOpenTimeHour;}
	
	double getOpenPrice(){return mOpenPrice;}
	void setOpenPrice(double aOpenPrice){mOpenPrice=aOpenPrice;}
	
	double getStopLoss(){return mStopLoss;}
	void setStopLoss(double aStopLoss){mStopLoss=aStopLoss;}

	double getTakeProfit(){return mTakeProfit;}
	void setTakeProfit(double aTakeProfit){mTakeProfit=aTakeProfit;}

	CString getCMD(){return mCMD;}
	void setCMD(CString aCMD){mCMD=aCMD;}
	
	int getVolume(){return mVolume;}
	void setVolume(int aVolume){mVolume=aVolume;}
	
	CString getCurrentBalance(){return mCurrentBalance;}
	void setCurrentBalance(CString aCurrentBalance){mCurrentBalance=aCurrentBalance;}

	//Account Type streaming = 0; countdown = 1;
	int getAccountGroup(){return mAccountGroup;}
	void setAccountGroup(int aAccountGroup){mAccountGroup=aAccountGroup;}

	int getOrderID(){return mOrderID;}
	void setOrderID(int aOrderID){mOrderID=aOrderID;}
};

#endif
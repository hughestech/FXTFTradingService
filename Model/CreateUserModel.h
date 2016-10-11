#if !defined CreateUserModel_H
#define CreateUserModel_H

#include "../FXTFTradingService/stdafx.h"
#include "../FXTFTradingService/MT4ManagerAPI.h"
#include "../Common/SingletonClass.h"

class CreateUserModel
{
private:
	CString mUserName;
	CString mUserPassword;
	CString mUserGroup;
	CString mUserEmail;
	int     mUserLeverage;
	bool    mUserEnable;
	bool    mUserSendReports;

public:
	CreateUserModel();
	~CreateUserModel();

	CString getUserName(){return mUserName;}
	void setUserName(CString aUserName){ mUserName=aUserName; }

	CString getUserPassword(){return mUserPassword;}
	void setUserPassword(CString aUserPassword){ mUserPassword=aUserPassword; }

	CString getUserGroup(){return mUserGroup;}
	void setUserGroup(CString aUserGroup){ mUserGroup=aUserGroup; }

	CString getUserEmail(){return mUserEmail;}
	void setUserEmail(CString aUserEmail){ mUserEmail=aUserEmail; }

	int getUserLeverage(){return mUserLeverage;}
	void setUserLeverage(int aUserLeverage){ mUserLeverage=aUserLeverage; }

	bool getUserEnable(){return mUserEnable;}
	void setUserEnable(bool aUserEnable){ mUserEnable=aUserEnable; }

	bool getUserSendReports(){return mUserSendReports;}
	void setUserSendReports(bool aUserSendReports){ mUserSendReports=aUserSendReports; }	

};
#endif
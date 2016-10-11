#if !defined MT4ManagerAPIConnection_H
#define MT4ManagerAPIConnection_H

#include "windows.h"
#include "../FXTFTradingService/MT4ManagerAPI.h"
#include "../Common/SingletonClass.h"
#include "../Common/ParseConfigFile.h"
#include "../Common/FXTFLog.h"
#include "../Common/Constant.h"

class MT4ManagerAPIConnection
{
private:
	CManagerFactory mMT4ManagerFactory;

public:
	string mMT4ServerIP;
	string mMT4UserNameID;
	string mMT4UserPassword;

public:
	CManagerInterface* ConnectWithMT4Server();
	void ReadConfigFile();
};


#endif
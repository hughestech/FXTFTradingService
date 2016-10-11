#include "MT4ManagerAPIConnection.h"

CManagerInterface* mMT4ManagerInterface = NULL;

void MT4ManagerAPIConnection::ReadConfigFile()
{
	ParseConfigFile lConfigFileRead(INI_CONF_FILE_NAME);
	mMT4ServerIP		=	lConfigFileRead.Get("MT4",INI_MT4ServerIP,"");
	mMT4UserNameID		=	lConfigFileRead.Get("MT4",INI_MT4UserNameID,"");
	mMT4UserPassword	=	lConfigFileRead.Get("MT4",INI_MT4UserPassword,"");
	SingletonClass::getInstance()->getFXTFLog()->LogOutLn("MT4 Server Access Credential: " + mMT4ServerIP+"  "+mMT4UserNameID+"  "+mMT4UserPassword);
}

CManagerInterface* MT4ManagerAPIConnection::ConnectWithMT4Server()
{
	ReadConfigFile();
	mMT4ManagerFactory = CManagerFactory("mtmanapi.dll");
	if(mMT4ManagerFactory.IsValid() == FALSE || (mMT4ManagerInterface = mMT4ManagerFactory.Create(ManAPIVersion)) == NULL )
	{
		SingletonClass::getInstance()->getFXTFLog()->LogOutLn("Error: Failed to read MT4 (DLL) manager interface.");
	}
	else
	{
		SingletonClass::getInstance()->getFXTFLog()->LogOutLn("Successfully read MT4 (DLL) manager interface.");
	}

	//Please check this carefully as here main credential has been passing.
	int lMT4ServerConncetStatus = mMT4ManagerInterface->Connect( mMT4ServerIP.c_str() );
	int lMT4ServerLoginStatus	= mMT4ManagerInterface->Login( atoi(mMT4UserNameID.c_str()), mMT4UserPassword.c_str() );
	if( lMT4ServerConncetStatus ==  RET_OK && lMT4ServerLoginStatus == RET_OK )
	{
		SingletonClass::getInstance()->getFXTFLog()->LogOutLn("Successfully connected and login to MT4 server.");
	}
	else
	{
		SingletonClass::getInstance()->getFXTFLog()->LogOutLn("Error: Failed to connect and login to MT4 server.");
	}
	
	return mMT4ManagerInterface;
}

#if !defined CreateGroupsSymbolMargins_H
#define CreateGroupsSymbolMargins_H

#include "../FXTFTradingService/stdafx.h"
#include "../FXTFTradingService/MT4ManagerAPI.h"
#include "../Common/SingletonClass.h"

class CreateGroupsSymbolMargins
{

public:
	void AddGroupsSymbolsSettingsSwapsAndMargin(CManagerInterface* lMT4ManagerInterface);

};

#endif
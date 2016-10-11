#include "../Operation/CreateGroupsSymbolMargins.h"

void CreateGroupsSymbolMargins::AddGroupsSymbolsSettingsSwapsAndMargin(CManagerInterface* lMT4ManagerInterface)
{
		if( lMT4ManagerInterface->IsConnected() )
	{
		SingletonClass::getInstance()->getFXTFLog()->LogOutLn("MT4 Manager connetion is okey.");
		int               m_total=2;

		ConGroup         *m_groups;
		m_groups  =lMT4ManagerInterface->CfgRequestGroup(&m_total);
		
		char lGroupNameGeneric[100];
		
		m_groups[2].margin_stopout = 62;

		ConGroup  lgr=m_groups[2];

		lgr.secmargins[1] = ConGroupMargin();
		strcpy(lgr.secmargins[1].symbol,  "USDJPY");
		lgr.secmargins[1].swap_long		 = 0.002;
		lgr.secmargins[1].swap_short	 = 0.005;
		lgr.secmargins[1].margin_divider = 1;
		int res2 = lMT4ManagerInterface->CfgUpdateGroup(&lgr); 

		strcpy(lGroupNameGeneric,  lgr.secmargins[1].symbol);
		double lLongPosition		= lgr.secmargins[1].swap_long;
		double lShortPosition		= lgr.secmargins[1].swap_short;
		double lMarginPercentage	= lgr.secmargins[1].margin_divider;

	}

}

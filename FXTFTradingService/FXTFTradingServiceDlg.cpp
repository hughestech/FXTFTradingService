
// FXTFTradingServiceDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FXTFTradingService.h"
#include "FXTFTradingServiceDlg.h"
#include "../FXTFTradingService/MT4ManagerAPIConnection.h"
#include "../Operation/DepositMoneyOperation.h"
#include "../Operation/OpenPositionOperation.h"
#include "../Operation/CreateUserOperation.h"
#include "../Operation/CreateGroupsSymbolMargins.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CFXTFTradingServiceDlg::CFXTFTradingServiceDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CFXTFTradingServiceDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFXTFTradingServiceDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CFXTFTradingServiceDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
END_MESSAGE_MAP()

BOOL CFXTFTradingServiceDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	FXTFLog mLogWriter;
	if (mLogWriter.CommonLogInit())
	{
		mLogWriter.Enable();
		mLogWriter.GetTimeStr();
		mLogWriter.LogOut("");
	};

	SingletonClass::getInstance()->setFXTFLog(&mLogWriter);
	SingletonClass::getInstance()->getFXTFLog()->LogOutLn("Main Method has been initialized.");

	MT4ManagerAPIConnection* lMT4ManagerAPIConnection = new MT4ManagerAPIConnection();
	CManagerInterface* lCManagerInterface = lMT4ManagerAPIConnection->ConnectWithMT4Server();

	/* Creating each groups margin settings into tading server */
	//CreateGroupsSymbolMargins* lCreateGroupsSymbolMargins = new CreateGroupsSymbolMargins();
	//lCreateGroupsSymbolMargins->AddGroupsSymbolsSettingsSwapsAndMargin( lCManagerInterface );

	/* Deposit money according to csv file into tading server */
	//DepositMoneyOperation* lDepositMoneyOperation = new DepositMoneyOperation();
	//lDepositMoneyOperation->DepositMoneyToMT4TradingService( lCManagerInterface );
	
	/* Open positions/orders according to csv file into tading server */
	//OpenPositionOperation* lOpenPositionOperation = new OpenPositionOperation();
	//lOpenPositionOperation->OpenPositionToMT4TradingService( lCManagerInterface );

	/* Create users into tading server */
	//CreateUserOperation* lCreateUserOperation = new CreateUserOperation();
	//lCreateUserOperation->CreateUserToMT4TradingService(lCManagerInterface);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CFXTFTradingServiceDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CFXTFTradingServiceDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


#if !defined CFXTFTradingServiceDlg_H
#define CFXTFTradingServiceDlg_H


// FXTFTradingServiceDlg.h : header file
//

#pragma once

using namespace std;

class CFXTFTradingServiceDlg : public CDialogEx
{
// Construction
public:
	CFXTFTradingServiceDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_FXTFTRADINGSERVICE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
};


#endif
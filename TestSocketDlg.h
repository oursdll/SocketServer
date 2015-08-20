// TestSocketDlg.h : header file
//

#if !defined(AFX_TESTSOCKETDLG_H__51362EB3_85D9_40D4_8E7C_1A1D2000330D__INCLUDED_)
#define AFX_TESTSOCKETDLG_H__51362EB3_85D9_40D4_8E7C_1A1D2000330D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


/////////////////////////////////////////////////////////////////////////////
// CTestSocketDlg dialog

class CTestSocketDlg : public CDialog
{
// Construction
public:
	CTestSocketDlg(CWnd* pParent = NULL);	// standard constructor

	CString m_strDataSend;
	char	m_pbuf[8192];

	CString m_strSendNum;


	int		m_i,m_ii,m_j;
	int		m_nPackSize;
	int		m_nSA;
	int    m_iDNo;

	double	m_dCoeff,m_dSFrequency,m_dFrequency;

	int		m_nPackTimes;

	void NetParseData();
	void NetMoveData(int nMove);
	short		m_nLen;
	int gm_nCurPos;
	int gm_nDataNum;
	BOOL SendDeviceInfo();
	BOOL SendStateInfo();

// Dialog Data
	//{{AFX_DATA(CTestSocketDlg)
	enum { IDD = IDD_TESTSOCKET_DIALOG };
	CEdit	m_CtrSendNum;
	CEdit	m_CtrRecvNum;
	CEdit	m_CtrServerInfo;
	CEdit	m_CtrDataSend;
	CEdit	m_CtrState;
	int		m_nRouteNum;
	int		m_nSFrequency;
	int		m_nFrequency;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestSocketDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CTestSocketDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnCleanup();
	afx_msg void OnSend();
	afx_msg void OnApply();
	afx_msg void OnAutosend();
	afx_msg void OnStop();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTSOCKETDLG_H__51362EB3_85D9_40D4_8E7C_1A1D2000330D__INCLUDED_)

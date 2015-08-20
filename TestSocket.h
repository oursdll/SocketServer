// TestSocket.h : main header file for the TESTSOCKET application
//

#if !defined(AFX_TESTSOCKET_H__FC85CE56_0EEC_4059_AB6A_E76A3813E576__INCLUDED_)
#define AFX_TESTSOCKET_H__FC85CE56_0EEC_4059_AB6A_E76A3813E576__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CTestSocketApp:
// See TestSocket.cpp for the implementation of this class
//

class CTestSocketApp : public CWinApp
{
public:
	CTestSocketApp();


	


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestSocketApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CTestSocketApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTSOCKET_H__FC85CE56_0EEC_4059_AB6A_E76A3813E576__INCLUDED_)

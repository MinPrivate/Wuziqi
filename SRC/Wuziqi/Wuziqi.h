// Wuziqi.h : main header file for the WUZIQI application
//

#if !defined(AFX_WUZIQI_H__8D3380E6_2125_4A45_A5EC_B6FE8A87987D__INCLUDED_)
#define AFX_WUZIQI_H__8D3380E6_2125_4A45_A5EC_B6FE8A87987D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CWuziqiApp:
// See Wuziqi.cpp for the implementation of this class
//

class CWuziqiApp : public CWinApp
{
public:
	CWuziqiApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWuziqiApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CWuziqiApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WUZIQI_H__8D3380E6_2125_4A45_A5EC_B6FE8A87987D__INCLUDED_)

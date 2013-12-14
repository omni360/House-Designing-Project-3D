// Arch.h : main header file for the ARCH application
//

#if !defined(AFX_ARCH_H__1E9BABB5_77A0_4D99_BA12_BE7BF0B4E8D2__INCLUDED_)
#define AFX_ARCH_H__1E9BABB5_77A0_4D99_BA12_BE7BF0B4E8D2__INCLUDED_

#include "CurvedWallDlg.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols
#include "pillardlg.h"	// Added by ClassView
#include "StraightWallDlg.h"	// Added by ClassView
#include "StairDlg.h"	// Added by ClassView
#include "CurvedWall.h"	// Added by ClassView


/////////////////////////////////////////////////////////////////////////////
// CArchApp:
// See Arch.cpp for the implementation of this class
//

class CArchApp : public CWinApp
{
public:
	CView* SwitchView(CView* pNewView);
	CView* m_pCurrentView;
	CView* m_pGLView;
	CView* m_pGDIView;
	
	


	CArchApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CArchApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CArchApp)
	afx_msg void OnAppAbout();
	afx_msg void OnView3dview();
	afx_msg void OnView2dview();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ARCH_H__1E9BABB5_77A0_4D99_BA12_BE7BF0B4E8D2__INCLUDED_)

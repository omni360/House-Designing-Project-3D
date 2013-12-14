// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__C8C07412_231F_452F_8433_A5E4780AD7D0__INCLUDED_)
#define AFX_MAINFRM_H__C8C07412_231F_452F_8433_A5E4780AD7D0__INCLUDED_
#include "ArchView.h"
#include "GL3dView.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMainFrame : public CFrameWnd
{
	
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

//protected:  // control bar embedded members
public:
/*	CArchView*   m_p2dView;
	GL3dView*    m_p3dView;
	UINT m_CurrentView;*/
	CStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;
	CToolBar    m_tbrAppMode;
	CToolBar    m_tbrElement;

// Generated message map functions
protected:
	CToolBar m_wndObjectBar;
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnUpdateView2dview(CCmdUI* pCmdUI);
	afx_msg void OnUpdateView3dview(CCmdUI* pCmdUI);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__C8C07412_231F_452F_8433_A5E4780AD7D0__INCLUDED_)

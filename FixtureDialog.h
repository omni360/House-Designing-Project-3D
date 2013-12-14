#if !defined(AFX_FIXTUREDIALOG_H__43BE81C7_721F_4689_8108_391068F16254__INCLUDED_)
#define AFX_FIXTUREDIALOG_H__43BE81C7_721F_4689_8108_391068F16254__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FixtureDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// FixtureDialog dialog

#include "wall.h"

class FixtureDialog : public CDialog
{
// Construction
public:
	CWall* m_pWallContainer;
	FixtureDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(FixtureDialog)
	enum { IDD = IDD_FIXTURE };
	CListBox	m_FixtureList;
	CButton	m_WallPreview;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(FixtureDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(FixtureDialog)
	afx_msg void OnBtnCHK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FIXTUREDIALOG_H__43BE81C7_721F_4689_8108_391068F16254__INCLUDED_)

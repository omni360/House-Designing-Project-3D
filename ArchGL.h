#if !defined(AFX_ARCHGL_H__940ECA4B_BC01_45E5_B968_915C009CFE4E__INCLUDED_)
#define AFX_ARCHGL_H__940ECA4B_BC01_45E5_B968_915C009CFE4E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ArchGL.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CArchGL dialog

class CArchGL : public CDialog
{
// Construction
public:
	CArchGL(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CArchGL)
	enum { IDD = IDD_ARCHGL_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CArchGL)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CArchGL)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ARCHGL_H__940ECA4B_BC01_45E5_B968_915C009CFE4E__INCLUDED_)

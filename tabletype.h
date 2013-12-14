#if !defined(AFX_TABLETYPE_H__A95FA281_2FB6_11D8_864D_D88955381671__INCLUDED_)
#define AFX_TABLETYPE_H__A95FA281_2FB6_11D8_864D_D88955381671__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// tabletype.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Ctabletype dialog

class Ctabletype : public CDialog
{
// Construction
public:
	Ctabletype(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(Ctabletype)
	enum { IDD = IDD_DIALOG1 };
	int		m_ctype;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Ctabletype)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Ctabletype)
	virtual BOOL OnInitDialog();
	afx_msg void OnChair1();
	afx_msg void OnChair2();
	afx_msg void OnChair3();
	afx_msg void OnChair4();
	afx_msg void OnChair5();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TABLETYPE_H__A95FA281_2FB6_11D8_864D_D88955381671__INCLUDED_)

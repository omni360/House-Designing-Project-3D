#if !defined(AFX_CHAIR_TYPE_H__3B40F4A0_4DBD_11D8_BA23_E0C6805CA65E__INCLUDED_)
#define AFX_CHAIR_TYPE_H__3B40F4A0_4DBD_11D8_BA23_E0C6805CA65E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// chair_type.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Cchair_type dialog

class Cchair_type : public CDialog
{
// Construction
public:
		COLORREF m_col;
	Cchair_type(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(Cchair_type)
	enum { IDD = IDD_DIALOG4 };
	int		m_ctype;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Cchair_type)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Cchair_type)
	afx_msg void OnChair1();
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnChair2();
	afx_msg void OnChair3();
	afx_msg void OnChair4();
	afx_msg void OnChair5();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHAIR_TYPE_H__3B40F4A0_4DBD_11D8_BA23_E0C6805CA65E__INCLUDED_)

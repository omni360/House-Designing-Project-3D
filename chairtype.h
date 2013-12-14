#if !defined(AFX_CHAIRTYPE_H__BD5F57A3_2FC3_11D8_864D_D88955381671__INCLUDED_)
#define AFX_CHAIRTYPE_H__BD5F57A3_2FC3_11D8_864D_D88955381671__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// chairtype.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Cchairtype dialog

class Cchairtype : public CDialog
{
// Construction
public:
COLORREF m_col;

	Cchairtype(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(Cchairtype)
	enum { IDD = IDD_DIALOG3 };
	CComboBox	m_chairtypectrl;
	CString	m_chairtype;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Cchairtype)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Cchairtype)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHAIRTYPE_H__BD5F57A3_2FC3_11D8_864D_D88955381671__INCLUDED_)

#if !defined(AFX_SOFATYPE_H__BD5F57A2_2FC3_11D8_864D_D88955381671__INCLUDED_)
#define AFX_SOFATYPE_H__BD5F57A2_2FC3_11D8_864D_D88955381671__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// sofatype.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Csofatype dialog

class Csofatype : public CDialog
{
// Construction
public:
	Csofatype(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(Csofatype)
	enum { IDD = IDD_DIALOG2 };
	CComboBox	m_sofatypectrl;
	CString	m_sofatype;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Csofatype)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Csofatype)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SOFATYPE_H__BD5F57A2_2FC3_11D8_864D_D88955381671__INCLUDED_)

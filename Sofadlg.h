#if !defined(AFX_SOFADLG_H__5DBCF580_86A9_11D9_A1DD_9DF3117FA528__INCLUDED_)
#define AFX_SOFADLG_H__5DBCF580_86A9_11D9_A1DD_9DF3117FA528__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Sofadlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSofadlg dialog

class CSofadlg : public CDialog
{
// Construction
public:
		COLORREF m_col;
	CSofadlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSofadlg)
	enum { IDD = IDD_DIALOG_SOFA };
	int		m_sofatype;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSofadlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSofadlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SOFADLG_H__5DBCF580_86A9_11D9_A1DD_9DF3117FA528__INCLUDED_)

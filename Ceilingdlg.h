#if !defined(AFX_CEILINGDLG_H__79024A40_5FA7_11D8_B190_F0AF78BC545C__INCLUDED_)
#define AFX_CEILINGDLG_H__79024A40_5FA7_11D8_B190_F0AF78BC545C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Ceilingdlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCeilingdlg dialog

class CCeilingdlg : public CDialog
{
// Construction
public:
	COLORREF m_color;
	CCeilingdlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCeilingdlg)
	enum { IDD = IDD_DIALOG_CEILING };
	float	m_ctoppoint;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCeilingdlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCeilingdlg)
	afx_msg void OnCeilColor();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CEILINGDLG_H__79024A40_5FA7_11D8_B190_F0AF78BC545C__INCLUDED_)

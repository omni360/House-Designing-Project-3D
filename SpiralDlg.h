#if !defined(AFX_SPIRALDLG_H__ED101E60_8681_11D9_A1DD_FCA147A7E328__INCLUDED_)
#define AFX_SPIRALDLG_H__ED101E60_8681_11D9_A1DD_FCA147A7E328__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SpiralDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSpiralDlg dialog

class CSpiralDlg : public CDialog
{
// Construction
public:
		COLORREF m_scol;
	CSpiralDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSpiralDlg)
	enum { IDD = IDD_DIALOG5 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSpiralDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSpiralDlg)
	afx_msg void OnSpiralColor();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SPIRALDLG_H__ED101E60_8681_11D9_A1DD_FCA147A7E328__INCLUDED_)

#if !defined(AFX_STAIRDLG_H__72E93240_9D9E_4315_AFF0_930E4A36E06B__INCLUDED_)
#define AFX_STAIRDLG_H__72E93240_9D9E_4315_AFF0_930E4A36E06B__INCLUDED_

#include "Stairs.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// StairDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CStairDlg dialog

class CStairDlg : public CDialog
{
// Construction
public:
	COLORREF m_color;
	int m_width;


	CStairDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CStairDlg)
	enum { IDD = IDD_DIALOG_STAIR };
	CButton	m_preview;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStairDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CStairDlg)
	afx_msg void OnButtonColor();
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnRadioWidth2();
	afx_msg void OnRadioWidth3();
	afx_msg void OnRadioWidth4();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STAIRDLG_H__72E93240_9D9E_4315_AFF0_930E4A36E06B__INCLUDED_)

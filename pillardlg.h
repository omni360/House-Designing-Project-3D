#if !defined(AFX_PILLARDLG_H__2284DE7E_05EE_4E60_B663_F25728F9EDB2__INCLUDED_)
#define AFX_PILLARDLG_H__2284DE7E_05EE_4E60_B663_F25728F9EDB2__INCLUDED_

#include "Pillar.h"	// Added by ClassView
#include "resource.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PillarDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPillarDlg dialog

class CPillarDlg : public CDialog
{
// Construction
public:
	
	COLORREF m_col;
//	int m_diff;

	CPillarDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPillarDlg)
	enum { IDD = IDD_DIALOG_PILLAR };
	CButton	m_preview;
	int		m_width;
	int		m_type;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPillarDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPillarDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnRadioTypeCylinder();
	afx_msg void OnRadioTypeCubic();
	afx_msg void OnRadioWidth1();
	afx_msg void OnRADIOWIDTH1andHalf();
	afx_msg void OnRadioWidth2();
	afx_msg void OnButtonColor();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PILLARDLG_H__2284DE7E_05EE_4E60_B663_F25728F9EDB2__INCLUDED_)

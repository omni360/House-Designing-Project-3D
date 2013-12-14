#if !defined(AFX_CURVEDWALLDLG_H__1D89C21B_5131_48A4_85F7_BEFE3FF8FB54__INCLUDED_)
#define AFX_CURVEDWALLDLG_H__1D89C21B_5131_48A4_85F7_BEFE3FF8FB54__INCLUDED_

#include "EnBitmap.h"	// Added by ClassView
#include "CurvedWall.h"	// Added by ClassView
#include "resource.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CurvedWallDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCurvedWallDlg dialog

class CCurvedWallDlg : public CDialog
{
// Construction
public:
	
	
	CString m_sFilenameB;
	CString m_sFilenameA;
	int m_width;
	bool m_istextureB;
	bool m_istextureA;
	COLORREF m_colorB;
	COLORREF m_colorA;
	CCurvedWallDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCurvedWallDlg)
	enum { IDD = IDD_DIALOG_CURVED_WALL };
	CButton	m_views2;
	CButton	m_views1;
	CButton	m_wallpreview;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCurvedWallDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCurvedWallDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	virtual void OnOK();
	afx_msg void OnRadioCol1();
	afx_msg void OnRadioTexture1();
	afx_msg void OnRadioCol2();
	afx_msg void OnRadioTexture2();
	afx_msg void OnRadioWall4();
	afx_msg void OnRadioWall9();
	afx_msg void OnRadioWall13();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CURVEDWALLDLG_H__1D89C21B_5131_48A4_85F7_BEFE3FF8FB54__INCLUDED_)

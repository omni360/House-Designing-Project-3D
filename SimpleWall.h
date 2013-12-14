#if !defined(AFX_SIMPLEWALL_H__3EC69601_859A_11D9_A1DD_B797C69CCA28__INCLUDED_)
#define AFX_SIMPLEWALL_H__3EC69601_859A_11D9_A1DD_B797C69CCA28__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SimpleWall.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSimpleWall dialog

class CSimpleWall : public CDialog
{
// Construction
public:
CString	m_sFilenameA; //Path of bitmap on side1
CString	m_sFilenameB;
	int fixturetype;
	int m_calculate;
	//CArchDoc* GetDocument();
	//CArchDoc* GetDocument();
//	CDocument* m_p;
    int m_flag,m_flag1;
	int value1;
	int countclk,countclk1;
	int countsave,countsave1;
	void SetValue();
    //CWall* wall;
	int m_walllength;
	int inc;
	COLORREF m_colorB;
	COLORREF m_colorA;
	int m_width;
	
	

	BOOL m_istextureB;	// To check whether color or texture on side2
	BOOL m_istextureA;  	// To check whether color or texture on side1
	
	CSimpleWall(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSimpleWall)
	enum { IDD = IDD_WALL };
	CButton	m_sideBpre;
	CButton	m_wallpreview;
	float	m_base;
	float	m_top;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSimpleWall)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSimpleWall)
	virtual BOOL OnInitDialog();
	afx_msg void OnSideA();
	afx_msg void OnSideB();
	afx_msg void OnPaint();
	afx_msg void OnRADIOWidth();
	afx_msg void OnRadio6_width9();
	afx_msg void OnRadio7_width13();
	afx_msg void OnT1();
	afx_msg void OnT2();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SIMPLEWALL_H__3EC69601_859A_11D9_A1DD_B797C69CCA28__INCLUDED_)

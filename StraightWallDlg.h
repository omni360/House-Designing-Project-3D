#if !defined(AFX_STRAIGHTWALLDLG_H__A3A1B555_EFBF_4722_911F_9D9D7B9DBA70__INCLUDED_)
#define AFX_STRAIGHTWALLDLG_H__A3A1B555_EFBF_4722_911F_9D9D7B9DBA70__INCLUDED_

#include "Wall.h"	// Added by ClassView
#include "Fixture.h"	// Added by ClassView
#include "EnBitmap.h"
#include "Door.h"	// Added by ClassView
#include "Wind.h"	// Added by ClassView
#include "resource.h"
#include "ArchDoc.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// StraightWallDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CStraightWallDlg dialog
class	CDocument;
class CStraightWallDlg : public CDialog
{
// Construction
public:
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

	int inc;
	CPoint leftdoorpoint,rightdoorpoint;
	CPoint dpoint,wpoint;
	CPoint m_connectedpointwindow,m_bottompointwindow;
	BOOL OverSizing();
	BOOL Overlapping();
	int m_walllength;
	int m_doorlength;
	int m_windowlength;

	CPoint m_connectedpointdoor;
    CPoint m_bottomRight,m_bottomLeft;
	
	CRect m_windowframe;
	CRect m_doorframe;
	COLORREF m_colorB;
	COLORREF m_colorA;
	int m_width;
	COLORREF m_windowcolor;
	COLORREF m_doorcolor;

	CRect * m_fixtdoor;
	CRect * m_fixtwindow; //check which fixture is selected at the moment
	int m_windowtype;  //Type of Window
	int m_doortype;    // Type of door
	


	BOOL m_iswindow;// to check whether window is added or not
	BOOL	m_isdoor; // to check whether door is added or not
	BOOL m_istextureB;	// To check whether color or texture on side2
	BOOL m_istextureA;  	// To check whether color or texture on side1
	
	CPoint m_pt1; // For resizing of fixtures
	CPoint m_pt2; // For resizing of fixtures
	
	
	BOOL OnInitDialog();

	CStraightWallDlg(CWnd* pParent = NULL); // standard constructor

//		HICON m_hIcon;
// Dialog Data
	//{{AFX_DATA(CStraightWallDlg)
	enum { IDD = IDD_DIALOG_STRAIGHT_WALL };
	CButton	m_btnwindowclr; 
	CButton	m_btndoorclr;
	CButton	m_wallview; //Wall Preview
	CButton	m_views2; //View of wall's 2nd side color or fixture
	CButton	m_views1; //View of wall's Ist side color or fixture
CString	m_sFilenameA; //Path of bitmap on side1
CString	m_sFilenameB;  //Path of bitmap on side2
	BOOL	m_checkdoor;
	BOOL	m_checkwindow;
	float	m_basepoint;
	float	m_wtoppoint;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStraightWallDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CStraightWallDlg)
	afx_msg void OnRadioTexture1();
	afx_msg void OnRadioWall4();
	afx_msg void OnRadioWall9();
	afx_msg void OnRadioWall13();
	afx_msg void OnRadioCol1();
	afx_msg void OnRadioCol2();
	afx_msg void OnPaint();
	afx_msg void OnRadioTexture2();
	afx_msg void OnRADIODOOR2x7();
	afx_msg void OnRADIODOOR3x7();
	afx_msg void OnRADIODOOR4x7();
	afx_msg void OnRADIOWINDOW2x3();
	afx_msg void OnRADIOWINDOW3x3();
	afx_msg void OnRADIOWINDOW3x4();
	afx_msg void OnRADIOWINDOW4x4();
	afx_msg void OnCheckDoor();
	afx_msg void OnCheckWindow();
	afx_msg void OnBtnDoorClr();
	afx_msg void OnBtnWindowClr();
	afx_msg void OnSelectDoor();
	afx_msg void OnSelectWindow();
	afx_msg void OnBtnMoveRight();
	afx_msg void OnBtnMoveLeft();
	virtual void OnOK();
	afx_msg void OnChangeBasePoint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
/*#ifndef _DEBUG  // debug version in ArchView.cpp
inline CArchDoc* CArchView::GetDocument()
   { return (CArchDoc*)m_pDocument; }
#endif*/
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.


#endif // !defined(AFX_STRAIGHTWALLDLG_H__A3A1B555_EFBF_4722_911F_9D9D7B9DBA70__INCLUDED_)

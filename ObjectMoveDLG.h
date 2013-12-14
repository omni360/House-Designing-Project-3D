#if !defined(AFX_OBJECTMOVEDLG_H__D83AA7C5_C925_4945_BFFD_8619C3537ECB__INCLUDED_)
#define AFX_OBJECTMOVEDLG_H__D83AA7C5_C925_4945_BFFD_8619C3537ECB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ObjectMoveDLG.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// ObjectMoveDLG dialog

class ObjectMoveDLG : public CDialog
{
// Construction
public:
	int Val_X;
		int Val_Y;
			int Val_Z;
	ObjectMoveDLG(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(ObjectMoveDLG)
	enum { IDD = IDD_DLG_MOVE };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ObjectMoveDLG)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(ObjectMoveDLG)
	afx_msg void OnMoveDone();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OBJECTMOVEDLG_H__D83AA7C5_C925_4945_BFFD_8619C3537ECB__INCLUDED_)

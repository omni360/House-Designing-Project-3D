#if !defined(AFX_OBJROTATEDLG_H__F94B747A_04EC_4887_9F3B_AE791F82A924__INCLUDED_)
#define AFX_OBJROTATEDLG_H__F94B747A_04EC_4887_9F3B_AE791F82A924__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ObjRotateDLG.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// ObjRotateDLG dialog

class ObjRotateDLG : public CDialog
{
// Construction
public:
	ObjRotateDLG(CWnd* pParent = NULL);   // standard constructor
    int rot_angle;
	int x_side;
	int y_side;
	int z_side;
// Dialog Data
	//{{AFX_DATA(ObjRotateDLG)
	enum { IDD = IDD_DLG_ROTATE };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ObjRotateDLG)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(ObjRotateDLG)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OBJROTATEDLG_H__F94B747A_04EC_4887_9F3B_AE791F82A924__INCLUDED_)

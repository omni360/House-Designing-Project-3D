#if !defined(AFX_VFD_H__1795C7B0_897A_4E74_85B4_3CB154FE3D7D__INCLUDED_)
#define AFX_VFD_H__1795C7B0_897A_4E74_85B4_3CB154FE3D7D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// vfd.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// ViewFloorDialog dialog

class ViewFloorDialog : public CDialog
{
// Construction
public:
	UINT m_nTotalFloor;
	ViewFloorDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(ViewFloorDialog)
	enum { IDD = IDD_FLOOR_VIEW };
	CEdit	m_editFloor;
	UINT	m_nFloor;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ViewFloorDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(ViewFloorDialog)
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VFD_H__1795C7B0_897A_4E74_85B4_3CB154FE3D7D__INCLUDED_)

// ObjectMoveDLG.cpp : implementation file
//

#include "stdafx.h"
#include "arch.h"
#include "ObjectMoveDLG.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ObjectMoveDLG dialog


ObjectMoveDLG::ObjectMoveDLG(CWnd* pParent /*=NULL*/)
	: CDialog(ObjectMoveDLG::IDD, pParent)
{
	//{{AFX_DATA_INIT(ObjectMoveDLG)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void ObjectMoveDLG::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ObjectMoveDLG)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ObjectMoveDLG, CDialog)
	//{{AFX_MSG_MAP(ObjectMoveDLG)
	ON_BN_CLICKED(ID_MOVE_DONE, OnMoveDone)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ObjectMoveDLG message handlers

void ObjectMoveDLG::OnMoveDone() 
{
	// TODO: Add your control notification handler code here

Val_X =  GetDlgItemInt(IDC_EDIT_X,NULL,TRUE);
Val_Y =  GetDlgItemInt(IDC_EDIT_Y,NULL,TRUE);
Val_Z =  GetDlgItemInt(IDC_EDIT_Z,NULL,TRUE);

CDialog::OnOK();
}

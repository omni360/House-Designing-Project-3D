// ObjRotateDLG.cpp : implementation file
//

#include "stdafx.h"
#include "arch.h"
#include "ObjRotateDLG.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ObjRotateDLG dialog


ObjRotateDLG::ObjRotateDLG(CWnd* pParent /*=NULL*/)
	: CDialog(ObjRotateDLG::IDD, pParent)
{
	//{{AFX_DATA_INIT(ObjRotateDLG)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void ObjRotateDLG::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ObjRotateDLG)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ObjRotateDLG, CDialog)
	//{{AFX_MSG_MAP(ObjRotateDLG)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ObjRotateDLG message handlers

void ObjRotateDLG::OnOK() 
{
	// TODO: Add extra validation here
rot_angle =  GetDlgItemInt(IDC_ROTATE_ANGLE,NULL,TRUE);
x_side    =  GetDlgItemInt(IDC_ROTATE_X , NULL,TRUE);
y_side    =  GetDlgItemInt(IDC_ROTATE_Y , NULL,TRUE);
z_side     =  GetDlgItemInt(IDC_ROTATE_Z ,NULL,TRUE);
	CDialog::OnOK();
}

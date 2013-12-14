// vfd.cpp : implementation file
//

#include "stdafx.h"
#include "Arch.h"
#include "vfd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ViewFloorDialog dialog


ViewFloorDialog::ViewFloorDialog(CWnd* pParent /*=NULL*/)
	: CDialog(ViewFloorDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(ViewFloorDialog)
	m_nFloor = 0;
	//}}AFX_DATA_INIT
}


void ViewFloorDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ViewFloorDialog)
	DDX_Control(pDX, IDC_EDIT_FLOORNUM, m_editFloor);
	DDX_Text(pDX, IDC_EDIT_FLOORNUM, m_nFloor);
	DDV_MinMaxUInt(pDX, m_nFloor, 0, m_nTotalFloor);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ViewFloorDialog, CDialog)
	//{{AFX_MSG_MAP(ViewFloorDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()



void ViewFloorDialog::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);
	CDialog::OnOK();
}

void ViewFloorDialog::OnCancel() 
{
	// TODO: Add extra cleanup here
	UpdateData(FALSE);
	CDialog::OnCancel();
}

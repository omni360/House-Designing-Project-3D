// FixtureDialog.cpp : implementation file
//

#include "stdafx.h"
#include "Arch.h"
#include "FixtureDialog.h"
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// FixtureDialog dialog


FixtureDialog::FixtureDialog(CWnd* pParent /*=NULL*/)
	: CDialog(FixtureDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(FixtureDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void FixtureDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(FixtureDialog)
	DDX_Control(pDX, IDC_LISTFIXTURE, m_FixtureList);
	DDX_Control(pDX, IDC_PREVIEW, m_WallPreview);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(FixtureDialog, CDialog)
	//{{AFX_MSG_MAP(FixtureDialog)
	ON_BN_CLICKED(IDC_BtnCHK, OnBtnCHK)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// FixtureDialog message handlers

void FixtureDialog::OnBtnCHK() 
{
	// TODO: Add your control notification handler code here
	CRect r;
	m_WallPreview.GetClientRect(&r); 
	CString msg;
	msg.Format("%d, %d %d, %d",r.left,r.top,r.right,r.bottom);
	MessageBox(msg,"ARCH",MB_OK);
}

BOOL FixtureDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CPoint f = m_pWallContainer->m_ptFirstPosition;
	CPoint s = m_pWallContainer->m_ptSecondPosition;
	double d;
	d = sqrt(pow((f.x-s.x),2)+pow((f.y-s.y),2));
	CString ts;
	ts.Format("%L",d);
	SetWindowText(ts);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

// chairtype.cpp : implementation file
//

#include "stdafx.h"
#include "Arch.h"
#include "chairtype.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Cchairtype dialog


Cchairtype::Cchairtype(CWnd* pParent /*=NULL*/)
	: CDialog(Cchairtype::IDD, pParent)
{
	//{{AFX_DATA_INIT(Cchairtype)
	m_chairtype = _T("");
	//}}AFX_DATA_INIT
}


void Cchairtype::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Cchairtype)
	DDX_Control(pDX, IDC_ctypeCOMBO1, m_chairtypectrl);
	DDX_CBString(pDX, IDC_ctypeCOMBO1, m_chairtype);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Cchairtype, CDialog)
	//{{AFX_MSG_MAP(Cchairtype)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Cchairtype message handlers

BOOL Cchairtype::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_chairtypectrl.AddString("A");
	m_chairtypectrl.AddString("B");
	m_chairtypectrl.AddString("C");
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

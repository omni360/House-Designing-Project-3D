// tabletype.cpp : implementation file
//

#include "stdafx.h"
#include "Arch.h"
#include "tabletype.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Ctabletype dialog


Ctabletype::Ctabletype(CWnd* pParent /*=NULL*/)
	: CDialog(Ctabletype::IDD, pParent)
{
	//{{AFX_DATA_INIT(Ctabletype)
	m_ctype = -1;
	//}}AFX_DATA_INIT
}


void Ctabletype::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Ctabletype)
	DDX_Radio(pDX, IDC_CHAIR1, m_ctype);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Ctabletype, CDialog)
	//{{AFX_MSG_MAP(Ctabletype)
	ON_BN_CLICKED(IDC_CHAIR1, OnChair1)
	ON_BN_CLICKED(IDC_CHAIR2, OnChair2)
	ON_BN_CLICKED(IDC_CHAIR3, OnChair3)
	ON_BN_CLICKED(IDC_CHAIR4, OnChair4)
	ON_BN_CLICKED(IDC_CHAIR5, OnChair5)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Ctabletype message handlers

BOOL Ctabletype::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_tabletypectrl.AddString("1");
	m_tabletypectrl.AddString("2");
	m_tabletypectrl.AddString("3");
	m_tabletypectrl.AddString("4");
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void Ctabletype::OnChair1() 
{
	// TODO: Add your control notification handler code here
m_ctype=1;	
}

void Ctabletype::OnChair2() 
{
	// TODO: Add your control notification handler code here
m_ctype=2;	
}

void Ctabletype::OnChair3() 
{
	// TODO: Add your control notification handler code here
	m_ctype=3;
}

void Ctabletype::OnChair4() 
{
	// TODO: Add your control notification handler code here
	m_ctype=4;
}

void Ctabletype::OnChair5() 
{
	// TODO: Add your control notification handler code here
	m_ctype=5;
}

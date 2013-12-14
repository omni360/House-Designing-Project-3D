// chair_type.cpp : implementation file
//

#include "stdafx.h"
#include "Arch.h"
#include "chair_type.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Cchair_type dialog


Cchair_type::Cchair_type(CWnd* pParent /*=NULL*/)
	: CDialog(Cchair_type::IDD, pParent)
{
	//{{AFX_DATA_INIT(Cchair_type)
	m_ctype = -1;
	//}}AFX_DATA_INIT
}


void Cchair_type::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Cchair_type)
	DDX_Radio(pDX, IDC_CHAIR1, m_ctype);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Cchair_type, CDialog)
	//{{AFX_MSG_MAP(Cchair_type)
	ON_BN_CLICKED(IDC_CHAIR1, OnChair1)
	ON_BN_CLICKED(IDC_CHAIR2, OnChair2)
	ON_BN_CLICKED(IDC_CHAIR3, OnChair3)
	ON_BN_CLICKED(IDC_CHAIR4, OnChair4)
	ON_BN_CLICKED(IDC_CHAIR5, OnChair5)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Cchair_type message handlers

void Cchair_type::OnChair1() 
{
	// TODO: Add your control notification handler code here
m_ctype=0;	
}









BOOL Cchair_type::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	if (m_ctype==4)
		CheckRadioButton( IDC_CHAIR1, IDC_CHAIR5, IDC_CHAIR5);	
	if (m_ctype==3)
		CheckRadioButton( IDC_CHAIR1, IDC_CHAIR5, IDC_CHAIR4);	
	if (m_ctype==2)
		CheckRadioButton( IDC_CHAIR1, IDC_CHAIR5, IDC_CHAIR3);	

	
	
	if (m_ctype==1)
		CheckRadioButton( IDC_CHAIR1, IDC_CHAIR5, IDC_CHAIR2);	
	if (m_ctype==0)
		CheckRadioButton( IDC_CHAIR1, IDC_CHAIR5, IDC_CHAIR1);
		
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void Cchair_type::OnOK() 
{
	// TODO: Add extra validation here

	CDialog::OnOK();
}

void Cchair_type::OnChair2() 
{
	// TODO: Add your control notification handler code here
m_ctype=1;		
}

void Cchair_type::OnChair3() 
{
	// TODO: Add your control notification handler code here
m_ctype=2;		
}

void Cchair_type::OnChair4() 
{
	// TODO: Add your control notification handler code here
m_ctype=3;		
}

void Cchair_type::OnChair5() 
{
	// TODO: Add your control notification handler code here
m_ctype=4;		
}

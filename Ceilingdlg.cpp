// Ceilingdlg.cpp : implementation file
//

#include "stdafx.h"
#include "arch.h"
#include "Ceilingdlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCeilingdlg dialog


CCeilingdlg::CCeilingdlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCeilingdlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCeilingdlg)
	m_ctoppoint = 0.0f;
	//}}AFX_DATA_INIT
}


void CCeilingdlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCeilingdlg)
	DDX_Text(pDX, IDC_CEILING_POINT, m_ctoppoint);
	DDV_MinMaxFloat(pDX, m_ctoppoint, 0.f, 120.f);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCeilingdlg, CDialog)
	//{{AFX_MSG_MAP(CCeilingdlg)
	ON_BN_CLICKED(IDC_CEIL_COLOR, OnCeilColor)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCeilingdlg message handlers

void CCeilingdlg::OnCeilColor() 
{
	// TODO: Add your control notification handler code here
		CColorDialog cdlg;
	if (cdlg.DoModal()==IDOK)
	{
		m_color=cdlg.GetColor();
	}
}

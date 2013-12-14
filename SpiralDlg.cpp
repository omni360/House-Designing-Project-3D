// SpiralDlg.cpp : implementation file
//

#include "stdafx.h"
#include "arch.h"
#include "SpiralDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSpiralDlg dialog


CSpiralDlg::CSpiralDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSpiralDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSpiralDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CSpiralDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSpiralDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSpiralDlg, CDialog)
	//{{AFX_MSG_MAP(CSpiralDlg)
	ON_BN_CLICKED(IDC_SPIRAL_COLOR, OnSpiralColor)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSpiralDlg message handlers

void CSpiralDlg::OnSpiralColor() 
{
	// TODO: Add your control notification handler code here
	CColorDialog cdlg;
	if (cdlg.DoModal()==IDOK)
	{
		m_scol=cdlg.GetColor();
	}	
}

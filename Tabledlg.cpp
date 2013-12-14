// Tabledlg.cpp : implementation file
//

#include "stdafx.h"
#include "arch.h"
#include "Tabledlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTabledlg dialog


CTabledlg::CTabledlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTabledlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTabledlg)
	m_tabletype = -1;
	//}}AFX_DATA_INIT
}


void CTabledlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTabledlg)
	DDX_Radio(pDX, IDC_RADIO_table, m_tabletype);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTabledlg, CDialog)
	//{{AFX_MSG_MAP(CTabledlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTabledlg message handlers

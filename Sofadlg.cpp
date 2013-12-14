// Sofadlg.cpp : implementation file
//

#include "stdafx.h"
#include "arch.h"
#include "Sofadlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSofadlg dialog


CSofadlg::CSofadlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSofadlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSofadlg)
	m_sofatype = -1;
	//}}AFX_DATA_INIT
}


void CSofadlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSofadlg)
	DDX_Radio(pDX, IDC_RADIO_sofa, m_sofatype);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSofadlg, CDialog)
	//{{AFX_MSG_MAP(CSofadlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSofadlg message handlers

// ArchGL.cpp : implementation file
//

#include "stdafx.h"
#include "Arch.h"
#include "ArchGL.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CArchGL dialog


CArchGL::CArchGL(CWnd* pParent /*=NULL*/)
	: CDialog(CArchGL::IDD, pParent)
{
	//{{AFX_DATA_INIT(CArchGL)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CArchGL::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CArchGL)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CArchGL, CDialog)
	//{{AFX_MSG_MAP(CArchGL)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CArchGL message handlers

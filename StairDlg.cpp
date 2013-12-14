// StairDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Arch.h"
#include "StairDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStairDlg dialog


CStairDlg::CStairDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CStairDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CStairDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CStairDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStairDlg)
	DDX_Control(pDX, IDC_STATIC_Preview, m_preview);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CStairDlg, CDialog)
	//{{AFX_MSG_MAP(CStairDlg)
	ON_BN_CLICKED(IDC_BUTTON_COLOR, OnButtonColor)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_RADIO_WIDTH_2, OnRadioWidth2)
	ON_BN_CLICKED(IDC_RADIO_WIDTH_3, OnRadioWidth3)
	ON_BN_CLICKED(IDC_RADIO_WIDTH_4, OnRadioWidth4)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStairDlg message handlers

void CStairDlg::OnButtonColor() 
{
	// TODO: Add your control notification handler code here
	CColorDialog cdlg;
	if (cdlg.DoModal()==IDOK)
	{
		m_color=cdlg.GetColor();
	}
	OnPaint();
}

BOOL CStairDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	if (m_width==48)	
	CheckRadioButton( IDC_RADIO_WIDTH_2, IDC_RADIO_WIDTH_4, IDC_RADIO_WIDTH_4);
	else if (m_width==36)
			CheckRadioButton( IDC_RADIO_WIDTH_2, IDC_RADIO_WIDTH_4, IDC_RADIO_WIDTH_3);	
	else if (m_width==24)
			CheckRadioButton( IDC_RADIO_WIDTH_2, IDC_RADIO_WIDTH_4, IDC_RADIO_WIDTH_2);	
	
return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE 
}

void CStairDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	CDC * dcstairview;
	dcstairview = m_preview.GetWindowDC();
	
	CBrush b1;
	b1.CreateSolidBrush(m_color);
	CBrush * oldBrush = dcstairview->SelectObject(&b1);
	dcstairview->SelectObject(&b1);
	int x = 10;
	int y = 20;
	for (int i=1; i<=10; i++)
	{
	dcstairview -> Rectangle (x,y,x+22,y+20);
	x+=17;
	y+=20;
	}
	dcstairview -> SelectObject(&oldBrush);
	// Do not call CDialog::OnPaint() for painting messages
}

void CStairDlg::OnRadioWidth2() 
{
	// TODO: Add your control notification handler code here
	m_width=24;
}

void CStairDlg::OnRadioWidth3() 
{
	// TODO: Add your control notification handler code here
	m_width=36;
}

void CStairDlg::OnRadioWidth4() 
{
	// TODO: Add your control notification handler code here
	m_width=48;
}

void CStairDlg::OnOK() 
{
	// TODO: Add extra validation here
	CDialog::OnOK();
}

// PillarDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Pillar.h"
#include "PillarDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPillarDlg dialog


CPillarDlg::CPillarDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPillarDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPillarDlg)
	m_width = -1;
	m_type = -1;
	//}}AFX_DATA_INIT
	
}


void CPillarDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPillarDlg)
	DDX_Control(pDX, IDC_STATIC_PILLAR_PREVIEW, m_preview);
	DDX_Radio(pDX, IDC_RADIO_WIDTH_1, m_width);
	DDX_Radio(pDX, IDC_RADIO_TYPE_CYLINDER, m_type);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPillarDlg, CDialog)
	//{{AFX_MSG_MAP(CPillarDlg)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_RADIO_TYPE_CYLINDER, OnRadioTypeCylinder)
	ON_BN_CLICKED(IDC_RADIO_TYPE_CUBIC, OnRadioTypeCubic)
	ON_BN_CLICKED(IDC_RADIO_WIDTH_1, OnRadioWidth1)
	ON_BN_CLICKED(IDC_RADIO_WIDTH_1andHalf, OnRADIOWIDTH1andHalf)
	ON_BN_CLICKED(IDC_RADIO_WIDTH_2, OnRadioWidth2)
	ON_BN_CLICKED(IDC_BUTTON_COLOR, OnButtonColor)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPillarDlg message handlers

BOOL CPillarDlg::OnInitDialog() 
{
	
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
//	CArchView
	
	
	

	
	if (m_width==12)
		CheckRadioButton( IDC_RADIO_WIDTH_1, IDC_RADIO_WIDTH_2, IDC_RADIO_WIDTH_1);	
	if (m_width==18)
		CheckRadioButton( IDC_RADIO_WIDTH_1, IDC_RADIO_WIDTH_2, IDC_RADIO_WIDTH_1andHalf);
	if (m_width== 24)
		CheckRadioButton( IDC_RADIO_WIDTH_1, IDC_RADIO_WIDTH_2, IDC_RADIO_WIDTH_2);	
	if (m_type==1)
		CheckRadioButton( IDC_RADIO_TYPE_CYLINDER, IDC_RADIO_TYPE_CUBIC, IDC_RADIO_TYPE_CUBIC);	
	if (m_type==0)
		CheckRadioButton( IDC_RADIO_TYPE_CYLINDER, IDC_RADIO_TYPE_CUBIC, IDC_RADIO_TYPE_CYLINDER);
		OnPaint();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPillarDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting

	// TODO: Add your message handler code here

	CDC * dcpillarview;
	dcpillarview = m_preview.GetWindowDC();
	
	CBrush bg;
	bg.CreateSolidBrush(RGB(255,255,255));
	CBrush * goldBrush = dcpillarview->SelectObject(&bg);
	dcpillarview->SelectObject(&bg);
	dcpillarview->Rectangle(0,15,400,400);
	dcpillarview->SelectObject(&goldBrush);
	

	
	CBrush b1;
	b1.CreateSolidBrush(m_col);
	CBrush *oldBrush = dcpillarview->SelectObject(&b1);
	dcpillarview->SelectObject(&b1);
	dcpillarview->Rectangle(20,20,20+12,300);
	dcpillarview->SelectObject(&oldBrush);

	if (m_width==1)
	{
	CBrush b1;
	b1.CreateSolidBrush(m_col);
	CBrush *oldBrush = dcpillarview->SelectObject(&b1);
	dcpillarview->SelectObject(&b1);
	dcpillarview->Rectangle(20,20,20+18,300);
	dcpillarview->SelectObject(&oldBrush);
	}
	if (m_width==2)
	{
	CBrush b1;
	b1.CreateSolidBrush(m_col);
	CBrush *oldBrush = dcpillarview->SelectObject(&b1);
	dcpillarview->SelectObject(&b1);
	dcpillarview->Rectangle(20,20,20+24,300);
	dcpillarview->SelectObject(&oldBrush);
	}

	// Do not call CDialog::OnPaint() for painting messages
}

void CPillarDlg::OnRadioTypeCylinder() 
{
	// TODO: Add your control notification handler code here
	m_type=0;
}

void CPillarDlg::OnRadioTypeCubic() 
{
	// TODO: Add your control notification handler code here
	m_type=1;
}


void CPillarDlg::OnRadioWidth1() 
{
	// TODO: Add your control notification handler code here
	m_width=0;
	OnPaint();
}

void CPillarDlg::OnRADIOWIDTH1andHalf() 
{
	// TODO: Add your control notification handler code here
	m_width=1;
	OnPaint();
}

void CPillarDlg::OnRadioWidth2() 
{
	// TODO: Add your control notification handler code here
	m_width=2;
	OnPaint();
}

void CPillarDlg::OnButtonColor() 
{
	// TODO: Add your control notification handler code here
	CColorDialog cdlg;
	if (cdlg.DoModal()==IDOK)
	{
		m_col=cdlg.GetColor();
	}
	
	OnPaint();
}

void CPillarDlg::OnOK() 
{
	// TODO: Add extra validation here
	;

	CDialog::OnOK();
}

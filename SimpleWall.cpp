// SimpleWall.cpp : implementation file
//

#include "stdafx.h"
#include "arch.h"
#include "SimpleWall.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSimpleWall dialog


CSimpleWall::CSimpleWall(CWnd* pParent /*=NULL*/)
	: CDialog(CSimpleWall::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSimpleWall)
	m_base = 0.0f;
	m_top = 0.0f;
	//}}AFX_DATA_INIT
}


void CSimpleWall::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSimpleWall)
	DDX_Control(pDX, IDC_WallPreB, m_sideBpre);
	DDX_Control(pDX, IDC_STATIC_Preview1, m_wallpreview);
	DDX_Text(pDX, IDC_Base, m_base);
	DDV_MinMaxFloat(pDX, m_base, 0.f, 120.f);
	DDX_Text(pDX, IDC_Top, m_top);
	DDV_MinMaxFloat(pDX, m_top, 0.f, 120.f);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSimpleWall, CDialog)
	//{{AFX_MSG_MAP(CSimpleWall)
	ON_BN_CLICKED(IDC_SideA, OnSideA)
	ON_BN_CLICKED(IDC_SideB, OnSideB)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_RADIO_Width, OnRADIOWidth)
	ON_BN_CLICKED(IDC_RADIO6, OnRadio6_width9)
	ON_BN_CLICKED(IDC_RADIO7, OnRadio7_width13)
	ON_BN_CLICKED(IDC_T1, OnT1)
	ON_BN_CLICKED(IDC_T2, OnT2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSimpleWall message handlers

BOOL CSimpleWall::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
 m_top=120.0f;
 m_base=0.0f;
	fixturetype=0;
    countclk=0; 
    countclk1=0;
	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	
	if (m_istextureA==TRUE)
	{
		CheckRadioButton( IDC_RADIO_COL1, IDC_RADIO_TEXTURE1, IDC_RADIO_TEXTURE1);
	
	}
	if (m_istextureA==FALSE)
		CheckRadioButton( IDC_RADIO_COL1, IDC_RADIO_TEXTURE1, IDC_RADIO_COL1);
	
	if (m_istextureB==TRUE)
		CheckRadioButton( IDC_RADIO_COL2, IDC_RADIO_TEXTURE2, IDC_RADIO_TEXTURE2);
	if (m_istextureB==FALSE)
		CheckRadioButton( IDC_RADIO_COL2, IDC_RADIO_TEXTURE2, IDC_RADIO_COL2);
		
	if (m_width==4)
	CheckRadioButton( IDC_RADIO_WALL_4, IDC_RADIO_WALL_13, IDC_RADIO_WALL_4);
	if (m_width==9)
	CheckRadioButton( IDC_RADIO_WALL_4, IDC_RADIO_WALL_13, IDC_RADIO_WALL_9);
	if (m_width==13)
	CheckRadioButton( IDC_RADIO_WALL_4, IDC_RADIO_WALL_13, IDC_RADIO_WALL_13);
	



	
	UpdateData(FALSE);
		
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSimpleWall::OnSideA() 
{
	// TODO: Add your control notification handler code here
	CColorDialog cdlg;
	if (cdlg.DoModal()==IDOK)
	{
		m_colorA=cdlg.GetColor();
		m_istextureA=FALSE;
	}
	else
	{
	if (m_istextureA)
			CheckRadioButton(IDC_SideA, IDC_T1, IDC_T1);
		else if (!m_istextureA)
			CheckRadioButton( IDC_SideA, IDC_T1, IDC_SideA);
	}
	

	OnPaint();	
}

void CSimpleWall::OnSideB() 
{
	// TODO: Add your control notification handler code here
CColorDialog cdlg;
	if (cdlg.DoModal()==IDOK)
	{
		m_colorB=cdlg.GetColor();
		m_istextureB=FALSE;
		
	}
	else
	{
		if (m_istextureB)
			CheckRadioButton( IDC_SideB, IDC_T2, IDC_T2);
		else if (!m_istextureB)
			CheckRadioButton( IDC_SideB, IDC_T2, IDC_SideB);
	}

	OnPaint();	
}

void CSimpleWall::OnPaint() 
{
// device context for painting
	
	// TODO: Add your message handler code here
	CPaintDC dc(this); // device context for painting
	
	CDC * dcwallview;
    CDC * dcwallviewB;

	dcwallview=m_wallpreview.GetWindowDC();
    dcwallviewB=m_sideBpre.GetWindowDC();

	// TODO: Add your message handler code here




	if (m_istextureA==FALSE)
	{
	CBrush b1;
	b1.CreateSolidBrush(m_colorA);
//	CBrush *oldBrush = dcview1->SelectObject(&b1);
//	dcview1->Rectangle(1,6,50,50);
	dcwallview->SelectObject(&b1);
	dcwallview->Rectangle(1,6,500,500);
//	dcview1->SelectObject(&oldBrush);
	}


	if (m_istextureB==FALSE)
	{
		CBrush b2;
	b2.CreateSolidBrush(m_colorB);
//	CBrush *oldBrush = dcview2->SelectObject(&b1);
//	dcview2->Rectangle(1,6,50,50);
//	dcview2->SelectObject(&oldBrush);
	dcwallviewB->SelectObject(&b2);
	dcwallviewB->Rectangle(1,6,500,500);

	
	}

	
	
	// Do not call CDialog::OnPaint() for painting messages*/
	


	
	// Do not call CDialog::OnPaint() for painting messages
}

void CSimpleWall::OnRADIOWidth() 
{
	// TODO: Add your control notification handler code here
	m_width=4;	
}

void CSimpleWall::OnRadio6_width9() 
{
	// TODO: Add your control notification handler code here
		m_width=9;
}

void CSimpleWall::OnRadio7_width13() 
{
	// TODO: Add your control notification handler code here
		m_width=13;
}

void CSimpleWall::OnT1() 
{
	// TODO: Add your control notification handler code here
CFileDialog dialog(TRUE, NULL, m_sFilenameA, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, 
							"Images (*.*)|*.*||");

	if (IDOK == dialog.DoModal())
	{
		m_colorA=FALSE;
		CEnBitmap bitmap;
		
		
		if (bitmap.LoadImage(dialog.GetPathName()))
		{
			BITMAP bmp;
			bitmap.GetObject(sizeof (bmp),&bmp);
			
			int width=bmp.bmWidth;
			int height=bmp.bmHeight;
			if (!(width==256 && height==256))
				AfxMessageBox("Select a bitmap of 128 x 128 pixels");
			else
			{
				m_sFilenameA = dialog.GetPathName();
				m_istextureA=TRUE;
			}
		}

						m_sFilenameA = dialog.GetPathName();
				m_istextureA=TRUE;

		if (m_istextureA)
			CheckRadioButton( IDC_SideA, IDC_T1, IDC_T1);
		else if (!m_istextureA)
			CheckRadioButton( IDC_SideA, IDC_T1, IDC_SideA);
	
	}
	else 
	{
	if (m_istextureA)
			CheckRadioButton( IDC_SideA, IDC_T1, IDC_T1);
		else if (!m_istextureA)
			CheckRadioButton( IDC_SideA, IDC_T1, IDC_SideA);
	}	
}

void CSimpleWall::OnT2() 
{
	// TODO: Add your control notification handler code here
CFileDialog dialog(TRUE, NULL, m_sFilenameB, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, 
							"Images (*.*)|*.*||");

	if (IDOK == dialog.DoModal())
	{
		m_colorB=FALSE;
		CEnBitmap bitmap;
		
		
		if (bitmap.LoadImage(dialog.GetPathName()))
		{
			BITMAP bmp;
			bitmap.GetObject(sizeof (bmp),&bmp);
			
			int width=bmp.bmWidth;
			int height=bmp.bmHeight;
			if (!(width==256 && height==256))
				AfxMessageBox("Select a bitmap of 128 x 128 pixels");
			else
			{
				m_sFilenameB= dialog.GetPathName();
				m_istextureB=TRUE;
			}
		}
		m_sFilenameB= dialog.GetPathName();
	    m_istextureB=TRUE;
	
	if (m_istextureB)
			CheckRadioButton( IDC_SideB, IDC_T2, IDC_T2);
		else if (!m_istextureB)
			CheckRadioButton( IDC_SideB, IDC_T2, IDC_SideB);
	
	}
	else 
	{
	if (m_istextureB)
			CheckRadioButton( IDC_SideB, IDC_T2, IDC_T2);
		else if (!m_istextureB)
			CheckRadioButton( IDC_SideB, IDC_T2, IDC_SideB);
	}
	OnPaint();		
}

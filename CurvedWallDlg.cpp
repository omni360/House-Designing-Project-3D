// CurvedWallDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Arch.h"
#include "CurvedWallDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCurvedWallDlg dialog


CCurvedWallDlg::CCurvedWallDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCurvedWallDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCurvedWallDlg)
	
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	
}


void CCurvedWallDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCurvedWallDlg)
	DDX_Control(pDX, IDC_STATIC_S2, m_views2);
	DDX_Control(pDX, IDC_STATIC_S1, m_views1);
	DDX_Control(pDX, IDC_STATIC_Preview, m_wallpreview);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCurvedWallDlg, CDialog)
	//{{AFX_MSG_MAP(CCurvedWallDlg)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_RADIO_COL1, OnRadioCol1)
	ON_BN_CLICKED(IDC_RADIO_TEXTURE1, OnRadioTexture1)
	ON_BN_CLICKED(IDC_RADIO_COL2, OnRadioCol2)
	ON_BN_CLICKED(IDC_RADIO_TEXTURE2, OnRadioTexture2)
	ON_BN_CLICKED(IDC_RADIO_WALL_4, OnRadioWall4)
	ON_BN_CLICKED(IDC_RADIO_WALL_9, OnRadioWall9)
	ON_BN_CLICKED(IDC_RADIO_WALL_13, OnRadioWall13)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCurvedWallDlg message handlers

BOOL CCurvedWallDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	if (m_istextureA==TRUE)
		CheckRadioButton( IDC_RADIO_COL1, IDC_RADIO_TEXTURE1, IDC_RADIO_TEXTURE1);
	
	else if (m_istextureA==FALSE)
		CheckRadioButton( IDC_RADIO_COL1, IDC_RADIO_TEXTURE1, IDC_RADIO_COL1);
	
	if (m_istextureB==TRUE)
		CheckRadioButton( IDC_RADIO_COL2, IDC_RADIO_TEXTURE2, IDC_RADIO_TEXTURE2);
	else if (m_istextureB==FALSE)
		CheckRadioButton( IDC_RADIO_COL2, IDC_RADIO_TEXTURE2, IDC_RADIO_COL2);
		
	if (m_width==9)
	CheckRadioButton( IDC_RADIO_WALL_4, IDC_RADIO_WALL_13, IDC_RADIO_WALL_9);
	if (m_width==13)
	CheckRadioButton( IDC_RADIO_WALL_4, IDC_RADIO_WALL_13, IDC_RADIO_WALL_13);
	if (m_width==4)
	CheckRadioButton( IDC_RADIO_WALL_4, IDC_RADIO_WALL_13, IDC_RADIO_WALL_4);


	//UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CCurvedWallDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	
	

	CDC * dcview1;
	CDC * dcview2;

	dcview1=m_views1.GetWindowDC();
	dcview2=m_views2.GetWindowDC();

	if (!m_istextureA)
	{
	CBrush b1;
	b1.CreateSolidBrush(m_colorA);
	CBrush *oldBrush = dcview1->SelectObject(&b1);
	dcview1->Rectangle(1,6,500,500);
	dcview1->SelectObject(&oldBrush);
	}
	else 
	{
	
	CEnBitmap bitmap;
		bitmap.DeleteObject();
		bitmap.LoadImage(m_sFilenameA);
		if (bitmap.GetSafeHandle())
		{
			CDC dcMem;
	
		
			if (dcMem.CreateCompatibleDC(dcview1))
			{
			
			CBitmap* pOldBM = dcMem.SelectObject(&bitmap);
			BITMAP BM;

			bitmap.GetBitmap(&BM);

			dcview1->BitBlt(0, 0, BM.bmWidth, BM.bmHeight, &dcMem, -1, -6, SRCCOPY);

			dcMem.SelectObject(pOldBM);
			}
		}
	}

	if (!m_istextureB)
	{
	CBrush b1;
	b1.CreateSolidBrush(m_colorB);
	CBrush *oldBrush = dcview2->SelectObject(&b1);
	dcview2->Rectangle(1,6,500,500);
	dcview2->SelectObject(&oldBrush);
	}

	else
	{
		CEnBitmap bitmap;
		bitmap.DeleteObject();
		bitmap.LoadImage(m_sFilenameB);
		if (bitmap.GetSafeHandle())
		{
			CDC dcMem;
	
		
			if (dcMem.CreateCompatibleDC(dcview2))
			{
			
			CBitmap* pOldBM = dcMem.SelectObject(&bitmap);
			BITMAP BM;

			bitmap.GetBitmap(&BM);

			dcview2->BitBlt(0, 0, BM.bmWidth, BM.bmHeight, &dcMem, -1, -6, SRCCOPY);

			dcMem.SelectObject(pOldBM);
			}
		}
	}
	// Do not call CDialog::OnPaint() for painting messages
}

void CCurvedWallDlg::OnOK() 
{
	// TODO: Add extra validation here
	CDialog::OnOK();
}

void CCurvedWallDlg::OnRadioCol1() 
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
			CheckRadioButton( IDC_RADIO_COL1, IDC_RADIO_TEXTURE1, IDC_RADIO_TEXTURE1);
		else if (!m_istextureB)
			CheckRadioButton( IDC_RADIO_COL1, IDC_RADIO_TEXTURE1, IDC_RADIO_COL1);
	}
	OnPaint();
}

void CCurvedWallDlg::OnRadioTexture1() 
{
	// TODO: Add your control notification handler code here
	CFileDialog dialog(TRUE, NULL, m_sFilenameA, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, 
							"Images (*.bmp)|*.bmp||");

	if (IDOK == dialog.DoModal())
	{
		
		CEnBitmap bitmap;
		
		if (bitmap.LoadImage(dialog.GetPathName()))
		{
			BITMAP bmp;
			bitmap.GetObject(sizeof (bmp),&bmp);
			int width=bmp.bmWidth;
			int height=bmp.bmHeight;

				if (!(width==128 && height==128))
					AfxMessageBox("Select a bitmap of 128 x 128 pixels");
				else
				{
				m_sFilenameA = dialog.GetPathName();
				m_istextureA=TRUE; 
				}
			}
		if (m_istextureA)
			CheckRadioButton( IDC_RADIO_COL1, IDC_RADIO_TEXTURE1, IDC_RADIO_TEXTURE1);
		else if (!m_istextureA)
			CheckRadioButton( IDC_RADIO_COL1, IDC_RADIO_TEXTURE1, IDC_RADIO_COL1);
	}
	else 
	{
		if (m_istextureA)
			CheckRadioButton( IDC_RADIO_COL1, IDC_RADIO_TEXTURE1, IDC_RADIO_TEXTURE1);
		else if (!m_istextureA)
			CheckRadioButton( IDC_RADIO_COL1, IDC_RADIO_TEXTURE1, IDC_RADIO_COL1);
	
	}
	OnPaint();
}

void CCurvedWallDlg::OnRadioCol2() 
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
			CheckRadioButton( IDC_RADIO_COL2, IDC_RADIO_TEXTURE2, IDC_RADIO_TEXTURE2);
		else if (!m_istextureB)
			CheckRadioButton( IDC_RADIO_COL2, IDC_RADIO_TEXTURE2, IDC_RADIO_COL2);
	}
	OnPaint();
}

void CCurvedWallDlg::OnRadioTexture2() 
{
	// TODO: Add your control notification handler code here
CFileDialog dialog(TRUE, NULL, m_sFilenameB, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, 
							"Images (*.bmp)|*.bmp||");

	if (IDOK == dialog.DoModal())
	{
		
		CEnBitmap bitmap;
		
		
		if (bitmap.LoadImage(dialog.GetPathName()))
		{
			BITMAP bmp;
			bitmap.GetObject(sizeof (bmp),&bmp);
			
			int width=bmp.bmWidth;
			int height=bmp.bmHeight;
			if (!(width==128 && height==128))
				AfxMessageBox("Select a bitmap of 128 x 128 pixels");
			else
			{
				m_sFilenameB = dialog.GetPathName();
				m_istextureB=TRUE;
			}
		}
	if (m_istextureB)
			CheckRadioButton( IDC_RADIO_COL2, IDC_RADIO_TEXTURE2, IDC_RADIO_TEXTURE2);
		else if (!m_istextureB)
			CheckRadioButton( IDC_RADIO_COL2, IDC_RADIO_TEXTURE2, IDC_RADIO_COL2);
	
	}
	else 
	{
		if (m_istextureB)
			CheckRadioButton( IDC_RADIO_COL2, IDC_RADIO_TEXTURE2, IDC_RADIO_TEXTURE2);
		else if (!m_istextureB)
			CheckRadioButton( IDC_RADIO_COL2, IDC_RADIO_TEXTURE2, IDC_RADIO_COL2);
	}
	OnPaint();	
}

void CCurvedWallDlg::OnRadioWall4() 
{
	// TODO: Add your control notification handler code here
	m_width=4;
}

void CCurvedWallDlg::OnRadioWall9() 
{
	// TODO: Add your control notification handler code here
	m_width=9;
}

void CCurvedWallDlg::OnRadioWall13() 
{
	// TODO: Add your control notification handler code here
	m_width=13;
}

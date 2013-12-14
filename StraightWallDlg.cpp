// StraightWallDlg.cpp : implementation file
//

#include "stdafx.h"
//#include "WallProp.h"
#include "StraightWallDlg.h"
#include "resource.h"
#include "Wall.h"
#include "ArchDoc.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;


//CArchDoc* CStraightWallDlg::GetDocument()
//{
//ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CArchDoc)));
//	return (CArchDoc*)m_pDocument;
//}
#endif

/////////////////////////////////////////////////////////////////////////////
// CStraightWallDlg dialog


CStraightWallDlg::CStraightWallDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CStraightWallDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CStraightWallDlg)
	m_basepoint = 0.0f;
	m_wtoppoint = 0.0f;
	//}}AFX_DATA_INIT
//		m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}


void CStraightWallDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStraightWallDlg)
	DDX_Control(pDX, IDC_BTN_WINDOW_CLR, m_btnwindowclr);
	DDX_Control(pDX, IDC_BTN_DOOR_CLR, m_btndoorclr);
	DDX_Control(pDX, IDC_STATIC_Preview, m_wallview);
	DDX_Control(pDX, IDC_STATIC_S2, m_views2);
	DDX_Control(pDX, IDC_STATIC_S1, m_views1);
	DDX_Check(pDX, IDC_CHECK_DOOR, m_checkdoor);
	DDX_Check(pDX, IDC_CHECK_WINDOW, m_checkwindow);
	DDX_Text(pDX, IDC_BASE_POINT, m_basepoint);
	DDV_MinMaxFloat(pDX, m_basepoint, 0.f, 120.f);
	DDX_Text(pDX, IDC_TOP_POINT, m_wtoppoint);
	DDV_MinMaxFloat(pDX, m_wtoppoint, 0.f, 120.f);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CStraightWallDlg, CDialog)
	//{{AFX_MSG_MAP(CStraightWallDlg)
	ON_BN_CLICKED(IDC_RADIO_TEXTURE1, OnRadioTexture1)
	ON_BN_CLICKED(IDC_RADIO_WALL_4, OnRadioWall4)
	ON_BN_CLICKED(IDC_RADIO_WALL_9, OnRadioWall9)
	ON_BN_CLICKED(IDC_RADIO_WALL_13, OnRadioWall13)
	ON_BN_CLICKED(IDC_RADIO_COL1, OnRadioCol1)
	ON_BN_CLICKED(IDC_RADIO_COL2, OnRadioCol2)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_RADIO_TEXTURE2, OnRadioTexture2)
	ON_BN_CLICKED(IDC_RADIO_DOOR_2x7, OnRADIODOOR2x7)
	ON_BN_CLICKED(IDC_RADIO_DOOR_3x7, OnRADIODOOR3x7)
	ON_BN_CLICKED(IDC_RADIO_DOOR_4x7, OnRADIODOOR4x7)
	ON_BN_CLICKED(IDC_RADIO_WINDOW_2x3, OnRADIOWINDOW2x3)
	ON_BN_CLICKED(IDC_RADIO_WINDOW_3x3, OnRADIOWINDOW3x3)
	ON_BN_CLICKED(IDC_RADIO_WINDOW_3x4, OnRADIOWINDOW3x4)
	ON_BN_CLICKED(IDC_RADIO_WINDOW_4x4, OnRADIOWINDOW4x4)
	ON_BN_CLICKED(IDC_CHECK_DOOR, OnCheckDoor)
	ON_BN_CLICKED(IDC_CHECK_WINDOW, OnCheckWindow)
	ON_BN_CLICKED(IDC_BTN_DOOR_CLR, OnBtnDoorClr)
	ON_BN_CLICKED(IDC_BTN_WINDOW_CLR, OnBtnWindowClr)
	ON_BN_CLICKED(IDC_SELECT_DOOR, OnSelectDoor)
	ON_BN_CLICKED(IDC_SELECT_WINDOW, OnSelectWindow)
	ON_BN_CLICKED(IDC_BTN_MOVE_RIGHT, OnBtnMoveRight)
	ON_BN_CLICKED(IDC_BTN_MOVE_LEFT, OnBtnMoveLeft)
	ON_EN_CHANGE(IDC_BASE_POINT, OnChangeBasePoint)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStraightWallDlg message handlers








void CStraightWallDlg::OnRadioTexture1() 
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

}





BOOL CStraightWallDlg::OnInitDialog()
{
	
	CDialog::OnInitDialog();
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
	


	if (m_iswindow==TRUE)
	{
	
		m_btnwindowclr.EnableWindow(TRUE);
		m_checkwindow=TRUE;
		if (m_windowtype==1)
		{
			CheckRadioButton( IDC_RADIO_WINDOW_2x3, IDC_RADIO_WINDOW_4x4, IDC_RADIO_WINDOW_2x3);
			m_windowlength=24;
		}
		else if (m_windowtype==2)
		{
			CheckRadioButton( IDC_RADIO_WINDOW_2x3, IDC_RADIO_WINDOW_4x4, IDC_RADIO_WINDOW_3x3);
			m_windowlength=36;
		}
		else if (m_windowtype==3)
		{
			CheckRadioButton( IDC_RADIO_WINDOW_2x3, IDC_RADIO_WINDOW_4x4, IDC_RADIO_WINDOW_3x4);
			m_windowlength=36;
		}
		else if (m_windowtype==4)
		{
			CheckRadioButton( IDC_RADIO_WINDOW_2x3, IDC_RADIO_WINDOW_4x4, IDC_RADIO_WINDOW_4x4);
			m_windowlength=48;
		}
	

	}
	
	else if (m_iswindow==FALSE)
	{
		m_btnwindowclr.EnableWindow(FALSE);
		m_checkwindow=FALSE;
	
		m_windowlength=0;
	
	}
		

	if (m_isdoor==TRUE)
	{
		
		m_btndoorclr.EnableWindow(TRUE);
		
		m_checkdoor=TRUE;
	
		if (m_doortype==1)
		{
			CheckRadioButton( IDC_RADIO_DOOR_2x7, IDC_RADIO_DOOR_4x7, IDC_RADIO_DOOR_2x7);
			m_doorlength=24;
		}
		else if (m_doortype==2)
		{
			CheckRadioButton( IDC_RADIO_DOOR_2x7, IDC_RADIO_DOOR_4x7, IDC_RADIO_DOOR_3x7);
			m_doorlength=36;
		}
		else if (m_doortype==3)
		{
			CheckRadioButton( IDC_RADIO_DOOR_2x7, IDC_RADIO_DOOR_4x7, IDC_RADIO_DOOR_4x7);
			m_doorlength=48;
		}
	
		
		
	}
	else if(m_isdoor==FALSE)
	{
		m_btndoorclr.EnableWindow(FALSE);
		m_checkdoor=FALSE;
	
		m_doorlength=0;
	}
	


	m_fixtdoor=&m_doorframe;

	
	UpdateData(FALSE);
	
		
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CStraightWallDlg::OnRadioWall4() 
{
	// TODO: Add your control notification handler code here
	m_width=4;

}

void CStraightWallDlg::OnRadioWall9() 
{
	// TODO: Add your control notification handler code here
	m_width=9;

}

void CStraightWallDlg::OnRadioWall13() 
{
	// TODO: Add your control notification handler code here
	m_width=13;

}






void CStraightWallDlg::OnRadioCol1() 
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
		else if (!m_istextureA)
			CheckRadioButton( IDC_RADIO_COL1, IDC_RADIO_TEXTURE1, IDC_RADIO_COL1);
	}
	

	OnPaint();
}

void CStraightWallDlg::OnRadioCol2() 
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


void CStraightWallDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	CDC * dcwallview;
	dcwallview=m_wallview.GetWindowDC();

	// TODO: Add your message handler code here



	CDC * dcview1;
	CDC * dcview2;

	dcview1=m_views1.GetWindowDC();
	dcview2=m_views2.GetWindowDC();

	if (m_istextureA==FALSE)
	{
	CBrush b1;
	b1.CreateSolidBrush(m_colorA);
	CBrush *oldBrush = dcview1->SelectObject(&b1);
	dcview1->Rectangle(1,6,50,50);
	dcwallview->SelectObject(&b1);
	dcwallview->Rectangle(1,6,500,500);
	dcview1->SelectObject(&oldBrush);
	}
	else if (m_istextureA==TRUE)
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
			dcwallview->Rectangle(1,6,500,500);

			dcMem.SelectObject(pOldBM);
			}
		}
	}

	if (m_istextureB==FALSE)
	{
		CBrush b1;
	b1.CreateSolidBrush(m_colorB);
	CBrush *oldBrush = dcview2->SelectObject(&b1);
	dcview2->Rectangle(1,6,50,50);
	dcview2->SelectObject(&oldBrush);
	}

	else if (m_istextureB==TRUE)
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
	
	// Do not call CDialog::OnPaint() for painting messages*/
	
	if (m_isdoor==TRUE)
	{
	CBrush b1;
	b1.CreateSolidBrush(m_doorcolor);
	CBrush *oldBrush = dcwallview->SelectObject(&b1);
	dcwallview->SelectObject(&b1);
	dcwallview->Rectangle(m_doorframe);
	/*	if (m_doortype==3)
		{
		m_pt1=m_doorframe.TopLeft();
		m_pt2=m_doorframe.BottomRight();
		int x = (m_pt2.x+m_pt1.x)/2;
		dcwallview->MoveTo(x,m_pt1.y);
		dcwallview->LineTo(x,m_pt2.y);
		}*/
	dcview1->SelectObject(&oldBrush);
	}

	if (m_iswindow)
	{
	CBrush b1;
	b1.CreateSolidBrush(m_windowcolor);
	CBrush *oldBrush = dcwallview->SelectObject(&b1);
	dcwallview->SelectObject(&b1);
	dcwallview->Rectangle(m_windowframe);
		if (m_windowtype==1||m_windowtype==2)
		{
		m_pt1=m_windowframe.TopLeft();
		m_pt2=m_windowframe.BottomRight();
		int x = (m_pt2.x+m_pt1.x)/2;
		dcwallview->MoveTo(x,m_pt1.y);
		dcwallview->LineTo(x,m_pt2.y);
		} 
		if (m_windowtype==3||m_windowtype==4)
		{
		m_pt1=m_windowframe.TopLeft();
		m_pt2=m_windowframe.BottomRight();
		int diff = (m_pt2.x-m_pt1.x)/3;
		int x1 = m_pt1.x+diff;
		int x2 =m_pt1.x+(diff*2);
		dcwallview->MoveTo(x1,m_pt1.y);
		dcwallview->LineTo(x1,m_pt2.y);
		dcwallview->MoveTo(x2,m_pt1.y);
		dcwallview->LineTo(x2,m_pt2.y);

		} 
	dcview1->SelectObject(&oldBrush);
	}

} 

void CStraightWallDlg::OnRadioTexture2() 
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





void CStraightWallDlg::OnRADIODOOR2x7() 
{
	// TODO: Add your control notification handler code here
	
	
	m_doorframe.SetRect(2,46,24,135);//start from 20 end at 2o+24, start from 46, end at 46+84);
    m_pt1 = m_doorframe.TopLeft();
	m_pt2 = m_doorframe.BottomRight();
	m_pt2.x= m_pt1.x+24;
	m_doorframe.SetRect(m_pt1, m_pt2);
	m_doortype=1;
	CheckRadioButton( IDC_RADIO_DOOR_2x7, IDC_RADIO_DOOR_4x7, IDC_RADIO_DOOR_2x7);
	m_doorlength=24;
//	leftdoorpoint=m_pt1;
//	rightdoorpoint=m_pt2;	
	OnPaint();


}

void CStraightWallDlg::OnRADIODOOR3x7() 
{
	// TODO: Add your control notification handler code here
	m_doorframe.SetRect(2,46,24,135);//start from 20 end at 2o+24, start from 46, end at 46+84);
	m_pt1 = m_doorframe.TopLeft();
	m_pt2 = m_doorframe.BottomRight();
	m_pt2.x= m_pt1.x+37;
	m_doorframe.SetRect(m_pt1, m_pt2);
	m_doortype=2;
	m_doorlength=37;
	OnPaint();
}

void CStraightWallDlg::OnRADIODOOR4x7() 
{
	// TODO: Add your control notification handler code here
	m_doorframe.SetRect(2,46,24,135);//start from 20 end at 2o+24, start from 46, end at 46+84);
	m_pt1 = m_doorframe.TopLeft();
	m_pt2 = m_doorframe.BottomRight();
	m_pt2.x= m_pt1.x+47;
	m_doorframe.SetRect(m_pt1, m_pt2);
	m_doortype=3;
	m_doorlength=47;
	OnPaint();
}

void CStraightWallDlg::OnRADIOWINDOW2x3() 
{
	// TODO: Add your control notification handler code here
	//m_windowframe.SetRect(100,58,124,94);
	m_windowframe.SetRect(2,46,24,135);
	m_pt1 = m_windowframe.TopLeft();
	m_pt2 = m_windowframe.BottomRight();
	m_pt2.x= m_pt1.x+24;
	m_pt2.y=m_pt1.y+36;
	m_windowframe.SetRect(m_pt1, m_pt2);
	m_windowtype=1;
	m_windowlength=24;
	CheckRadioButton( IDC_RADIO_WINDOW_2x3, IDC_RADIO_WINDOW_4x4, IDC_RADIO_WINDOW_2x3);
	OnPaint();
}

void CStraightWallDlg::OnRADIOWINDOW3x3() 
{
	// TODO: Add your control notification handler code here
	//m_windowframe.SetRect(100,58,124,94);
		m_windowframe.SetRect(2,46,24,135);
	m_pt1 = m_windowframe.TopLeft();
	m_pt2 = m_windowframe.BottomRight();
	m_pt2.x= m_pt1.x+37;
	m_pt2.y=m_pt1.y+36;
	m_windowframe.SetRect(m_pt1, m_pt2);
	m_windowtype=2;
	m_windowlength=37;
	OnPaint();
	
}

void CStraightWallDlg::OnRADIOWINDOW3x4() 
{
	// TODO: Add your control notification handler code here
	//m_windowframe.SetRect(100,58,124,94);
	m_windowframe.SetRect(2,46,24,135);
	m_pt1 = m_windowframe.TopLeft();
	m_pt2 = m_windowframe.BottomRight();
	m_pt2.x= m_pt1.x+47;
	m_pt2.y=m_pt1.y+36;
	m_windowframe.SetRect(m_pt1, m_pt2);
	m_windowtype=3;
	m_windowlength=37;
	OnPaint();
}



void CStraightWallDlg::OnRADIOWINDOW4x4() 
{
	// TODO: Add your control notification handler code here
	//m_windowframe.SetRect(100,58,124,94);
		m_windowframe.SetRect(2,46,24,135);
	m_pt1 = m_windowframe.TopLeft();
	m_pt2 = m_windowframe.BottomRight();
	m_pt2.x= m_pt1.x+47;
	m_pt2.y=m_pt1.y+48;
	m_windowframe.SetRect(m_pt1, m_pt2);
	m_windowtype=4;
	m_windowlength=37;
	OnPaint();
}






void CStraightWallDlg::OnCheckDoor() 
{
	// TODO: Add your control notification handler code here
if (m_isdoor==FALSE)
	{
		m_flag=1;
	    m_isdoor=TRUE ;
		m_btndoorclr.EnableWindow(TRUE);
		CheckRadioButton(IDC_SELECT_DOOR, IDC_SELECT_WINDOW, IDC_SELECT_DOOR);
		OnSelectDoor();
		OnRADIODOOR2x7() ;
	}
	else if (m_isdoor==TRUE)
	{
		m_flag=0;
		m_isdoor=FALSE;
		m_btndoorclr.EnableWindow(FALSE);
	}
OnPaint();
}

void CStraightWallDlg::OnCheckWindow() 
{
	// TODO: Add your control notification handler code here
	if (m_iswindow==FALSE)
	{
		m_flag1=1;
		m_iswindow=TRUE ;
		m_btnwindowclr.EnableWindow(TRUE);
		CheckRadioButton(IDC_SELECT_DOOR, IDC_SELECT_WINDOW, IDC_SELECT_WINDOW);
		OnSelectWindow();
		OnRADIOWINDOW2x3() ;
	}
	else if (m_iswindow==TRUE)
	{
		m_flag1=0;
		m_iswindow=FALSE;
		m_btnwindowclr.EnableWindow(FALSE);
	}
	OnPaint();
}

void CStraightWallDlg::OnBtnDoorClr() 
{
	// TODO: Add your control notification handler code here
CColorDialog cdlg;
	if (cdlg.DoModal()==IDOK)
	{
		m_doorcolor=cdlg.GetColor();
	}
	OnPaint();
	
}

void CStraightWallDlg::OnBtnWindowClr() 
{
	// TODO: Add your control notification handler code here
	CColorDialog cdlg;
	if (cdlg.DoModal()==IDOK)
	{
	m_windowcolor= cdlg.GetColor();
		}

	OnPaint();
	
}


void CStraightWallDlg::OnSelectDoor() 
{
	// TODO: Add your control notification handler code here
	m_fixtdoor=&m_doorframe;
    fixturetype=1;
}

void CStraightWallDlg::OnSelectWindow() 
{
	// TODO: Add your control notification handler code here
	m_fixtwindow=&m_windowframe;
    fixturetype=2;  
}

void CStraightWallDlg::OnBtnMoveRight() 
{
	// TODO: Add your control notification handler code here
//CWall* w1;
//CWall* pWall = (CWall* )
if(fixturetype==1)
{
	dpoint= m_fixtdoor->BottomRight();

    if(dpoint.x==26 || dpoint.x==39 || dpoint.x==49)//||dpoint.x==124||dpoint.x==136||dpoint.x==148)
       countclk=0;
    else
		countclk=countsave;

	if (dpoint.x<200)
	{	
		//inc=inc-((P2.x-P1.x)/50);
	   
        m_fixtdoor->OffsetRect(3,0);
	  
	
	}
	//else
		
	 countclk++;
	 countsave=countclk;
	 OnPaint();
}
else
if(fixturetype==2)
{
  wpoint= m_fixtwindow->BottomRight();

    if(wpoint.x==26 || wpoint.x==39 || wpoint.x==49)//||dpoint.x==124||dpoint.x==136||dpoint.x==148)
       countclk1=0;
    else
		countclk1=countsave1;

	if (wpoint.x<200)
	{	
		//inc=inc-((P2.x-P1.x)/50);
	   
        m_fixtwindow->OffsetRect(3,0);
	  
	
	}
	//else
		
	 countclk1++;
	 countsave1=countclk1;
	 OnPaint();
}		
}

void CStraightWallDlg::OnBtnMoveLeft() 
{
	// TODO: Add your control notification handler code here
//	CPoint p;
	if(fixturetype==1)
	{
	dpoint=m_fixtdoor->TopLeft();
	if(dpoint.x==2)
		countclk=0;
	else
		countclk=countsave;
	if (dpoint.x>3)
	{
		
		//inc=inc+((P2.x-P1.x)/50);
		m_fixtdoor->OffsetRect(-3,0);
	   
	    
	}
	 countclk--;
	 countsave=countclk;
	OnPaint();
}
else
if(fixturetype==2)
	{
	wpoint=m_fixtwindow->TopLeft();
	if(wpoint.x==2)
		countclk1=0;
	else
		countclk1=countsave1;
	if (wpoint.x>3)
	{
		
		//inc=inc+((P2.x-P1.x)/50);
		m_fixtwindow->OffsetRect(-3,0);
	   
	    
	}
	 countclk1--;
	 countsave1=countclk1;
	OnPaint();
}

}
void CStraightWallDlg::OnOK() 
{
//	CWall *wall;
	//CArchDoc* pDoc=(CArchDoc*) GetDocument();
//	ASSERT_VALID(pDoc);
	m_connectedpointdoor=m_doorframe.TopLeft();
	m_bottomRight=m_doorframe.BottomRight();
//	m_bottomLeft=m_doorframe.BottomLeft();
	m_connectedpointwindow=m_windowframe.TopLeft();
	m_bottompointwindow=m_windowframe.BottomRight();
	m_connectedpointdoor.y=36;
	m_connectedpointwindow.y=48;
	leftdoorpoint=m_connectedpointdoor;
	rightdoorpoint=m_bottomRight;	
    
	if (!Overlapping())
	{
		if (!OverSizing())
		{
			CDialog::OnOK();
		}
	}

}




BOOL CStraightWallDlg::Overlapping()
{
	if (m_isdoor ==TRUE && m_iswindow==TRUE)
	{

	CRect IsOverlapping;

		if (IntersectRect(IsOverlapping, m_doorframe, m_windowframe))
		
			{
				AfxMessageBox("Fixtures are overlapping with each other");
				return TRUE;
			}
	}
 return FALSE;
}

BOOL CStraightWallDlg::OverSizing()
{
	if (m_isdoor==TRUE && m_iswindow==TRUE)
	{
		if (m_walllength<=m_doorlength+m_windowlength+18)
		{
			AfxMessageBox("Size of Door and Window is greater than of wall");
			return TRUE;
		}
	}
	
	else if (m_isdoor==TRUE)
	{
		if (m_walllength<=m_doorlength+12)
		{
			AfxMessageBox("Size of Door is greater than of wall");
			return TRUE;
		}
	}
	else if (m_iswindow==TRUE)
	{
		if (m_walllength<=m_windowlength+12)
		{
			AfxMessageBox("Size of Window is greater than of wall");
			return TRUE;
		}
	}
	return FALSE;
}

void CStraightWallDlg::SetValue()
{
//P3=m_pt1;
//P4=m_pt2;

}





void CStraightWallDlg::OnChangeBasePoint() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
    	
     

}

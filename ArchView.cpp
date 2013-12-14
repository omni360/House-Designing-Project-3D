// ArchView.cpp : implementation of the CArchView class
//

#include "stdafx.h"
#include "Arch.h"

#include "ArchDoc.h"
#include "ArchView.h"
#include "vfd.h"
#include "ArchCons.h"
#include "Wall.h"
#include "ArchDraw.h"
#include "MainFrm.h"
#include "math.h"
#include "ChairObject.h"
#include "tabletype.h"
#include "sofatype.h"
#include "chairtype.h"
#include "FixtureWall.h"
#include <gl\gl.h>										// Header File For The OpenGL32 Library
#include <gl\glu.h>	
#include <gl\glut.h>		

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CArchView

IMPLEMENT_DYNCREATE(CArchView, CScrollView)

BEGIN_MESSAGE_MAP(CArchView, CScrollView)
	//{{AFX_MSG_MAP(CArchView)
	ON_WM_LBUTTONDOWN()
	ON_WM_SETCURSOR()
	ON_WM_MOUSEMOVE()
	ON_WM_ERASEBKGND()
	ON_COMMAND(ID_VIEW_FLOOR, OnViewFloor)
	ON_WM_LBUTTONDBLCLK()
	ON_COMMAND(ID_VIEW_VIEWFLOOR, OnViewconstructedfloor)
	ON_UPDATE_COMMAND_UI(ID_VIEW_VIEWFLOOR, OnUpdateConstructedViewfloor)
	ON_COMMAND(ID_VIEW_NEWFLOOR, OnBuildNewfloor)
	ON_UPDATE_COMMAND_UI(ID_VIEW_NEWFLOOR, OnUpdateNewfloor)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CScrollView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CArchView construction/destruction

CArchView::CArchView()
{
	// TODO: add construction code here

	m_ptCounter = 0;
}

CArchView::~CArchView()
{
	if(m_CCursor) DestroyCursor(m_CCursor);
}

BOOL CArchView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CScrollView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CArchView drawing

void CArchView::OnDraw(CDC* pDC)
{
	CArchDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	CBuildingElement *pBElement;
	CFloor *floor;
	floor = pDoc->m_CurrentFloor;
	
	ASSERT_VALID(floor);
	floor->DrawBase(pDC);
	
	for (int i=0;i<floor->GetElementCount();i++)
	{
		pBElement = floor->GetElement(i); 
		pBElement->Draw(pDC);
	}
	if (pDoc->m_BESelected)
		pDoc->m_BESelected->Draw(pDC, TRUE);

	//m_walltempc.Draw(pDC);

/////////////////To display a bitmap//////////////////////////////////////





////////////////////////




}

void CArchView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: calculate the total size of this view
	sizeTotal.cx = sizeTotal.cy = 100;
	SetScrollSizes(MM_TEXT, sizeTotal);
//	m_testPillar.DoModal();
//	CClientDC dc(this);
//	m_curConstruction  = LoadCursorFromFile("res\\hcross.cur"); 
//	m_curConstruction
//	SetMapMode(NULL,MM_ANISOTROPIC);
//	SetWindowExtEx(NULL,1,-1,&sizeTotal);
//	SetWindowOrgEx(NULL,1,-1,p);
	//CFrameWnd* Frm = Get
	//CView *AV = GetActiveView();
}

/////////////////////////////////////////////////////////////////////////////
// CArchView printing

BOOL CArchView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CArchView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CArchView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CArchView diagnostics

#ifdef _DEBUG
void CArchView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CArchView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CArchDoc* CArchView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CArchDoc)));
	return (CArchDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CArchView message handlers

void CArchView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CArchDoc* pDoc=GetDocument();
	ASSERT_VALID(pDoc);
	CClientDC dc(this);
	if (m_PillarTemp.HitTest(point))
		m_PillarTemp.Draw(&dc,TRUE);
	if (m_wallTemp.HitTest(point))
		m_wallTemp.Draw(&dc,TRUE);
	if (m_walltempc.HitTest(point))
		m_walltempc.Draw(&dc, TRUE);
    if (m_fixturewallTemp.HitTest(point))
		m_fixturewallTemp.Draw(&dc,TRUE);
	
	if(m_chairTemp.HitTest(point)) 
	{
	
		m_chairTemp.Draw(&dc,TRUE);
		
	}
	
//construction mode begin here
	switch (pDoc->m_AppMode)
	{
	case MODE_ADJUSTMENT:
			switch(pDoc->m_AppTool)
			{
			case ADJUSTMENT_SELECT:
				pDoc->m_BESelected=SelecteElement(point);
				if (pDoc->m_BESelected)
				{
					CClientDC dc(this);
					OnPrepareDC (&dc);
					OnDraw(&dc); 
					pDoc->m_BESelected->Draw(&dc,TRUE); 
				}
				
			break;
			}
			break;
	case MODE_CONSTRUCTION:
		//::SetCursor(LoadCursor(NULL,MAKEINTRESOURCE(IDC_CROSS)));
			switch(pDoc->m_AppTool)
			{
			case CONSTRUCT_WALL:
				ConstructWall(nFlags,point,WM_LBUTTONDOWN);
				//pDoc->m_CurrentFloor->AddElement(
				break;
			case CONSTRUCT_CWALL:
				ConstructCWall(nFlags,point,WM_LBUTTONDOWN);
				break;
			case CONSTRUCT_PILLAR:
				ConstructPillar(nFlags,point,WM_LBUTTONDOWN);
				break;
			case CONSTRUCT_STAIRS:
				ConstructStairs(nFlags,point,WM_LBUTTONDOWN);
				break;
			case CONSTRUCT_CEILPLANE:
				ConstructCCeiling(nFlags,point,WM_LBUTTONDOWN);
				break;
            case CONSTRUCT_CHAIROBJ:
				ConstructChairObj(nFlags,point,WM_LBUTTONDOWN);
				break;
			case CONSTRUCT_TABLEOBJ:
				ConstructTableObj(nFlags,point,WM_LBUTTONDOWN);
				break;
			case CONSTRUCT_SOFAOBJ:
				ConstructSofaObj(nFlags,point,WM_LBUTTONDOWN);
				break;
			
			case CONSTRUCT_SPIRALSTAIR:
				ConstructSpiralstair(nFlags,point,WM_LBUTTONDOWN);
				break;
		    case CONSTRUCT_FIXTUREWALL:
				ConstructFixtureWall(nFlags,point,WM_LBUTTONDOWN);
				//pDoc->m_CurrentFloor->AddElement(
				break; 
			
			}
			break;
	}

	//CScrollView::OnLButtonDown(nFlags, point);
	
}

CBuildingElement* CArchView::SelecteElement(CPoint point)
{
	CClientDC dc(this);
	OnPrepareDC(&dc);
//	dc.DPtoLP(&point,1);

	CArchDoc* pDoc = GetDocument();
	CBuildingElement* pBE = 0;
	CFloor* floor = 0;
	floor = pDoc->m_CurrentFloor;
	for (int i=0; i<floor->GetElementCount();i++)
	{
		pBE = floor->GetElement(i);
		if (pBE->HitTest(point))
			return pBE;
	}
	return ((CBuildingElement*) 0);
}


BOOL CArchView::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	// TODO: Add your message handler code here and/or call default
	
	if (nHitTest!=HTCLIENT)
		return CScrollView::OnSetCursor(pWnd, nHitTest, message);
	/*else
		::SetCursor(m_CCursor);*/
	return TRUE;
}

void CArchView::ConstructWall(UINT nFlags, CPoint point, UINT messagefrom)
{
	if (messagefrom == WM_LBUTTONDOWN)
	{
		if (m_ptCounter == 0)
		{
			if (m_ptList.GetSize()>0) m_ptList.RemoveAll();
			m_ptList.Add(point);
			
		
			m_ptCounter++;
			SetCapture();
			char a[10],b[10];
			itoa(point.x,a,10);
			itoa(point.y,b,10);
			//AfxMessageBox(b);
	         
			return;
		}
		else //if (m_ptCounter==1 && GetCapture()==this)
		{
			m_ptList.Add(point);
			m_ptCounter=0;
			ReleaseCapture();
			CArchDoc* pDoc=GetDocument();
			ASSERT_VALID(pDoc);
			//pDoc->s_count2=pDoc->s_count2+1;
		//	pDoc->loc3=pDoc->loc3+1;
			CWall w(m_ptList[0],m_ptList[1]);
			pDoc->loc3=pDoc->loc3+1;
			pDoc->m_CurrentFloor->AddElement(w);
			pDoc->SetModifiedFlag();
			CClientDC dc(this);
			OnPrepareDC (&dc);
			w.Draw(&dc);
			
		}
		/*CString s;
		CPoint t = m_ptList.GetAt(0);
		s.Format("Value of first elements is %d , %d",t.x,t.y);
		MessageBox(s,"list check");*/

	}
	else
		if (messagefrom == WM_MOUSEMOVE)
		{
			
			if(m_ptCounter > 0 && GetCapture()==this)
			{
				
				CClientDC dc(this);
				OnPrepareDC(&dc);
				if(m_ptCounter==1)
				{
					m_ptList.Add(point);
					m_ptCounter++;
				}
				else if(m_ptCounter==2)
				{
					dc.SetROP2(R2_NOT);
					dc.MoveTo(m_ptList[0].x,m_ptList[0].y);
					dc.LineTo(m_ptList[1].x,m_ptList[1].y);
				}
				dc.SetROP2(R2_NOT);
				dc.MoveTo(m_ptList[0].x,m_ptList[0].y);
				m_ptList[1]=point;
				dc.LineTo(m_ptList[1].x,m_ptList[1].y);
				
			}
		}

}

void CArchView::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	//if (GetDocument()->m_AppMode == MODE_CONSTRUCTION)
	//		ConstructWall(nFlags,point,WM_MOUSEMOVE);
    CArchDoc* pDoc=GetDocument();
	ASSERT_VALID(pDoc);
//	CScrollView::OnMouseMove(nFlags, point);
	switch (pDoc->m_AppMode)
	{
	case MODE_ZOOM:
	case MODE_ADJUSTMENT:
			//MessageBox("Underconstruction..!","ARCH3d",MB_OK);
			break;
	case MODE_CONSTRUCTION:
		::SetCursor(LoadCursor(NULL,MAKEINTRESOURCE(IDC_CROSS)));
			switch(pDoc->m_AppTool)
			{
			case CONSTRUCT_WALL:
				ConstructWall(nFlags,point,WM_MOUSEMOVE);
				break;
			case CONSTRUCT_CWALL:
				ConstructCWall(nFlags,point,WM_MOUSEMOVE);
				break;
			case CONSTRUCT_PILLAR:
				break;
			case CONSTRUCT_STAIRS:
				ConstructStairs(nFlags,point,WM_MOUSEMOVE);
				break;
			case CONSTRUCT_CEILPLANE:
				ConstructCPlane(nFlags,point,WM_MOUSEMOVE);
				break;
			case CONSTRUCT_FIXTUREWALL:
				ConstructFixtureWall(nFlags,point,WM_MOUSEMOVE);
				//pDoc->m_CurrentFloor->AddElement(
				break;
			}
	}
}

void CArchView::ConstructCWall(UINT nFlags, CPoint point, UINT messagefrom)
{
	if (messagefrom == WM_LBUTTONDOWN)
	{
		if (m_ptCounter < 4)
		{
			if (m_ptCounter==0 && m_ptList.GetSize()>0) m_ptList.RemoveAll();
			m_ptList.Add(point);
			m_ptCounter++;
			SetCapture();
		}	
		// (m_ptCounter<4) // && GetCapture()==this)
		//m_ptList.Add(point);
		//m_ptCounter++;
		
		else
			if (m_ptCounter==4)
				{
					ReleaseCapture();
					CArchDoc* pDoc=GetDocument();
					ASSERT_VALID(pDoc);
					
					CPoint temp[4]={m_ptList[0],m_ptList[1],m_ptList[2],m_ptList[3]};
					CCurvedWall cw(temp,4);
					pDoc->s_count2=pDoc->s_count2+1;
					pDoc->loc4=pDoc->loc4+1;
					pDoc->m_CurrentFloor->AddElement(cw);
					pDoc->SetModifiedFlag();
					CClientDC dc(this);
					OnPrepareDC (&dc);
					cw.Draw(&dc);
					m_ptCounter=0;
					m_ptList.RemoveAll();
					
					return;
				}
	}
	else
		if (messagefrom == WM_MOUSEMOVE && GetCapture()==this)
		{
			if (m_ptCounter > 1)
			{
				
				CClientDC dc(this);
				OnPrepareDC(&dc);
				CPoint pt[4];
				if(m_ptCounter<=4)
				{
					dc.SetROP2(R2_NOT);
					for (int i=0; i<m_ptList.GetSize();i++)
						pt[i] = m_ptList.GetAt(i);
					dc.Polyline(pt,m_ptList.GetSize());
				}
				dc.SetROP2(R2_NOT);
				//dc.MoveTo(m_ptList.GetAt(0));
				for (int i=0; i<m_ptList.GetSize();i++)
					pt[i] = m_ptList.GetAt(i);

				dc.Polyline(pt,m_ptList.GetSize());
			}
		}
}

void CArchView::ConstructPillar(UINT nFlags, CPoint point, UINT messagefrom)
{
	if (messagefrom == WM_LBUTTONDOWN)
	{
		/*CClientDC dc(this);
		CRect rect(point, point);
		rect.InflateRect(5,5);
		dc.Rectangle(&rect);*/
		CArchDoc* pDoc=GetDocument();
		ASSERT_VALID(pDoc);
//pDoc->s_count2=pDoc->s_count2+1;
//pDoc->loc3=pDoc->loc3+1;
		CPillar p(point);
		pDoc->loc3=pDoc->loc3+1;
		pDoc->m_CurrentFloor->AddElement(p);
		pDoc->SetModifiedFlag();
		CClientDC dc(this);
		OnPrepareDC (&dc);
		p.Draw(&dc);
	}
}

void CArchView::ConstructStairs(UINT nFlags, CPoint point, UINT messagefrom)
{
	CClientDC dc(this);
	OnPrepareDC (&dc);
	if (messagefrom == WM_LBUTTONDOWN)
	{
		if (m_ptCounter == 0)
		{
			if (m_ptList.GetSize()>0) m_ptList.RemoveAll();
			m_ptList.Add(point);
			m_ptCounter++;
			SetCapture();
			return;
		}
		else //if (m_ptCounter==1 && GetCapture()==this)
		{
			m_ptList.Add(point);
			m_ptCounter=0;
			ReleaseCapture();
			CArchDoc* pDoc=GetDocument();
			ASSERT_VALID(pDoc);
		//	pDoc->s_count2=pDoc->s_count2+1;
		//	pDoc->loc3=pDoc->loc3+1;
			CStairs  cs(m_ptList[0],m_ptList[1]);
			pDoc->loc1=pDoc->loc1+1;
			cs.Draw(&dc);
			pDoc->m_CurrentFloor->AddElement(cs);
			pDoc->SetModifiedFlag();
			m_ptList.RemoveAll();
			
		}
		/*CString s;
		CPoint t = m_ptList.GetAt(0);
		s.Format("Value of first elements is %d , %d",t.x,t.y);
		MessageBox(s,"list check");*/

	}
	else
		if (messagefrom == WM_MOUSEMOVE)
		{
			
			if(m_ptCounter > 0 && GetCapture()==this)
			{
				
				CClientDC dc(this);
				OnPrepareDC(&dc);
				if(m_ptCounter==1)
				{
					m_ptList.Add(point);
					m_ptCounter++;
				}
				else if(m_ptCounter==2)
				{
					dc.SetROP2(R2_NOT);
					dc.MoveTo(m_ptList[0].x,m_ptList[0].y);
					dc.LineTo(m_ptList[1].x,m_ptList[1].y);
				}
				dc.SetROP2(R2_NOT);
				dc.MoveTo(m_ptList[0].x,m_ptList[0].y);
				m_ptList[1]=point;
				dc.LineTo(m_ptList[1].x,m_ptList[1].y);
				
			}
		}

}

void CArchView::ConstructCPlane(UINT nFlags, CPoint point, UINT messagefrom)
{
	if (messagefrom == WM_LBUTTONDOWN)
	{
		if (m_ptCounter==0 && m_ptList.GetSize()>0) m_ptList.RemoveAll();
			m_ptList.Add(point);
			m_ptCounter++;
			SetCapture();
	}
		
	else	
		if (messagefrom == WM_LBUTTONDBLCLK && m_ptCounter>5)
		{
			ReleaseCapture();
			CArchDoc* pDoc=GetDocument();
			ASSERT_VALID(pDoc);
			
pDoc->s_count2=pDoc->s_count2+1;
			CPoint *temp = new CPoint[m_ptList.GetSize()];
			for (int i=0; i<m_ptList.GetSize();i++)
				temp[i] = m_ptList.GetAt(i);
			pDoc->m_CurrentFloor->AddCeilling(temp,m_ptCounter);
			delete[] temp;
			CClientDC dc(this);
			OnPrepareDC (&dc);
			//pDoc->m_CurrentFloor->
			m_ptCounter=0;
			m_ptList.RemoveAll();
			return;
		}
	else
		if (messagefrom == WM_MOUSEMOVE && GetCapture()==this)
		{
			if (m_ptCounter > 1)
			{
				
				CClientDC dc(this);
				OnPrepareDC(&dc);
				CPoint *pt= new CPoint[m_ptCounter];
				//dc.SetROP2(R2_NOT);
				for (int i=0; i<m_ptList.GetSize();i++)
						pt[i] = m_ptList.GetAt(i);
				dc.Polyline(pt,m_ptList.GetSize());
				
				//dc.SetROP2(R2_NOT);
				//dc.MoveTo(m_ptList.GetAt(0));
				//for (int i=0; i<m_ptList.GetSize();i++)
				//	pt[i] = m_ptList.GetAt(i);
				//dc.Polyline(pt,m_ptList.GetSize());

			}
		}
}

BOOL CArchView::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	CScrollView::OnEraseBkgnd(pDC);
	CRect r;
	GetClientRect(&r);
	CBrush *pBrush, brush;
	brush.CreateSolidBrush(RGB(255,255,225));
	CPen *pPen, pen;
	pen.CreatePen(PS_DOT,0,RGB(200,200,200));
	pBrush=pDC->SelectObject(&brush);
	pPen = pDC->SelectObject(&pen);
	int i;
	pDC->FillRect(&r,&brush);
	for (i=r.left;i<r.right;i+=12)
	{
		pDC->MoveTo(i,r.top);
		pDC->LineTo(i,r.bottom);
	}
	for (i=r.top;i<r.bottom;i+=12)
	{
		pDC->MoveTo(r.left,i);
		pDC->LineTo(r.right,i);
	}
	pDC->SelectObject(pPen);
	pDC->SelectObject(pBrush);
	return TRUE;
}

void CArchView::OnViewFloor() 
{
	CArchDoc* pDoc=GetDocument();
	m_dlgViewFloor.m_nTotalFloor=pDoc->m_Building.GetFloorCount()-1;

	if (m_dlgViewFloor.DoModal()==IDOK)
	{
		pDoc->m_CurrentFloor = pDoc->m_Building.GetFloorAt(m_dlgViewFloor.m_nFloor);
		pDoc->m_BESelected = 0;
		pDoc->UpdateAllViews(0); 
	}
}

void CArchView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo) 
{
	// TODO: Add your specialized code here and/or call the base class
	CScrollView::OnPrepareDC(pDC, pInfo);

}

/*
void CArchView::OnView3dview() 
{
	// TODO: Add your command handler code here
	//ArchDraw3d();
	//int argc=1;
	//char *argv[1];
	//glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(30,30);
	glutCreateWindow("Arch3D View");

}
*/

void CArchView::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	// TODO : Add your message handler code here and/or call default
	CArchDoc* pDoc=GetDocument();
	ASSERT_VALID(pDoc);
	if (pDoc->m_AppMode == MODE_CONSTRUCTION)
	{
		if (pDoc->m_AppTool == CONSTRUCT_CEILPLANE)
		{
			ConstructCPlane(nFlags,point,WM_LBUTTONDBLCLK);
			pDoc->m_AppMode = MODE_ADJUSTMENT;
			pDoc->m_AppTool = ADJUSTMENT_SELECT;
		}

	}
	else if(pDoc->m_AppMode==MODE_ADJUSTMENT)
	{
		if (pDoc->m_AppTool == ADJUSTMENT_SELECT)
		{
			if(pDoc->m_BESelected == NULL)
				AfxMessageBox("No Building Element is Selected");
			else 
			{
				
			
			UINT type=pDoc->m_BESelected->GetType();
			switch (type)
			{
			case	BUILDING_ELEMENT_WALL:  ShowSimpleWallDialog();break;
			case	BUILDING_ELEMENT_FIXTUREWALL: ShowDialogStWall(); break;
			
			case	BUILDING_ELEMENT_STAIRS: ShowDialogStairs(); break;
			case	BUILDING_ELEMENT_SPIRALSTAIR: ShowSpiralDlg(); break;
			
			case	BUILDING_ELEMENT_CURVEDWALL: ShowDialogCuWall(); break;
			case	BUILDING_ELEMENT_ROUNDPILLAR: 
			case    BUILDING_ELEMENT_SQUAREPILLAR:
						ShowDialogPillar(); break;
			case    BUILDING_ELEMENT_CEILING:ShowCeilingDlg();break;
			case    BUILDING_ELEMENT_CHAIR1:
			case    BUILDING_ELEMENT_CHAIR2:
			case    BUILDING_ELEMENT_CHAIR3:
			case    BUILDING_ELEMENT_CHAIR4:
			case    BUILDING_ELEMENT_CHAIR5:
				        ShowDialogChair();break; 
			case    BUILDING_ELEMENT_TABLE1:
			case    BUILDING_ELEMENT_TABLE2:
			case    BUILDING_ELEMENT_TABLE3:
			case    BUILDING_ELEMENT_TABLE4:
			case    BUILDING_ELEMENT_TABLE5:
				        ShowDialogTable();break; 
			case    BUILDING_ELEMENT_SOFA1:
			case    BUILDING_ELEMENT_SOFA2:
			case    BUILDING_ELEMENT_SOFA3:
			case    BUILDING_ELEMENT_SOFA4:
			case    BUILDING_ELEMENT_SOFA5:
				        ShowDialogSofa();break; 
			default  : AfxMessageBox("Error"); break;
			}				
			
			}

		 
		}
	}
	CScrollView::OnLButtonDblClk(nFlags, point);
}

void CArchView::ShowDialogStWall()
{
  
   CArchDoc* pDoc=GetDocument();
   CFixtureWall* pswall=static_cast<CFixtureWall*> (pDoc->m_BESelected);
   
   
   m_stwalldlg.m_width = pswall->m_uiWidth;
   int dx=pswall->m_ptFirstPosition.x-pswall->m_ptSecondPosition.x;
   int dy=pswall->m_ptFirstPosition.y-pswall->m_ptSecondPosition.y;
   int length=sqrt((dx*dx)+(dy*dy));
   m_stwalldlg.m_walllength=length;
   //cal=(pswall->m_ptSecondPosition.x-pswall->m_ptFirstPosition.x)/58;
   cal=length/58; 
   diff1=cal-3;
   pswall->m_basep=m_stwalldlg.m_basepoint;
   pswall->m_uiHeight=m_stwalldlg.m_wtoppoint;
   if (pswall->m_IsTexturizedSideA==TRUE)
   {
	   m_stwalldlg.m_istextureA=TRUE;
	   m_stwalldlg.m_sFilenameA=pswall->m_SideATexture;
	   //Do something to load texture
	   
   }
   else
   {
	   m_stwalldlg.m_istextureA=FALSE;
	   m_stwalldlg.m_colorA=pswall->m_SideAColor;
   }

   if (pswall->m_IsTexturizedSideB==TRUE)
   {
	   m_stwalldlg.m_istextureB=TRUE;
	   //Do something to load texture
	   m_stwalldlg.m_sFilenameB=pswall->m_SideBTexture;
 
   }
   else
   {
	   m_stwalldlg.m_istextureB=FALSE;
	   m_stwalldlg.m_colorB=pswall->m_SideBColor;
   }
//   if(m_stwalldlg.m_flag==1)
  // {
   if(pswall->m_isdoor==TRUE)
   {
	   m_stwalldlg.m_isdoor=TRUE;
	   m_stwalldlg.m_doortype=pswall->m_door.m_uiType;
	   m_stwalldlg.m_doorcolor=pswall->m_door.m_Color;
	   m_stwalldlg.m_doorframe=pswall->m_door.m_rectframe;
	   m_stwalldlg.m_connectedpointdoor=pswall->m_door.m_ConnectedPoint;
          
   }
   
   else
	   m_stwalldlg.m_isdoor=FALSE;
//   }
  // if(m_stwalldlg.m_flag1==1)
  // {
   if(pswall->m_iswindow==TRUE)
	{
	   m_stwalldlg.m_iswindow=TRUE;
	   m_stwalldlg.m_windowtype=pswall->m_window.m_uiType;
	   m_stwalldlg.m_windowframe=pswall->m_window.m_rectframe;
	   m_stwalldlg.m_windowcolor=pswall->m_window.m_Color;
	   m_stwalldlg.m_connectedpointwindow=pswall->m_window.m_ConnectedPoint;
   }
   
   else
  	   m_stwalldlg.m_iswindow=FALSE;
//   }
 //  if(m_stwalldlg.m_flag==1 && m_stwalldlg.m_flag1==1)
//{ 
if(pswall->m_isdoor==TRUE && pswall->m_iswindow==TRUE)
{
 	   m_stwalldlg.m_isdoor=TRUE;
	   m_stwalldlg.m_doortype=pswall->m_door.m_uiType;
	   m_stwalldlg.m_doorcolor=pswall->m_door.m_Color;
	   m_stwalldlg.m_doorframe=pswall->m_door.m_rectframe;
	   m_stwalldlg.m_connectedpointdoor=pswall->m_door.m_ConnectedPoint;
    
   
   	   m_stwalldlg.m_iswindow=TRUE;
	   m_stwalldlg.m_windowtype=pswall->m_window.m_uiType;
	   m_stwalldlg.m_windowframe=pswall->m_window.m_rectframe;
	   m_stwalldlg.m_windowcolor=pswall->m_window.m_Color;
	   m_stwalldlg.m_connectedpointwindow=pswall->m_window.m_ConnectedPoint;
  }  
//}   
if (m_stwalldlg.DoModal()==IDOK)
   {
		pswall->m_uiWidth=m_stwalldlg.m_width;
        pswall->m_basep=m_stwalldlg.m_basepoint;
		pswall->m_uiHeight=m_stwalldlg.m_wtoppoint;
		if (m_stwalldlg.m_istextureA==FALSE)
		{
			pswall->m_SideAColor=m_stwalldlg.m_colorA;
			pswall->m_IsTexturizedSideA=FALSE;
		}
		else 
		{
			pswall->m_IsTexturizedSideA=TRUE;
			//pswall->m_SideATexture.DeleteObject();
			//pswall->m_SideATexture.LoadImage(m_stwalldlg.m_sFilenameA);
			pswall->m_SideATexture=m_stwalldlg.m_sFilenameA;
		}
		if (m_stwalldlg.m_istextureB==FALSE)
		{
			pswall->m_IsTexturizedSideB=FALSE;
			pswall->m_SideBColor=m_stwalldlg.m_colorB;
		}
		else 
		{
		//	pswall->m_SideBTexture.DeleteObject();
			//pswall->m_SideBTexture.LoadImage(m_cuwalldlg.m_sFilenameB);
			pswall->m_IsTexturizedSideB=TRUE;
			pswall->m_SideBTexture=m_stwalldlg.m_sFilenameB;
		}
		if (m_stwalldlg.m_isdoor)
			{
			pswall->m_isdoor=TRUE;
			pswall->m_door.m_Color=m_stwalldlg.m_doorcolor;
			pswall->m_door.m_uiType=m_stwalldlg.m_doortype;
			pswall->m_door.m_rectframe=m_stwalldlg.m_doorframe;
			pswall->m_door.m_ConnectedPoint=m_stwalldlg.m_connectedpointdoor;
		    pswall->m_door.m_ConnectedPoint.x=pswall->m_door.m_ConnectedPoint.x+(diff1*m_stwalldlg.countclk);
			pswall->m_door.m_ConnectedPoint.y=pswall->m_door.m_ConnectedPoint.y+(diff1*m_stwalldlg.countclk);
			pswall->m_door.m_bottompoint=m_stwalldlg.m_bottomRight;    	
	        pswall->m_door.m_bottompoint.x=pswall->m_door.m_bottompoint.x+(diff1*m_stwalldlg.countclk);
		    pswall->m_door.m_bottompoint.y=pswall->m_door.m_bottompoint.y+(diff1*m_stwalldlg.countclk);
		    pDoc->loc2=pDoc->loc2+1;
			
			//pswall->loc1=pswall->loc1+1; 
		}
		else
		
			pswall->m_isdoor=FALSE;
	
		if (m_stwalldlg.m_iswindow)
			{
			pswall->m_iswindow=TRUE;
			pswall->m_window.m_rectframe=m_stwalldlg.m_windowframe;
			pswall->m_window.m_uiType=m_stwalldlg.m_windowtype;
			pswall->m_window.m_Color=m_stwalldlg.m_windowcolor;
			pswall->m_window.m_ConnectedPoint=m_stwalldlg.m_connectedpointwindow;
	        pswall->m_window.m_ConnectedPoint.x=pswall->m_window.m_ConnectedPoint.x+(diff1*m_stwalldlg.countclk1);    
			pswall->m_window.m_ConnectedPoint.y=pswall->m_window.m_ConnectedPoint.y+(diff1*m_stwalldlg.countclk1);
			pswall->m_window.m_bottompoint=m_stwalldlg.m_bottompointwindow;    	
	        pswall->m_window.m_bottompoint.x=pswall->m_window.m_bottompoint.x+(diff1*m_stwalldlg.countclk1);
		    pswall->m_window.m_bottompoint.y=pswall->m_window.m_bottompoint.y+(diff1*m_stwalldlg.countclk1);
		
		
		}
		else
			pswall->m_iswindow=FALSE;
		if (m_stwalldlg.m_isdoor && m_stwalldlg.m_iswindow)
			{
			pswall->m_isdoor=TRUE;
			pswall->m_door.m_Color=m_stwalldlg.m_doorcolor;
			pswall->m_door.m_uiType=m_stwalldlg.m_doortype;
			pswall->m_door.m_rectframe=m_stwalldlg.m_doorframe;
			pswall->m_door.m_ConnectedPoint=m_stwalldlg.m_connectedpointdoor;
		    pswall->m_door.m_ConnectedPoint.x=pswall->m_door.m_ConnectedPoint.x+(diff1*m_stwalldlg.countclk);
			pswall->m_door.m_ConnectedPoint.y=pswall->m_door.m_ConnectedPoint.y+(diff1*m_stwalldlg.countclk);
			pswall->m_door.m_bottompoint=m_stwalldlg.m_bottomRight;    	
	        pswall->m_door.m_bottompoint.x=pswall->m_door.m_bottompoint.x+(diff1*m_stwalldlg.countclk);
		    pswall->m_door.m_bottompoint.y=pswall->m_door.m_bottompoint.y+(diff1*m_stwalldlg.countclk);
		
			pswall->m_iswindow=TRUE;
			pswall->m_window.m_rectframe=m_stwalldlg.m_windowframe;
			pswall->m_window.m_uiType=m_stwalldlg.m_windowtype;
			pswall->m_window.m_Color=m_stwalldlg.m_windowcolor;
			pswall->m_window.m_ConnectedPoint=m_stwalldlg.m_connectedpointwindow;
	        pswall->m_window.m_ConnectedPoint.x=pswall->m_window.m_ConnectedPoint.x+(diff1*m_stwalldlg.countclk1);    
			pswall->m_window.m_ConnectedPoint.y=pswall->m_window.m_ConnectedPoint.y+(diff1*m_stwalldlg.countclk1);
			pswall->m_window.m_bottompoint=m_stwalldlg.m_bottompointwindow;    	
	        pswall->m_window.m_bottompoint.x=pswall->m_window.m_bottompoint.x+(diff1*m_stwalldlg.countclk1);
		    pswall->m_window.m_bottompoint.y=pswall->m_window.m_bottompoint.y+(diff1*m_stwalldlg.countclk1);
		
		
		}
	   	 pDoc->UpdateAllViews(0); 
   }
   CClientDC dc(this);
   OnPrepareDC(&dc);
   pswall->Draw(&dc,TRUE);

}

void CArchView::ShowDialogPillar()
{

   CArchDoc* pDoc=GetDocument();
   CPillar* ppillar=static_cast<CPillar*> (pDoc->m_BESelected);
   m_pillardlg.m_width = ppillar->m_uiWidth;
   m_pillardlg.m_type= ppillar->m_uiType;
   m_pillardlg.m_col=ppillar->m_Color;
   
   if (m_pillardlg.DoModal()==IDOK)
   {
		if (m_pillardlg.m_width==0)
				ppillar->m_uiWidth=12;
		else if (m_pillardlg.m_width==1)
				ppillar->m_uiWidth=18;
		else if (m_pillardlg.m_width==2)
				ppillar->m_uiWidth=24;
		ppillar->m_uiType=m_pillardlg.m_type;
		ppillar->m_Color=m_pillardlg.m_col;
    pDoc->UpdateAllViews(0); 
   }
   CClientDC dc(this);
   OnPrepareDC(&dc);
   ppillar->Draw(&dc,TRUE);
  
}

void CArchView::ShowDialogStairs()
{
   CArchDoc* pDoc=GetDocument();
   CStairs* pstair=static_cast<CStairs*> (pDoc->m_BESelected);

   m_stairdlg.m_width = pstair->m_uiWidth;
   m_stairdlg.m_color=pstair->m_StairColor;
   
   if (m_stairdlg.DoModal()==IDOK)
   {
		pstair->m_uiWidth=m_stairdlg.m_width;
		pstair->m_StairColor=m_stairdlg.m_color;
    pDoc->UpdateAllViews(0); 
   }
   CClientDC dc(this);
   OnPrepareDC(&dc);
   pstair->Draw(&dc,TRUE);
}

void CArchView::ShowDialogCuWall()
{

   CArchDoc* pDoc=GetDocument();
   CCurvedWall* pcwall=static_cast<CCurvedWall*> (pDoc->m_BESelected);
  
   m_cuwalldlg.m_width   = pcwall->m_uiWidth;

   
   

   if (pcwall->m_IsTexturizedSideA)
   {
	   m_cuwalldlg.m_istextureA=TRUE;
	   
	   //Do something to load texture
		m_cuwalldlg.m_sFilenameA=pcwall->m_SideATexture;

   }
   else 
   {
	   m_cuwalldlg.m_colorA  = pcwall->m_SideAColor;
	   m_cuwalldlg.m_istextureA=FALSE;
   }

   if (pcwall->m_IsTexturizedSideB)
   {
	   m_cuwalldlg.m_istextureB=TRUE;
	   //Do something to load texture
	   m_cuwalldlg.m_sFilenameB=pcwall->m_SideBTexture;
   }
   else
   {
	   m_cuwalldlg.m_istextureB=FALSE;
	   m_cuwalldlg.m_colorB  = pcwall->m_SideBColor;
   }

   if (m_cuwalldlg.DoModal()==IDOK)
   {
		pcwall->m_uiWidth=m_cuwalldlg.m_width;

		if (m_cuwalldlg.m_istextureA==FALSE)
		{
			pcwall->m_SideAColor=m_cuwalldlg.m_colorA;
			pcwall->m_IsTexturizedSideA=FALSE;

		}
		else if (m_cuwalldlg.m_istextureA==TRUE)
		{
			//pcwall->m_SideATexture.DeleteObject();
			//pcwall->m_SideATexture.LoadImage(m_cuwalldlg.m_sFilenameA);
			pcwall->m_IsTexturizedSideA=TRUE;
			pcwall->m_SideATexture=m_cuwalldlg.m_sFilenameA;
	
		}
		if (m_cuwalldlg.m_istextureB==FALSE)
		{
			pcwall->m_SideBColor=m_cuwalldlg.m_colorB;
			pcwall->m_IsTexturizedSideB=FALSE;
		}
		else if (m_cuwalldlg.m_istextureB==TRUE)
		{
			//pcwall->m_SideBTexture.DeleteObject();
			//pcwall->m_SideBTexture.LoadImage(m_cuwalldlg.m_sFilenameB);
			pcwall->m_IsTexturizedSideB=TRUE;
			pcwall->m_SideBTexture=m_cuwalldlg.m_sFilenameB;
		}
	
   }

   CClientDC dc(this);
   OnPrepareDC(&dc);
   pcwall->Draw(&dc,TRUE);
}













void CArchView::ConstructCCeiling(UINT nFlags, CPoint point, UINT messagefrom)
{
	if (messagefrom == WM_LBUTTONDOWN)
	{
		if (m_ptCounter == 0)
		{
			if (m_ptList.GetSize()>0) m_ptList.RemoveAll();
			m_ptList.Add(point);
			
		
			m_ptCounter++;
			SetCapture();
			char a[10],b[10];
			itoa(point.x,a,10);
			itoa(point.y,b,10);
			//AfxMessageBox(b);
	         
			return;
		}
		else //if (m_ptCounter==1 && GetCapture()==this)
		{
			m_ptList.Add(point);
			m_ptCounter=0;
			ReleaseCapture();
			CArchDoc* pDoc=GetDocument();
			ASSERT_VALID(pDoc);
		//	pDoc->s_count2=pDoc->s_count2+1;
        //    pDoc->loc3=pDoc->loc3+1;
			CCeiling ceil(m_ptList[0],m_ptList[1]);
			pDoc->loc3=pDoc->loc3+1;
			pDoc->m_CurrentFloor->AddElement(ceil);
			pDoc->SetModifiedFlag();
			CClientDC dc(this);
			OnPrepareDC (&dc);
			ceil.Draw(&dc);
			
		}
		/*CString s;
		CPoint t = m_ptList.GetAt(0);
		s.Format("Value of first elements is %d , %d",t.x,t.y);
		MessageBox(s,"list check");*/

	}
	else
		if (messagefrom == WM_MOUSEMOVE)
		{
			
			if(m_ptCounter > 0 && GetCapture()==this)
			{
				
				CClientDC dc(this);
				OnPrepareDC(&dc);
				if(m_ptCounter==1)
				{
					m_ptList.Add(point);
					m_ptCounter++;
				}
				else if(m_ptCounter==2)
				{
					dc.SetROP2(R2_NOT);
					dc.Rectangle(m_ptList[0].x,m_ptList[0].y,m_ptList[1].x,m_ptList[1].y);
					//dc.LineTo();
				}
				dc.SetROP2(R2_NOT);
				dc.Rectangle(m_ptList[0].x,m_ptList[0].y,m_ptList[1].x,m_ptList[1].y);
				m_ptList[1]=point;
				//dc.LineTo(m_ptList[1].x,m_ptList[1].y);
				
			}
		}
}



void CArchView::ConstructChairObj(UINT nFlags, CPoint point, UINT messagefrom)
{
if (messagefrom == WM_LBUTTONDOWN)
	{
		/*CClientDC dc(this);
		CRect rect(point, point);
		rect.InflateRect(5,5);
		dc.Rectangle(&rect);*/
		CArchDoc* pDoc=GetDocument();
		ASSERT_VALID(pDoc);
	//	pDoc->s_count2=pDoc->s_count2+1;
	//	pDoc->loc3=pDoc->loc3+1;
		CChairObject co(point);
		pDoc->m_CurrentFloor->AddElement(co);
		pDoc->SetModifiedFlag();
		CClientDC dc(this);
		OnPrepareDC (&dc);
	
		co.Draw(&dc);
	}
}

void CArchView::ShowDialogChair()
{
 CArchDoc* pDoc=GetDocument();
   CChairObject* cchair=static_cast<CChairObject*> (pDoc->m_BESelected);
   //m_chairdlg.m_width = cchair->m_uiWidth;
   m_chairdlg.m_ctype= cchair->m_uiType;
   m_chairdlg.m_col=cchair->m_Color;
   
   if (m_chairdlg.DoModal()==IDOK)
   {
		cchair->m_uiType=m_chairdlg.m_ctype;
		cchair->m_Color=m_chairdlg.m_col;
   pDoc->UpdateAllViews(0); 
   }
   CClientDC dc(this);
   OnPrepareDC(&dc);
   cchair->Draw(&dc,TRUE);
}

void CArchView::ShowCeilingDlg()
{
	CArchDoc* pDoc=GetDocument();
    CCeiling* pceil=static_cast<CCeiling*> (pDoc->m_BESelected);
	m_ceildlg.m_ctoppoint=pceil->m_uiHeight;
      m_ceildlg.m_color=pceil->m_SideAColor;
	if(m_ceildlg.DoModal()==IDOK)
	{
		pceil->m_uiHeight=m_ceildlg.m_ctoppoint;
	    pceil->m_SideAColor=m_ceildlg.m_color;
	
	}
}

void CArchView::ConstructSpiralstair(UINT nFlags, CPoint point, UINT messagefrom)
{
if (messagefrom == WM_LBUTTONDOWN)
	{
		/*CClientDC dc(this);
		CRect rect(point, point);
		rect.InflateRect(5,5);
		dc.Rectangle(&rect);*/
		CArchDoc* pDoc=GetDocument();
		ASSERT_VALID(pDoc);
		//pDoc->s_count2=pDoc->s_count2+1;
		pDoc->loc3=pDoc->loc3+1;
		CSpiralstair sp(point);
		pDoc->m_CurrentFloor->AddElement(sp);
		pDoc->SetModifiedFlag();
		CClientDC dc(this);
		OnPrepareDC (&dc);
		sp.Draw(&dc);
	}
}

void CArchView::ConstructFixtureWall(UINT nFlags, CPoint point, UINT messagefrom)
{
	if (messagefrom == WM_LBUTTONDOWN)
	{
		if (m_ptCounter == 0)
		{
			if (m_ptList.GetSize()>0) m_ptList.RemoveAll();
			m_ptList.Add(point);
			
		
			m_ptCounter++;
			SetCapture();
			char a[10],b[10];
			itoa(point.x,a,10);
			itoa(point.y,b,10);
			//AfxMessageBox(b);
	         
			return;
		}
		else //if (m_ptCounter==1 && GetCapture()==this)
		{
			m_ptList.Add(point);
			m_ptCounter=0;
			ReleaseCapture();
			CArchDoc* pDoc=GetDocument();
			ASSERT_VALID(pDoc);
		//	pDoc->s_count2=pDoc->s_count2+1;
		//	pDoc->loc2=pDoc->loc2+1;
			CFixtureWall fw(m_ptList[0],m_ptList[1]);
			//pDoc->loc2=pDoc->loc2+1;
			pDoc->m_CurrentFloor->AddElement(fw);
			pDoc->SetModifiedFlag();
			CClientDC dc(this);
			OnPrepareDC (&dc);
			fw.Draw(&dc);
			
		}
		/*CString s;
		CPoint t = m_ptList.GetAt(0);
		s.Format("Value of first elements is %d , %d",t.x,t.y);
		MessageBox(s,"list check");*/

	}
	else
		if (messagefrom == WM_MOUSEMOVE)
		{
			
			if(m_ptCounter > 0 && GetCapture()==this)
			{
				
				CClientDC dc(this);
				OnPrepareDC(&dc);
				if(m_ptCounter==1)
				{
					m_ptList.Add(point);
					m_ptCounter++;
				}
				else if(m_ptCounter==2)
				{
					dc.SetROP2(R2_NOT);
					dc.MoveTo(m_ptList[0].x,m_ptList[0].y);
					dc.LineTo(m_ptList[1].x,m_ptList[1].y);
				}
				dc.SetROP2(R2_NOT);
				dc.MoveTo(m_ptList[0].x,m_ptList[0].y);
				m_ptList[1]=point;
				dc.LineTo(m_ptList[1].x,m_ptList[1].y);
				
			}
		}
}

void CArchView::ShowSimpleWallDialog()
{
   CArchDoc* pDoc=GetDocument();
   CWall* pwall=static_cast<CWall*> (pDoc->m_BESelected);
   m_swalldlg.m_width = pwall->m_uiWidth;
  
   int dx=pwall->m_ptFirstPosition.x-pwall->m_ptSecondPosition.x;
   int dy=pwall->m_ptFirstPosition.y-pwall->m_ptSecondPosition.y;
   int length=sqrt((dx*dx)+(dy*dy));
   m_swalldlg.m_walllength=length;
   //cal=(pwall->m_ptSecondPosition.x-pwall->m_ptFirstPosition.x)/58;
   cal=length/58; 
   diff1=cal-3;
 //  pwall->m_basep=m_swalldlg.m_base;
  // pwall->m_uiHeight=m_swalldlg.m_top;
   if (pwall->m_IsTexturizedSideA==TRUE)
   {
	   m_swalldlg.m_istextureA=TRUE;
//	   m_swalldlg.m_sFilenameA=pwall->m_SideATexture;
	   //Do something to load texture
	   
   }
   else
   {
	   m_swalldlg.m_istextureA=FALSE;
	   m_swalldlg.m_colorA=pwall->m_SideAColor;
   }

   if (pwall->m_IsTexturizedSideB==TRUE)
   {
	   m_swalldlg.m_istextureB=TRUE;
	   //Do something to load texture
//	   m_swalldlg.m_sFilenameB=pwall->m_SideBTexture;
 
   }
   else
   {
	   m_swalldlg.m_istextureB=FALSE;
	   m_swalldlg.m_colorB=pwall->m_SideBColor;
   }
//   if(m_swalldlg.m_flag==1)
  // {
     
//}   
if (m_swalldlg.DoModal()==IDOK)
   {
		pwall->m_uiWidth=m_swalldlg.m_width;
        pwall->m_basep=m_swalldlg.m_base;
		pwall->m_topp=m_swalldlg.m_top;
		if (m_swalldlg.m_istextureA==FALSE)
		{
			pwall->m_SideAColor=m_swalldlg.m_colorA;
			pwall->m_IsTexturizedSideA=FALSE;
		}
		else 
		{
			pwall->m_IsTexturizedSideA=TRUE;
			//pwall->m_SideATexture.DeleteObject();
			//pwall->m_SideATexture.LoadImage(m_swalldlg.m_sFilenameA);
//			pwall->m_SideATexture=m_swalldlg.m_sFilenameA;
		}
		if (m_swalldlg.m_istextureB==FALSE)
		{
			pwall->m_IsTexturizedSideB=FALSE;
			pwall->m_SideBColor=m_swalldlg.m_colorB;
		}
		else 
		{
		//	pwall->m_SideBTexture.DeleteObject();
			//pwall->m_SideBTexture.LoadImage(m_cuwalldlg.m_sFilenameB);
			pwall->m_IsTexturizedSideB=TRUE;
//			pwall->m_SideBTexture=m_swalldlg.m_sFilenameB;
		}
	   	 pDoc->UpdateAllViews(0); 
   }
   CClientDC dc(this);
   OnPrepareDC(&dc);
   pwall->Draw(&dc,TRUE);
}

void CArchView::ConstructTableObj(UINT nFlags, CPoint point, UINT messagefrom)
{
if (messagefrom == WM_LBUTTONDOWN)
	{
		/*CClientDC dc(this);
		CRect rect(point, point);
		rect.InflateRect(5,5);
		dc.Rectangle(&rect);*/
		CArchDoc* pDoc=GetDocument();
		ASSERT_VALID(pDoc);
	//	pDoc->s_count2=pDoc->s_count2+1;
	//	pDoc->loc3=pDoc->loc3+1;
		CTableobject t(point);
		pDoc->m_CurrentFloor->AddElement(t);
		pDoc->SetModifiedFlag();
		CClientDC dc(this);
		OnPrepareDC (&dc);
		t.Draw(&dc);
	}

}
void CArchView::ShowSpiralDlg()
{
	CArchDoc* pDoc=GetDocument();
	CSpiralstair* psstair=static_cast<CSpiralstair*> (pDoc->m_BESelected);
	if (m_spiraldlg.DoModal()==IDOK)
	{
	//	psstair->m_uiWidth=m_spiraldlg.m_width;
		psstair->m_Color=m_spiraldlg.m_scol;
		pDoc->UpdateAllViews(0); 
	}
}

void CArchView::ShowDialogTable()
{
	CArchDoc* pDoc=GetDocument();
	CTableobject* table=static_cast<CTableobject*> (pDoc->m_BESelected);
   //m_chairdlg.m_width = cchair->m_uiWidth;
   m_tabdlg.m_tabletype= table->m_uiType;
   m_tabdlg.m_col=table->m_Color;
   
   if (m_tabdlg.DoModal()==IDOK)
   {
		table->m_uiType=m_tabdlg.m_tabletype;
		table->m_Color=m_tabdlg.m_col;
   pDoc->UpdateAllViews(0); 
   }
   CClientDC dc(this);
   OnPrepareDC(&dc);
   table->Draw(&dc,TRUE);
}

void CArchView::ShowDialogSofa()
{
	CArchDoc* pDoc=GetDocument();
	CSofaobject* sofa=static_cast<CSofaobject*> (pDoc->m_BESelected);
   //m_chairdlg.m_width = cchair->m_uiWidth;
	m_sofadlg.m_sofatype= sofa->m_uiType;
	m_sofadlg.m_col=sofa->m_Color;
   
   if (m_sofadlg.DoModal()==IDOK)
   {
		sofa->m_uiType=m_sofadlg.m_sofatype;
		sofa->m_Color=m_sofadlg.m_col;
   pDoc->UpdateAllViews(0); 
   }
   CClientDC dc(this);
   OnPrepareDC(&dc);
   sofa->Draw(&dc,TRUE);
}

void CArchView::ConstructSofaObj(UINT nFlags, CPoint point, UINT messagefrom)
{
if (messagefrom == WM_LBUTTONDOWN)
	{
		/*CClientDC dc(this);
		CRect rect(point, point);
		rect.InflateRect(5,5);
		dc.Rectangle(&rect);*/
		CArchDoc* pDoc=GetDocument();
		ASSERT_VALID(pDoc);
	//	pDoc->s_count2=pDoc->s_count2+1;
	//	pDoc->loc3=pDoc->loc3+1;
		CSofaobject sf(point);
		pDoc->m_CurrentFloor->AddElement(sf);
		pDoc->SetModifiedFlag();
		CClientDC dc(this);
		OnPrepareDC (&dc);
		sf.Draw(&dc);
	}
}

void CArchView::OnViewconstructedfloor() 
{
	// TODO: Add your command handler code here
	CArchDoc* pDoc=GetDocument();
	m_dlgViewFloor.m_nTotalFloor=pDoc->m_Building.GetFloorCount()-1;

	if (m_dlgViewFloor.DoModal()==IDOK)
	{
		pDoc->m_CurrentFloor = pDoc->m_Building.GetFloorAt(m_dlgViewFloor.m_nFloor);
		pDoc->m_BESelected = 0;
		pDoc->UpdateAllViews(0); 
	}
}

void CArchView::OnUpdateConstructedViewfloor(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CArchView::OnBuildNewfloor() 
{
	CArchDoc* pDoc=GetDocument();
// TODO: Add your command handler code here
	pDoc->m_BESelected = 0;
//	m_CurrentFloor = 0;
	CPoint pt[]={(0,0),(300,300)};
	
	if (pDoc->m_Building.GetFloorCount()==1)
	{
		pDoc->m_Building.AddFloor(pt,2);
		AfxMessageBox("We Are At Ground Floor");
	}
	else
		 if (pDoc->m_Building.GetFloorCount()==2) 
		 {
			pDoc->m_Building.AddFloor(pt,3);
	 		AfxMessageBox("We  Are At First Floor");
	 	 }
	 else
		 if (pDoc->m_Building.GetFloorCount()==3) 
		 {
			 pDoc->m_Building.AddFloor(pt,4);	
			 AfxMessageBox("We Are At Second Floor");	
		 }
	 else
		 if (pDoc->m_Building.GetFloorCount()==4) 
		 AfxMessageBox("No more floor will create");
		
		/* else
	{
		CFloor* f=m_CurrentFloor;
		int npoints = f->m_CeillingPlane.m_BoundaryPoints.GetSize();
		CPoint* pt1= new CPoint[npoints];
		for (int i=0;i<npoints;i++)
			pt1[i]=f->m_CeillingPlane.m_BoundaryPoints.GetAt(i);
		m_Building.AddFloor(pt1,npoints);
		delete[] pt1;
		//m_CurrentFloor->
		//int n=m_Building
	}*/
	int cf=pDoc->m_Building.GetFloorCount();
	pDoc->m_CurrentFloor=pDoc->m_Building.GetFloorAt(cf-1);
	pDoc->UpdateAllViews(0);
}

void CArchView::OnUpdateNewfloor(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "Arch.h"
#include "MainFrm.h"
#include "GL3dView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_UPDATE_COMMAND_UI(ID_VIEW_2DVIEW, OnUpdateView2dview)
	ON_UPDATE_COMMAND_UI(ID_VIEW_3DVIEW, OnUpdateView3dview)
	ON_WM_SHOWWINDOW()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	
//	m_p2dView = (CArchView*) GetActiveView();
//	m_p3dView = new GL3dView;
//	m_CurrentView = 2;
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_tbrAppMode.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_tbrAppMode.LoadToolBar(IDR_TBRAPPMODE))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
	if (!m_tbrElement.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_tbrElement.LoadToolBar(IDR_TBRELEMENT))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

// Add the color toolbar
     int iTBCtlID;
     int i;

    // Create the Color Toolbar
     if (!m_wndObjectBar.CreateEx(this, TBSTYLE_ALTDRAG, WS_CHILD |
         WS_VISIBLE | CBRS_LEFT | CBRS_GRIPPER | CBRS_TOOLTIPS |
         CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
         !m_wndObjectBar.LoadToolBar(IDR_TBOBJECT))
     {
        TRACE0("Failed to create toolbar\n");
        return -1;      // fail to create
     }
     // Find the Black button on the toolbar
     iTBCtlID = m_wndObjectBar.CommandToIndex(ID_OBJECT_TABLE);
     if (iTBCtlID >= 0)
     {
         // Loop through the buttons, setting them to act as radio                 Âbuttons
         for (i= iTBCtlID; i < (iTBCtlID + 3); i++)
             m_wndObjectBar.SetButtonStyle(i, TBBS_BUTTON);
     }

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
    m_wndObjectBar.EnableDocking(CBRS_ALIGN_ANY);

	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);
DockControlBar(&m_wndObjectBar);

//	CString s;
//	s.Format("Opps %u ",m_CurrentView);
//	AfxMessageBox(s);
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers


void CMainFrame::OnUpdateView2dview(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	//if (m_CurrentView==1)
		//pCmdUI->Enable(FALSE);

}

void CMainFrame::OnUpdateView3dview(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	//if (m_CurrentView==2)
	//	pCmdUI->Enable(FALSE);
}



void CMainFrame::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CFrameWnd::OnShowWindow(bShow, nStatus);
	
	// TODO: Add your message handler code here
	
}



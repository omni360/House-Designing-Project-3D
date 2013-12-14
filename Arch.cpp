// Arch.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "Arch.h"
#include <afxpriv.h>


#include "MainFrm.h"
#include "ArchDoc.h"
#include "ArchView.h"
#include "ArchDraw.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CArchApp

BEGIN_MESSAGE_MAP(CArchApp, CWinApp)
	//{{AFX_MSG_MAP(CArchApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_COMMAND(ID_VIEW_3DVIEW, OnView3dview)
	ON_COMMAND(ID_VIEW_2DVIEW, OnView2dview)
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CArchApp construction

CArchApp::CArchApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CArchApp object

CArchApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CArchApp initialization

BOOL CArchApp::InitInstance()
{
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	// Change the registry key under which our settings are stored.
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CArchDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CArchView));
	AddDocTemplate(pDocTemplate);

	// Enable DDE Execute open
	EnableShellOpen();
	RegisterShellFileTypes(TRUE);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;
	// Creating new view, Adding to SDI
	
	  CView* pActiveView= ((CFrameWnd*) m_pMainWnd)->GetActiveView();
	  m_pGDIView = pActiveView;
	  m_pGLView  = (CView*) new GL3dView;

	  CDocument* pCurrentDoc= ((CFrameWnd*) m_pMainWnd)->GetActiveDocument();

	  CCreateContext newContext;
	  newContext.m_pNewViewClass = NULL;
	  newContext.m_pNewDocTemplate = NULL;
	  newContext.m_pLastView = NULL;
	  newContext.m_pCurrentFrame = NULL;
	  newContext.m_pCurrentDoc = pCurrentDoc;

	  UINT ViewId = AFX_IDW_PANE_FIRST + 1;
	  CRect rect(0,0,0,0);
	  m_pGLView->Create(NULL,"Architect 3D View",WS_CHILD, rect, m_pMainWnd, ViewId, &newContext);

	  // the following code may be not needed
	  m_pGLView->SendMessage(WM_INITIALUPDATE,0,0);

     // end of view 
	  
   
	// The one and only window has been initialized, so show and update it.

    
	m_pMainWnd->ShowWindow(SW_MAXIMIZE);
	m_pMainWnd->UpdateWindow();

	// Enable drag/drop open
	m_pMainWnd->DragAcceptFiles();

	

	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
		// No message handlers
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CArchApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CArchApp message handlers


CView* CArchApp::SwitchView(CView *pNewView)
{
	CView* pActiveView =((CFrameWnd*)m_pMainWnd)->GetActiveView();

#ifndef _WIN32
	UINT temp = ::GetWindowWord(pActiveView->m_hWnd,GWW_ID);
	::SetWindowWord(pActiveView->m_hWnd,GWW_ID,
	::GetWindowWord(pNewView->m_hWnd,GWW_ID));
	::SetWindowWord(pNewView->m_hWnd,GWW_ID,temp);
#else
	UINT temp= ::GetWindowLong(pActiveView->m_hWnd, GWL_ID);
	::SetWindowLong(pActiveView->m_hWnd,GWL_ID,	
	::GetWindowLong(pNewView->m_hWnd,GWL_ID));
	::SetWindowLong(pNewView->m_hWnd,GWL_ID,temp);
#endif
	pActiveView->ShowWindow(SW_HIDE);
	pNewView->ShowWindow(SW_SHOW);
	((CFrameWnd*) m_pMainWnd)->SetActiveView(pNewView);
	((CFrameWnd*) m_pMainWnd)->RecalcLayout();
	pNewView->Invalidate();
	return pActiveView;
}


void CArchApp::OnView3dview() 
{
	// TODO: Add your command handler code here
	if (m_pGLView)
		m_pCurrentView=SwitchView(m_pGLView);
	else
		AfxMessageBox("There is no GL View .. Failed...!");
}

void CArchApp::OnView2dview() 
{
	// TODO: Add your command handler code here
	if (m_pGDIView)
		m_pCurrentView=SwitchView(m_pGDIView);
	else
		AfxMessageBox("There is no GDI View .. Failed...!");
}

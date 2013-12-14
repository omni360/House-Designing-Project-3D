// ArchDoc.cpp : implementation of the CArchDoc class
//

#include "stdafx.h"
#include "Arch.h"
#include "ArchCons.h"
#include "ArchDoc.h"
#include "FixtureDialog.h"
#include "StraightWallDlg.h"
#include "Wall.h"
#include "ArchView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CArchDoc

IMPLEMENT_SERIAL(CArchDoc, CDocument,1)

BEGIN_MESSAGE_MAP(CArchDoc, CDocument)
	//{{AFX_MSG_MAP(CArchDoc)
	ON_COMMAND(ID_BUILD_WALL, OnBuildWall)
	ON_UPDATE_COMMAND_UI(ID_BUILD_WALL, OnUpdateBuildWall)
	ON_COMMAND(ID_BUILD_CURVEDWALL, OnBuildCurvedwall)
	ON_UPDATE_COMMAND_UI(ID_BUILD_CURVEDWALL, OnUpdateBuildCurvedwall)
	ON_COMMAND(ID_BUILD_PILLAR, OnBuildPillar)
	ON_UPDATE_COMMAND_UI(ID_BUILD_PILLAR, OnUpdateBuildPillar)
	ON_COMMAND(ID_BUILD_STAIRS, OnBuildStairs)
	ON_UPDATE_COMMAND_UI(ID_BUILD_STAIRS, OnUpdateBuildStairs)
	ON_COMMAND(ID_EDIT_ROTATEELEMENT, OnEditRotateelement)
	ON_UPDATE_COMMAND_UI(ID_EDIT_ROTATEELEMENT, OnUpdateEditRotateelement)
	ON_COMMAND(ID_EDIT_RESIZEELEMENT, OnEditResizeelement)
	ON_UPDATE_COMMAND_UI(ID_EDIT_RESIZEELEMENT, OnUpdateEditResizeelement)
	ON_COMMAND(ID_EDIT_DELETEELEMENT, OnEditDeleteelement)
	ON_UPDATE_COMMAND_UI(ID_EDIT_DELETEELEMENT, OnUpdateEditDeleteelement)
	ON_COMMAND(ID_EDIT_MOVEELEMENT, OnEditMoveelement)
	ON_UPDATE_COMMAND_UI(ID_EDIT_MOVEELEMENT, OnUpdateEditMoveelement)
	ON_COMMAND(ID_EDIT_SELECTELEMENT, OnEditSelectelement)
	ON_UPDATE_COMMAND_UI(ID_EDIT_SELECTELEMENT, OnUpdateEditSelectelement)
	ON_COMMAND(ID_BUILD_FLOOR, OnBuildFloor)
	ON_COMMAND(ID_BUILD_CEIL, OnBuildCeil)
	ON_UPDATE_COMMAND_UI(ID_BUILD_CEIL, OnUpdateBuildCeil)
	ON_COMMAND(ID_OBJECT_CHAIR, OnObjectChair)
	ON_UPDATE_COMMAND_UI(ID_OBJECT_CHAIR, OnUpdateObjectChair)
	ON_COMMAND(ID_BBUILD_SPIRALSTAIR, OnBbuildSpiralstair)
	ON_UPDATE_COMMAND_UI(ID_BBUILD_SPIRALSTAIR, OnUpdateBbuildSpiralstair)
	ON_COMMAND(ID_BUILD_FIXTURE, OnBuildFixture)
	ON_UPDATE_COMMAND_UI(ID_BUILD_FIXTURE, OnUpdateBuildFixture)
	ON_COMMAND(ID_OBJECT_TABLE, OnObjectTable)
	ON_UPDATE_COMMAND_UI(ID_OBJECT_TABLE, OnUpdateObjectTable)
	ON_COMMAND(ID_OBJECT_SOFA, OnObjectSofa)
	ON_UPDATE_COMMAND_UI(ID_OBJECT_SOFA, OnUpdateObjectSofa)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CArchDoc construction/destruction

CArchDoc::CArchDoc()
{
	// TODO: add one-time construction code here

}

CArchDoc::~CArchDoc()
{
	//for (int i=0; i<GetFloorCount();i++)
}

BOOL CArchDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)
	m_BESelected = 0;
//	m_CurrentFloor = 0;
	CPoint pt[]={(0,0),(3000,3000)};
//	m_CurrentFloor = new CFloor(pt,2);
	//if (m_Building.GetFloorCount()>0) m_Building.
	m_Building.AddFloor(pt,2); 
	m_CurrentFloor=m_Building.GetFloorAt(0);
//	FixtureDialog fx;
//	CRect r;
//	fx.DoModal();//==ID_OK)
    top=(0,0);
	bottom=(0,0);
	s_count2=0;
	loc2=0;
	loc1=0;
	loc3=loc4=0;
	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CArchDoc serialization

void CArchDoc::Serialize(CArchive& ar)
{
	

	m_Building.Serialize(ar);
//	m_CurrentFloor->Serialize(ar);

	if (ar.IsStoring())
	{
		// TODO: add storing code here
		ar << m_AppMode
		   << m_AppTool;
	}
	else
	{
		// TODO: add loading code here
		ar >> m_AppMode
		   >> m_AppTool;
	}
}

/////////////////////////////////////////////////////////////////////////////
// CArchDoc diagnostics

#ifdef _DEBUG
void CArchDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CArchDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CArchDoc commands

void CArchDoc::OnBuildWall() 
{
	// TODO: Add your command handler code here
	m_AppMode = MODE_CONSTRUCTION;
	m_AppTool = CONSTRUCT_WALL;
}

void CArchDoc::OnUpdateBuildWall(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_AppTool == CONSTRUCT_WALL);
}

void CArchDoc::OnBuildCurvedwall() 
{
	// TODO: Add your command handler code here
	m_AppMode = MODE_CONSTRUCTION;
	m_AppTool = CONSTRUCT_CWALL;
}

void CArchDoc::OnUpdateBuildCurvedwall(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_AppTool == CONSTRUCT_CWALL);
}

void CArchDoc::OnBuildPillar() 
{
	// TODO: Add your command handler code here
	m_AppMode = MODE_CONSTRUCTION;
	m_AppTool = CONSTRUCT_PILLAR;
}

void CArchDoc::OnUpdateBuildPillar(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_AppTool == CONSTRUCT_PILLAR);
}

void CArchDoc::OnBuildStairs() 
{
	// TODO: Add your command handler code here
	m_AppMode = MODE_CONSTRUCTION;
	m_AppTool = CONSTRUCT_STAIRS;
}

void CArchDoc::OnUpdateBuildStairs(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_AppTool == CONSTRUCT_STAIRS);	
}




void CArchDoc::OnEditRotateelement() 
{
	// TODO: Add your command handler code here
	m_AppMode = MODE_ADJUSTMENT;
	m_AppTool = ADJUSTMENT_ROTATE;
}

void CArchDoc::OnUpdateEditRotateelement(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_AppTool == ADJUSTMENT_ROTATE); 
}

void CArchDoc::OnEditResizeelement() 
{
	// TODO: Add your command handler code here
	m_AppMode = MODE_ADJUSTMENT;
	m_AppTool = ADJUSTMENT_RESIZE; 	
}

void CArchDoc::OnUpdateEditResizeelement(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_AppTool==ADJUSTMENT_RESIZE); 
}

void CArchDoc::OnEditDeleteelement() 
{
	// TODO: Add your command handler code here
	m_AppMode = MODE_ADJUSTMENT;
	m_AppTool = ADJUSTMENT_SELECT;
	if (m_BESelected)
		if (m_CurrentFloor)
		{
			m_CurrentFloor->RemoveElement(m_BESelected);
			m_BESelected= (CBuildingElement *) 0;
			UpdateAllViews(0);
		}

}

void CArchDoc::OnUpdateEditDeleteelement(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	//pCmdUI->SetCheck(m_AppTool==ADJUSTMENT_DELETE);
}

void CArchDoc::OnEditMoveelement() 
{
	// TODO: Add your command handler code here
	m_AppMode = MODE_ADJUSTMENT;
	m_AppTool = ADJUSTMENT_MOVE; 
	
}

void CArchDoc::OnUpdateEditMoveelement(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_AppTool==ADJUSTMENT_MOVE); 
}

void CArchDoc::OnEditSelectelement() 
{
	// TODO: Add your command handler code here
	m_AppMode = MODE_ADJUSTMENT;
	m_AppTool = ADJUSTMENT_SELECT; 
}

void CArchDoc::OnUpdateEditSelectelement(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_AppTool == ADJUSTMENT_SELECT); 
}

BOOL CArchDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;
	
	// TODO: Add your specialized creation code here
	m_CurrentFloor=m_Building.GetFloorAt(0);
	SendInitialUpdate();
	return TRUE;
}

void CArchDoc::DeleteContents() 
{
	// TODO: Add your specialized code here and/or call the base class
	if (m_Building.GetFloorCount()>0) m_Building.RemoveFloorAll();
	CDocument::DeleteContents();
}

void CArchDoc::OnBuildFloor() 
{
	// TODO: Add your command handler code here
	m_BESelected = 0;
//	m_CurrentFloor = 0;
	CPoint pt[]={(0,0),(300,300)};

	if (m_Building.GetFloorCount()==1) 
		m_Building.AddFloor(pt,2);
else
	 if (m_Building.GetFloorCount()==2) 
		m_Building.AddFloor(pt,3);
else
	 if (m_Building.GetFloorCount()==3) 
		m_Building.AddFloor(pt,4);	
	
else
	 if (m_Building.GetFloorCount()==4) 
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
	int cf=m_Building.GetFloorCount();
	m_CurrentFloor=m_Building.GetFloorAt(cf-1);
	UpdateAllViews(0);
}

//DEL void CArchDoc::OnBuildCeilling() 
//DEL {
//DEL 	// TODO: Add your command handler code here
//DEL 		m_AppMode = MODE_CONSTRUCTION;
//DEL 		m_AppTool = CONSTRUCT_CEILPLANE;
//DEL }





//DEL void CArchDoc::OnBuildCelling() 
//DEL {
//DEL 	// TODO: Add your command handler code here
//DEL 		m_AppMode = MODE_CONSTRUCTION;
//DEL 		m_AppTool = CONSTRUCT_CEILPLANE;
//DEL }

//DEL void CArchDoc::OnUpdateBuildCelling(CCmdUI* pCmdUI) 
//DEL {
//DEL 	// TODO: Add your command update UI handler code here
//DEL pCmdUI->SetCheck(m_AppTool == CONSTRUCT_CEILPLANE);
//DEL 	
//DEL }

void CArchDoc::OnBuildCeil() 
{
	// TODO: Add your command handler code here
		m_AppMode = MODE_CONSTRUCTION;
		m_AppTool = CONSTRUCT_CEILPLANE;
}

void CArchDoc::OnUpdateBuildCeil(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_AppTool == CONSTRUCT_CEILPLANE);
}

int CArchDoc::calculate1()
{
         
return val;
		 
}

void CArchDoc::OnObjectChair() 
{
	// TODO: Add your command handler code here
		m_AppMode = MODE_CONSTRUCTION;
		m_AppTool = CONSTRUCT_CHAIROBJ;	
             
}

void CArchDoc::OnUpdateObjectChair(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_AppTool == CONSTRUCT_CHAIROBJ);		
}

void CArchDoc::OnBbuildSpiralstair() 
{
	// TODO: Add your command handler code here
	m_AppMode = MODE_CONSTRUCTION;
	m_AppTool = CONSTRUCT_SPIRALSTAIR;	
             
}

void CArchDoc::OnUpdateBbuildSpiralstair(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_AppTool == CONSTRUCT_SPIRALSTAIR);
}

void CArchDoc::OnBuildFixture() 
{
	// TODO: Add your command handler code here
	m_AppMode = MODE_CONSTRUCTION;
	m_AppTool =  CONSTRUCT_FIXTUREWALL ;		
}

void CArchDoc::OnUpdateBuildFixture(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
pCmdUI->SetCheck(m_AppTool ==  CONSTRUCT_FIXTUREWALL );
}	


void CArchDoc::OnObjectTable() 
{
	// TODO: Add your command handler code here
	m_AppMode = MODE_CONSTRUCTION;
	m_AppTool = CONSTRUCT_TABLEOBJ;	
             
}

void CArchDoc::OnUpdateObjectTable(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_AppTool == CONSTRUCT_TABLEOBJ );
}

void CArchDoc::OnObjectSofa() 
{
	// TODO: Add your command handler code here
	m_AppMode = MODE_CONSTRUCTION;
	m_AppTool = CONSTRUCT_SOFAOBJ;	
}

void CArchDoc::OnUpdateObjectSofa(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
		pCmdUI->SetCheck(m_AppTool == CONSTRUCT_SOFAOBJ);
}

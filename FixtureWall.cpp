// FixtureWall.cpp: implementation of the CFixtureWall class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "arch.h"
#include "FixtureWall.h"
#include "ArchCons.h"
#include <math.h>
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


IMPLEMENT_SERIAL(CFixtureWall,CBuildingElement,1)



CFixtureWall::CFixtureWall()
{
	m_uiWidth = 4;
	m_IsTexturizedSideA=FALSE;
	m_IsTexturizedSideB=FALSE;
	m_isdoor=FALSE;
	m_iswindow=FALSE;
    m_basep=0.0;
	loc1=0;
}

CFixtureWall::~CFixtureWall()
{

}

void CFixtureWall::Draw(CDC *pDC, BOOL bSelected)
{
	CPen   pen, *oldpen;
	LOGPEN p;
	p.lopnColor = (bSelected ? RGB(255,0,0) : RGB(0,0,0));
	p.lopnStyle = PS_SOLID;
	p.lopnWidth = CPoint(m_uiWidth,0);
	pen.CreatePenIndirect(&p);
	oldpen = pDC->SelectObject(&pen);
	pDC->MoveTo(m_ptFirstPosition);
	pDC->LineTo(m_ptSecondPosition);
	pDC->SelectObject(oldpen);
}

BOOL CFixtureWall::HitTest(CPoint ptHit)
{
	int Tol=m_uiWidth;
	const int dxLine = m_ptSecondPosition.x - m_ptFirstPosition.x;
	const int dyLine = m_ptSecondPosition.y - m_ptFirstPosition.y;
// 1 - a
	const int dx1 = m_ptFirstPosition.x - ptHit.x;
	const int dy1 = m_ptFirstPosition.y - ptHit.y;

	if ((dxLine > 0 && dx1 > 0) || (dyLine > 0 && dy1 > 0) ||
		(dxLine < 0 && dx1 < 0) || (dyLine < 0 && dy1 < 0))
		return (sqrt((dx1*dx1)+(dy1*dy1))<=Tol);
// 1 - b
	const int dx2 = m_ptSecondPosition.x - ptHit.x;
	const int dy2 = m_ptSecondPosition.y - ptHit.y;

	if ((dxLine > 0 && dx2 < 0) || (dyLine < 0 && dy2 > 0) ||
		(dxLine < 0 && dx2 > 0) || (dyLine > 0 && dy2 < 0))
		return (sqrt((dx2*dx2)+(dy2*dy2))<=Tol);

	Tol *= (int) sqrt((dxLine*dxLine)+(dyLine*dyLine));
	const int diff = (dy1*dx2)-(dy2*dx1);
	return (diff>=-Tol && diff <= Tol);
}

CFixtureWall::CFixtureWall(CPoint p1, CPoint p2)
{
	
	
	m_ptFirstPosition=p1;
	m_ptSecondPosition=p2;
	m_SideAColor=RGB(0,0,50);
	m_SideBColor=RGB(0,0,50);
//	m_SideATexture="not implemented.";
//	m_SideBTexture="not implemented.";
	m_uiHeight=120;
	m_uiWidth=9;
	m_IsTexturizedSideA=FALSE;
	m_IsTexturizedSideB=FALSE;
	m_isdoor=FALSE;
	m_iswindow=FALSE;
	m_basep=0.0;
    
	loc1=0; 
}

CFixtureWall::CFixtureWall(CFixtureWall& fw)
{
	m_ptFirstPosition = fw.m_ptFirstPosition;
	m_ptSecondPosition= fw.m_ptSecondPosition;
    
	//m_ptdoortop=m_stwall.SetValue().m_ptdoortop;
	
	//m_ptdoorbottom=m_stwall.SetValue().m_ptdoorbottom;;

	m_SideAColor = fw.m_SideAColor;
	m_SideBColor = fw.m_SideBColor;
//	m_SideATexture = w.m_SideATexture;
//	m_SideBTexture = w.m_SideBTexture;
	m_uiHeight=fw.m_uiHeight;
	m_uiWidth=fw.m_uiWidth;
	m_basep=fw.m_basep;
	m_IsTexturizedSideA=fw.m_IsTexturizedSideA;
	m_IsTexturizedSideB=fw.m_IsTexturizedSideB;
	m_isdoor=FALSE;
	m_iswindow=FALSE;
	diff=(int)((m_ptSecondPosition.x-m_ptFirstPosition.x)/58);
    loc1=fw.loc1;	 
	
	
//    calculate(); 
    
}

void CFixtureWall::AddFixture(CFixture *pFix)
{
	m_FixtureList.Add(pFix);
}

void CFixtureWall::RemoveFixture(CFixture *pFix)
{
	//m_FixtureList
}

UINT CFixtureWall::FixtureCount() const
{
	return (m_FixtureList.GetSize());
}

void CFixtureWall::Serialize(CArchive &ar)
{
	CBuildingElement::Serialize(ar);
	m_FixtureList.Serialize(ar);
//	m_SideATexture.Serialize(ar);
//	m_SideBTexture.Serialize(ar);
	m_door.Serialize(ar);
	m_window.Serialize(ar);
	if(ar.IsStoring())
	{
		ar << m_IsTexturizedSideA
		   << m_IsTexturizedSideB
		   << m_ptFirstPosition
		   << m_ptSecondPosition
		   << m_SideAColor
		   << m_SideBColor
		   << m_uiHeight
		   << m_uiWidth
		   << m_isdoor
		   << m_iswindow
		   << m_SideATexture
		   << m_SideBTexture;

	}
	else
	{
		ar >> m_IsTexturizedSideA
		   >> m_IsTexturizedSideB
		   >> m_ptFirstPosition
		   >> m_ptSecondPosition
		   >> m_SideAColor
		   >> m_SideBColor
		   >> m_uiHeight
		   >> m_uiWidth
		   >> m_isdoor
		   >> m_iswindow
		   >> m_SideATexture
		   >> m_SideBTexture;
	}
}

UINT CFixtureWall::GetType()
{
	return BUILDING_ELEMENT_FIXTUREWALL;
}


int CFixtureWall::calculate2(CFixtureWall fw)
{
	diff=(int)((fw.m_ptSecondPosition.x-fw.m_ptFirstPosition.x)/58);
	return diff;
}

// Ceiling.cpp: implementation of the CCeiling class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Arch.h"
#include "Ceiling.h"
#include "ArchCons.h"
#include "math.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_SERIAL(CCeiling,CBuildingElement,1)
CCeiling::CCeiling()
{
m_uiWidth=4;
}

CCeiling::~CCeiling()
{

}

void CCeiling::Draw(CDC *pDC, BOOL bSelected)
{
	CPen   pen, *oldpen;
	LOGPEN p;
	p.lopnColor = (bSelected ? RGB(255,0,0) : RGB(0,0,0));
	p.lopnStyle = PS_SOLID;
	p.lopnWidth = CPoint(m_uiWidth,0);
	pen.CreatePenIndirect(&p);
	oldpen = pDC->SelectObject(&pen);
	//pDC->MoveTo(m_ptFirstPosition);
	//pDC->LineTo(m_ptSecondPosition);
	pDC->Rectangle(m_ptFirstPosition.x,m_ptFirstPosition.y,m_ptSecondPosition.x,m_ptSecondPosition.y);
	pDC->SelectObject(oldpen);
}

BOOL CCeiling::HitTest(CPoint ptHit)
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

UINT CCeiling::GetType()
{
	return BUILDING_ELEMENT_CEILING;
}

void CCeiling::Serialize(CArchive &ar)
{
CBuildingElement::Serialize(ar);
//	m_FixtureList.Serialize(ar);
//	m_SideATexture.Serialize(ar);
//	m_SideBTexture.Serialize(ar);
//	m_door.Serialize(ar);
//	m_window.Serialize(ar);
	if(ar.IsStoring())
	{
		ar << m_ptFirstPosition
		   << m_ptSecondPosition
		   << m_SideAColor
		   << m_SideBColor
		   << m_uiHeight
		   << m_uiWidth;

	}
	else
	{
		ar >> m_ptFirstPosition
		   >> m_ptSecondPosition
		   >> m_SideAColor
		   >> m_SideBColor
		   >> m_uiHeight
		   >> m_uiWidth;
		   
	}
}

CCeiling::CCeiling(CPoint p1, CPoint p2)
{
	m_ptFirstPosition=p1;
	m_ptSecondPosition=p2;
    //m_ptThirdPosition=p2.x;
	//m_ptFourthPosition=p2.y;

	m_SideAColor=RGB(255,255,200);
	m_SideBColor=RGB(255,255,200);
//	m_SideATexture="not implemented.";
//	m_SideBTexture="not implemented.";
	m_uiHeight=120;
	m_uiWidth=9;
}

CCeiling::CCeiling(CCeiling &c)
{
    m_ptFirstPosition = c.m_ptFirstPosition;
	m_ptSecondPosition= c.m_ptSecondPosition;
	m_SideAColor = c.m_SideAColor;
	m_SideBColor = c.m_SideBColor;
//	m_SideATexture = w.m_SideATexture;
//	m_SideBTexture = w.m_SideBTexture;
	m_uiHeight=c.m_uiHeight;
	m_uiWidth=c.m_uiWidth;
}

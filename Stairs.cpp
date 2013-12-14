// Stairs.cpp: implementation of the CStairs class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "Arch.h"
#include "Stairs.h"
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
IMPLEMENT_SERIAL(CStairs,CBuildingElement,1)
CStairs::CStairs()
{

}

CStairs::~CStairs()
{

}

CStairs::CStairs(CPoint pt1, CPoint pt2)
{
	m_ptFirstPosition=pt1;
	m_ptSecondPosition=pt2;
	m_uiHeight=120;
	m_uiWidth=15;
	m_StairColor=RGB(255,255,200);

}

BOOL CStairs::HitTest(CPoint ptHit)
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

void CStairs::Draw(CDC* pDC, BOOL bSelected)
{
	CPen   pen, *oldpen;
	LOGPEN p;
	p.lopnColor = (bSelected ? RGB(255,0,0) : RGB(200,200,200));
	p.lopnStyle = PS_SOLID;
	p.lopnWidth = CPoint(m_uiWidth,0);
	pen.CreatePenIndirect(&p);
	oldpen = pDC->SelectObject(&pen);
    //test case III

	pDC->MoveTo(m_ptFirstPosition);
//	pDC->AngleArc(m_ptFirstPosition.x,m_ptFirstPosition.y,m_uiWidth,Deg,360);
	pDC->LineTo(m_ptSecondPosition);
	//CPoint p1;
	//p1.x = m_uiWidth + sin(90);
	//p1.y = m_uiWidth + cos(90);
	//pDC->LineTo(p1);
	//**** new ****//
/*	CPoint p1=m_ptFirstPosition;
	CPoint p2=m_ptSecondPosition;
	CPoint p3, p4;
	pDC->LPtoDP(&p1);
	pDC->LPtoDP(&p2);
	p3.y = long (p1.y / (1 - pow((p2.x - p1.x),3)/pow((p2.y-p1.y),2)));
	p3.x = long (p1.x + ((p2.x - p1.x) / (p2.y - p1.y)) * p3.y);
	pDC->LPtoDP(&p1);
	pDC->LPtoDP(&p3);
	pDC->MoveTo(p1);
	pDC->LineTo(p2);
	pDC->MoveTo(p1);
	pDC->LineTo(p3);
*/
	//**** end new ****//
	pDC->SelectObject(oldpen);
}

CStairs::CStairs(CStairs &s)
{
	m_ptFirstPosition = s.m_ptFirstPosition;
	m_ptSecondPosition= s.m_ptSecondPosition;
	m_uiHeight=s.m_uiHeight;
	m_uiWidth=s.m_uiWidth;
	m_StairColor=s.m_StairColor;
}

void CStairs::Serialize(CArchive &ar)
{
	CBuildingElement::Serialize(ar);
	
	if(ar.IsStoring())
	{
		ar << m_ptFirstPosition
		   << m_ptSecondPosition
		   << m_StairColor
		   << m_uiHeight
		   << m_uiWidth;
	}
	else
	{
		ar >> m_ptFirstPosition
		   >> m_ptSecondPosition
		   >> m_StairColor
		   >> m_uiHeight
		   >> m_uiWidth;
	}
}

unsigned int CStairs::GetType()
{
	return BUILDING_ELEMENT_STAIRS;
}

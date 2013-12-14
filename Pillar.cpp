// Pillar.cpp: implementation of the CPillar class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "Arch.h"
#include "Pillar.h"
#include "ArchCons.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_SERIAL(CPillar,CBuildingElement,1)
CPillar::CPillar()
{

}

CPillar::~CPillar()
{

}

void CPillar::Draw(CDC *pDC, BOOL bSelected)
{
	CPen   pen, *oldpen;
	LOGPEN p;
	p.lopnColor = (bSelected ? RGB(255,0,0) : RGB(0,0,0));
	p.lopnStyle = PS_SOLID;
	p.lopnWidth = CPoint(2,0);
	pen.CreatePenIndirect(&p);
	oldpen = pDC->SelectObject(&pen);
	CPoint p1, p2;
	p1.x = m_ptPosition.x - int(m_uiWidth / 2.0)-1;
	p1.y = m_ptPosition.y - int(m_uiWidth / 2.0)-1;
	p2.x = m_ptPosition.x + int(m_uiWidth / 2.0)+1;
	p2.y = m_ptPosition.y + int(m_uiWidth / 2.0)+1;

	CRect rect(p1,p2);

	if (m_uiType)
		pDC->Rectangle(&rect);
	else
		pDC->Ellipse(&rect);


	pDC->SelectObject(oldpen);
}

BOOL CPillar::HitTest(CPoint ptHit)
{
	CPoint p1, p2;
	p1.x = m_ptPosition.x - int(m_uiWidth / 2.0)-1;
	p1.y = m_ptPosition.y - int(m_uiWidth / 2.0)-1;
	p2.x = m_ptPosition.x + int(m_uiWidth / 2.0)+1;
	p2.y = m_ptPosition.y + int(m_uiWidth / 2.0)+1;
	CRect rect(p1,p2);
	return rect.PtInRect(ptHit);
}

CPillar::CPillar(CPoint point)
{
	m_ptPosition=point;
	m_Color=RGB(255,255,200);
	m_uiType=0;
//	m_Texture="not implemented";
	m_uiHeight=120;
	m_uiWidth=12;
}

CPillar::CPillar(CPillar &p)
{

	m_ptPosition=p.m_ptPosition;
	m_Color	  = p.m_Color;
	m_uiType	  = p.m_uiType;
//	m_Texture = p.m_Texture;
	m_uiHeight= p.m_uiHeight;
	m_uiWidth = p.m_uiWidth;
}

void CPillar::Serialize(CArchive &ar)
{
	CBuildingElement::Serialize(ar);
	
	
	
	if(ar.IsStoring())
	{
		ar << m_Color
		   << m_uiType
		   << m_ptPosition
		   << m_uiHeight
		   << m_uiWidth;
	}
	else
	{
		ar >> m_Color
		   >> m_uiType
		   >> m_ptPosition
		   >> m_uiHeight
		   >> m_uiWidth;
	}


}

unsigned int CPillar::GetType()
{
	if (m_uiType==0)
		return BUILDING_ELEMENT_ROUNDPILLAR;
	else
		return BUILDING_ELEMENT_SQUAREPILLAR;
}

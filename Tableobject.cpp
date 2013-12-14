// Tableobject.cpp: implementation of the CTableobject class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "arch.h"
#include "Tableobject.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTableobject::CTableobject()
{

}

CTableobject::~CTableobject()
{

}
void CTableobject::Draw(CDC *pDC, BOOL bSelected)
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


	if (m_uiType==0)
//	if(ch1==0)
	{
		pDC->Rectangle(&rect);
        pDC->MoveTo(p1.x,p2.y);
		pDC->LineTo(p1.x+5,p2.y-5);
		
		pDC->MoveTo(p2.x,p2.y);
		pDC->LineTo(p2.x+5,p2.y-5);
		
		pDC->MoveTo(p2.x+5,p1.y-5);
		pDC->LineTo(p2.x,p1.y);
		
		pDC->MoveTo(p2.x-5,p1.y-5);
		pDC->LineTo(p1.x,p1.y);
		
	}
	else
		if(m_uiType==1)
        {
	    pDC->Ellipse(&rect);
        pDC->MoveTo(p1.x+5,p2.y+5);
		pDC->LineTo(p1.x,p2.y);
		
		pDC->MoveTo(p2.x,p2.y);
		pDC->LineTo(p2.x+5,p2.y+5);
		
		pDC->MoveTo(p1.x,p1.y);
		pDC->LineTo(p1.x+5,p1.y+5);
		
		pDC->MoveTo(p2.x,p1.y);
		pDC->LineTo(p2.x+5,p1.y+5);
		
	//	pDC->MoveTo(p2.x-5,p2.y+5);
	//	pDC->LineTo(p2.x-5,p2.y+10);
		}
	else
		if(m_uiType==2)
        {
		pDC->Rectangle(&rect);
		pDC->MoveTo(p2.x-5,p1.y+5);
		pDC->LineTo(p2.x-5,p1.y+5);
		
		}
	else
		if(m_uiType==3)
        {
		pDC->Rectangle(&rect);
		}
	else
		if(m_uiType==4)
		{
		
		pDC->Rectangle(&rect);
        pDC->MoveTo(p1.x,p2.y);
		pDC->LineTo(p1.x+5,p2.y-5);
		
		pDC->MoveTo(p2.x,p2.y);
		pDC->LineTo(p2.x+5,p2.y-5);
		
		pDC->MoveTo(p2.x+5,p1.y-5);
		pDC->LineTo(p2.x,p1.y);
		
		pDC->MoveTo(p2.x-5,p1.y-5);
		pDC->LineTo(p1.x,p1.y);
		pDC->Ellipse(&rect);
		}

	pDC->SelectObject(oldpen);
}

BOOL CTableobject::HitTest(CPoint ptHit)
{
	CPoint p1, p2;
	p1.x = m_ptPosition.x - int(m_uiWidth / 2.0)-1;
	p1.y = m_ptPosition.y - int(m_uiWidth / 2.0)-1;
	p2.x = m_ptPosition.x + int(m_uiWidth / 2.0)+1;
	p2.y = m_ptPosition.y + int(m_uiWidth / 2.0)+1;
	CRect rect(p1,p2);
	return rect.PtInRect(ptHit);
}

CTableobject::CTableobject(CPoint point)
{  // ch1=0;
	m_ptPosition=point;
	m_Color=RGB(255,255,200);
	m_uiType=0;
//	m_Texture="not implemented";
	m_uiHeight=120;
	m_uiWidth=12;
}

CTableobject::CTableobject(CTableobject &ta)
{
//    ch1=ch.ch1;
	m_ptPosition=ta.m_ptPosition;
	m_Color	  = ta.m_Color;
	m_uiType	  = ta.m_uiType;
//	m_Texture = p.m_Texture;
	m_uiHeight= ta.m_uiHeight;
	m_uiWidth = ta.m_uiWidth;
}

void CTableobject::Serialize(CArchive &ar)
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

unsigned int CTableobject::GetType()
{

	if (m_uiType==0)
		return BUILDING_ELEMENT_TABLE1;
	else
		if(m_uiType==1)
        	return BUILDING_ELEMENT_TABLE2;	
	else
		if(m_uiType==2)
        	return BUILDING_ELEMENT_TABLE3;	
	else
		if(m_uiType==3)
        	return BUILDING_ELEMENT_TABLE4;
	else
		if(m_uiType==4)
        	return BUILDING_ELEMENT_TABLE5;	
	
	//	return BUILDING_ELEMENT_CHAIROBJ;
		else
		return 1;
	}

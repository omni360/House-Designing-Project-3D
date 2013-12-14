// ChairObject.cpp: implementation of the CChairObject class.
//
//////////////////////////////////////////////////////////////////////


#include "stdafx.h"
#include "Arch.h"
#include "ChairObject.h"
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
IMPLEMENT_SERIAL(CChairObject,CBuildingElement,1)
CChairObject::CChairObject()
{

}

CChairObject::~CChairObject()
{

}
void CChairObject::Draw(CDC *pDC, BOOL bSelected)
{
	CPen   pen, *oldpen;
	LOGPEN p;
	p.lopnColor = (bSelected ? RGB(255,0,0) : RGB(0,0,0));
    //m_bolSelecFlag = bSelected;

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
		pDC->LineTo(p1.x-5,p2.y+5);
		
		pDC->MoveTo(p2.x,p2.y);
		pDC->LineTo(p2.x-5,p2.y+5);
		
		pDC->MoveTo(p1.x-5,p2.y+5);
		pDC->LineTo(p2.x-5,p2.y+5);
		
		pDC->MoveTo(p1.x-5,p2.y+5);
		pDC->LineTo(p1.x-5,p2.y+10);
		
		pDC->MoveTo(p2.x-5,p2.y+5);
		pDC->LineTo(p2.x-5,p2.y+10);
	}
	else
		if(m_uiType==1)
        {
	    pDC->Ellipse(&rect);
        pDC->MoveTo(p1.x,p2.y);
		pDC->LineTo(p1.x-5,p2.y+5);
		
		pDC->MoveTo(p2.x,p2.y);
		pDC->LineTo(p2.x-5,p2.y+5);
		
		pDC->MoveTo(p1.x-5,p2.y+5);
		pDC->LineTo(p2.x-5,p2.y+5);
		
		pDC->MoveTo(p1.x-5,p2.y+5);
		pDC->LineTo(p1.x-5,p2.y+10);
		
		pDC->MoveTo(p2.x-5,p2.y+5);
		pDC->LineTo(p2.x-5,p2.y+10);
		}
	else
		if(m_uiType==2)
        {
		pDC->Rectangle(&rect);
		}
			//	else
//		pDC->Ellipse(&rect);


	pDC->SelectObject(oldpen);
}

BOOL CChairObject::HitTest(CPoint ptHit)
{
	CPoint p1, p2;
	p1.x = m_ptPosition.x - int(m_uiWidth / 2.0)-1;
	p1.y = m_ptPosition.y - int(m_uiWidth / 2.0)-1;
	p2.x = m_ptPosition.x + int(m_uiWidth / 2.0)+1;
	p2.y = m_ptPosition.y + int(m_uiWidth / 2.0)+1;
	CRect rect(p1,p2);
	return rect.PtInRect(ptHit);
}

CChairObject::CChairObject(CPoint point)
{  // ch1=0;
	m_ptPosition=point;
	m_Color=RGB(255,255,200);
	m_uiType=0;
//	m_Texture="not implemented";
	m_uiHeight=120;
	m_uiWidth=12;
   // m_bolSelecFlag = false;
}

CChairObject::CChairObject(CChairObject &ch)
{
//    ch1=ch.ch1;
	m_ptPosition=ch.m_ptPosition;
	m_Color	  = ch.m_Color;
	m_uiType	  = ch.m_uiType;
//	m_Texture = p.m_Texture;
	m_uiHeight= ch.m_uiHeight;
	m_uiWidth = ch.m_uiWidth;
   

}

void CChairObject::Serialize(CArchive &ar)
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

unsigned int CChairObject::GetType()
{

	if (m_uiType==0)
		return BUILDING_ELEMENT_CHAIR1;
	else
		if(m_uiType==1)
        	return BUILDING_ELEMENT_CHAIR2;	
	else
		if(m_uiType==2)
        	return BUILDING_ELEMENT_CHAIR3;	
	else
		if(m_uiType==3)
        	return BUILDING_ELEMENT_CHAIR4;	
	else
		if(m_uiType==4)
        	return BUILDING_ELEMENT_CHAIR5;	
	
		//return BUILDING_ELEMENT_CHAIROBJ;
    else
		 return 1;
	}

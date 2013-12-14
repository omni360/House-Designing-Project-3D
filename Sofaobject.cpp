// Sofaobject.cpp: implementation of the CSofaobject class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "arch.h"
#include "Sofaobject.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSofaobject::CSofaobject()
{

}

CSofaobject::~CSofaobject()
{

}
void CSofaobject::Draw(CDC *pDC, BOOL bSelected)
{
	CPen   pen, *oldpen;
	LOGPEN p;
	p.lopnColor = (bSelected ? RGB(255,0,0) : RGB(0,0,0));
	//selectionFlag = bSelected;
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
		pDC->Rectangle(p1.x-5,p1.y+10,p2.x+10,p2.y+5);
		/*  pDC->MoveTo(p1.x,p2.y);
		pDC->LineTo(p1.x+5,p2.y-5);
		
		pDC->MoveTo(p2.x,p2.y);
		pDC->LineTo(p2.x+5,p2.y-5);
		
		pDC->MoveTo(p2.x+5,p1.y-5);
		pDC->LineTo(p2.x,p1.y);
		
		pDC->MoveTo(p2.x-5,p1.y-5);
		pDC->LineTo(p1.x,p1.y);
		*/
	}
	else
		if(m_uiType==1)
        {
	    pDC->Ellipse(&rect);
		pDC->Rectangle(p1.x-5,p1.y+10,p2.x+10,p2.y+5);
       /* pDC->MoveTo(p1.x+5,p2.y+5);
		pDC->LineTo(p1.x,p2.y);
		
		pDC->MoveTo(p2.x,p2.y);
		pDC->LineTo(p2.x+5,p2.y+5);
		
		pDC->MoveTo(p1.x,p1.y);
		pDC->LineTo(p1.x+5,p1.y+5);
		
		pDC->MoveTo(p2.x,p1.y);
		pDC->LineTo(p2.x+5,p1.y+5);
		
	//	pDC->MoveTo(p2.x-5,p2.y+5);
	//	pDC->LineTo(p2.x-5,p2.y+10);*/
		}
	else
		if(m_uiType==2)
        {
		pDC->Ellipse(&rect);
		pDC->Rectangle(p1.x-5,p1.y+10,p2.x+10,p2.y+5);
		pDC->MoveTo(p2.x,p1.y);
		pDC->LineTo(p2.x+10,p1.y+10);
		
		}
	else
		if(m_uiType==3)
        {
		pDC->Rectangle(&rect);
		pDC->Rectangle(p1.x-5,p1.y+10,p2.x+10,p2.y+5);
		pDC->MoveTo(p2.x,p1.y);
		pDC->LineTo(p2.x+10,p1.y+10);
		
		}
	else
		if(m_uiType==4)
		{
		
		pDC->Rectangle(&rect);
      //  pDC->MoveTo(p1.x,p2.y);
	//	pDC->LineTo(p1.x+5,p2.y-5);
		
	//	pDC->MoveTo(p2.x,p2.y);
	//	pDC->LineTo(p2.x+5,p2.y-5);
		
	//	pDC->MoveTo(p2.x+5,p1.y-5);
	//	pDC->LineTo(p2.x,p1.y);
		
	//	pDC->MoveTo(p2.x-5,p1.y-5);
	//	pDC->LineTo(p1.x,p1.y);
		pDC->Ellipse(&rect);
		pDC->Rectangle(p1.x-5,p1.y+10,p2.x+10,p2.y+5);
		}

	pDC->SelectObject(oldpen);
}

BOOL CSofaobject::HitTest(CPoint ptHit)
{
	CPoint p1, p2;
	p1.x = m_ptPosition.x - int(m_uiWidth / 2.0)-1;
	p1.y = m_ptPosition.y - int(m_uiWidth / 2.0)-1;
	p2.x = m_ptPosition.x + int(m_uiWidth / 2.0)+1;
	p2.y = m_ptPosition.y + int(m_uiWidth / 2.0)+1;

	CRect rect(p1,p2);
	return rect.PtInRect(ptHit);
}

CSofaobject::CSofaobject(CPoint point)
{  // ch1=0;
	m_ptPosition=point;
	m_Color=RGB(255,255,200);
	m_uiType=0;
//	m_Texture="not implemented";
	m_uiHeight=120;
	m_uiWidth=12;
}

CSofaobject::CSofaobject(CSofaobject &sf)
{
//    ch1=ch.ch1;
	m_ptPosition=sf.m_ptPosition;
	m_Color	  = sf.m_Color;
	m_uiType	  = sf.m_uiType;
//	m_Texture = p.m_Texture;
	m_uiHeight= sf.m_uiHeight;
	m_uiWidth = sf.m_uiWidth;
}

void CSofaobject::Serialize(CArchive &ar)
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

unsigned int CSofaobject::GetType()
{

	if (m_uiType==0)
		return BUILDING_ELEMENT_SOFA1;
	else
		if(m_uiType==1)
        	return BUILDING_ELEMENT_SOFA2;	
	else
		if(m_uiType==2)
        	return BUILDING_ELEMENT_SOFA3;	
	else
		if(m_uiType==3)
        	return BUILDING_ELEMENT_SOFA4;
	else
		if(m_uiType==4)
        	return BUILDING_ELEMENT_SOFA5;	
	else 
		return 1;
		//return BUILDING_ELEMENT_CHAIROBJ;
	}

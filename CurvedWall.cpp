// CurvedWall.cpp: implementation of the CCurvedWall class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "Arch.h"
#include "CurvedWall.h"
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
IMPLEMENT_SERIAL(CCurvedWall,CWall,1)
CCurvedWall::CCurvedWall()
{
m_IsTexturizedSideA=FALSE;
m_IsTexturizedSideB=FALSE;
}

CCurvedWall::~CCurvedWall()
{

}

void CCurvedWall::Draw(CDC *pDC, BOOL bSelected)
{
	CPen   pen, *oldpen;
	CPoint ptlist[]={m_ptFirstPosition,m_ptControlPosition1,
		m_ptControlPosition2,m_ptSecondPosition};
	LOGPEN p;
	p.lopnColor = (bSelected ? RGB(255,0,0) : RGB(0,0,0));
	p.lopnStyle = PS_SOLID;
	p.lopnWidth = CPoint(m_uiWidth,0);
	pen.CreatePenIndirect(&p);
	oldpen = pDC->SelectObject(&pen);
	pDC->PolyBezier(ptlist,4);
	pDC->SelectObject(oldpen);

}

BOOL CCurvedWall::HitTest(CPoint ptHit)
{
	CPoint pCurve[4]={m_ptFirstPosition,m_ptControlPosition1,
		m_ptControlPosition2,m_ptSecondPosition};
	int Tol=m_uiWidth;
	for (int index=0;index<4;++index)
	{
		const int dX = ptHit.x - pCurve[index].x;
		const int dY = ptHit.y - pCurve[index].y;
		if (sqrt((dX * dX)+(dY * dY))<=Tol)
			return TRUE;
	}
	double curve_dist = 0;
	for (int seg=0; seg < 3; ++seg)
	{
		const int dXseg = pCurve[seg].x - pCurve[seg + 1].x;
		const int dYseg = pCurve[seg].y - pCurve[seg + 1].y;
		curve_dist += sqrt((dXseg*dXseg) + (dYseg*dYseg));
	}
	double time_step = 1.0 / curve_dist;

	//second test
	for (double t = 0.0; t < 1.0; t += time_step)
	{
		const double t_squared = t * t;
		const double one_minus_t = (1.0 - t);
		const double one_minus_t_squared = one_minus_t * one_minus_t;

		const double c1 = one_minus_t_squared * one_minus_t;
		const double c2 = 3 * t * one_minus_t_squared;
		const double c3 = 3 * t_squared * one_minus_t;
		const double c4 = t_squared * t;

		const double xt = (c1 * pCurve[0].x) + (c2 * pCurve[1].x) + 
						  (c3 * pCurve[2].x) + (c4 * pCurve[3].x) ;
		const double dX = ptHit.x - xt;
		if (dX >= -Tol && dX <= Tol)
		{
			const double yt = (c1 * pCurve[0].y) + (c2 * pCurve[1].y) + 
						      (c3 * pCurve[2].y) + (c4 * pCurve[3].y) ;
			
			const double dY = ptHit.y - yt;
			if (dY >= -Tol && dY <= Tol) return TRUE;
		}
	}
	return FALSE;
}

CCurvedWall::CCurvedWall(CPoint pointlist[],int n)
{
	
	m_ptFirstPosition=pointlist[0];
	m_ptControlPosition1=pointlist[1];
	m_ptControlPosition2=pointlist[2];
	m_ptSecondPosition=pointlist[3];
	m_SideAColor=RGB(255,255,200);
	m_SideBColor=RGB(255,255,200);
//	m_SideATexture="not implemented.";
//	m_SideBTexture="not implemented.";
	m_uiHeight=120;
	m_uiWidth=4;

	m_IsTexturizedSideA=FALSE;
	m_IsTexturizedSideB=FALSE;

}

CCurvedWall::CCurvedWall(CCurvedWall &cw)
{
	m_ptFirstPosition = cw.m_ptFirstPosition;
	m_ptControlPosition1=cw.m_ptControlPosition1;
	m_ptControlPosition2=cw.m_ptControlPosition2;
	m_ptSecondPosition=cw.m_ptSecondPosition;
	m_SideAColor=cw.m_SideAColor;
	m_SideBColor=cw.m_SideBColor;
//	m_SideATexture=cw.m_SideATexture;
//	m_SideBTexture=cw.m_SideBTexture;
	m_uiHeight=cw.m_uiHeight;
	m_uiWidth=cw.m_uiWidth;
	m_IsTexturizedSideA=FALSE;
	m_IsTexturizedSideB=FALSE;
}



void CCurvedWall::Serialize(CArchive &ar)
{
	CWall::Serialize(ar);
//	m_SideATexture.Serialize(ar);
//	m_SideBTexture.Serialize(ar);
	
	if(ar.IsStoring())
	{
		ar << m_ptControlPosition1
		   << m_ptControlPosition2 	 
		   << m_ptFirstPosition
		   << m_ptSecondPosition
		   << m_SideAColor
		   << m_SideBColor
		   << m_uiHeight
		   << m_uiWidth
		   << m_IsTexturizedSideA
		   << m_IsTexturizedSideB 
		   << m_SideATexture
		   << m_SideBTexture;
	}
	else
	{
		ar >> m_ptControlPosition1
		   >> m_ptControlPosition2 	 
		   >> m_ptFirstPosition
		   >> m_ptSecondPosition
		   >> m_SideAColor
		   >> m_SideBColor
		   >> m_uiHeight
		   >> m_uiWidth
		   >> m_IsTexturizedSideA
		   >> m_IsTexturizedSideB 
		   >> m_SideATexture
		   >> m_SideBTexture;
	}
}

UINT CCurvedWall::GetType()
{
	return BUILDING_ELEMENT_CURVEDWALL;
}

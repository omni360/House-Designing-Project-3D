// Door.cpp: implementation of the CDoor class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Door.h"
#include "ArchCons.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_SERIAL(CDoor,CFixture,1)
CDoor::CDoor()
{
	m_rectframe = CRect(0,0,5,5);
	m_Color = RGB(100,50,0);
	m_uiType = FIXTURE_DOOR_SINGLE;
}

CDoor::~CDoor()
{

}

CDoor::CDoor(CRect rect)
{
	m_rectframe = rect;
	m_Color = RGB(100,50,0);
	m_uiType = FIXTURE_DOOR_SINGLE;
}

void CDoor::Draw(CDC *pDC, bool bSELECTED)
{
	LOGBRUSH brush;
	CBrush   abrush;
	brush.lbColor = (bSELECTED ? RGB(200,200,200) : m_Color);
	brush.lbStyle = BS_SOLID;
	abrush.CreateBrushIndirect(&brush);
	pDC->FillRect(&m_rectframe,&abrush);
}

void CDoor ::Serialize(CArchive &ar)
{
	CFixture ::Serialize(ar);

		if(ar.IsStoring())
		{
			ar << m_rectframe
               << m_Color
			   << m_ConnectedPoint
			   << m_uiType;
		}
		else
		{
			ar >> m_rectframe
               >> m_Color
			   >> m_ConnectedPoint
			   >> m_uiType;
		}
}

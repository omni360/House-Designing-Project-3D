// Wind.cpp: implementation of the CWindow class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "Arch.h"
#include "Wind.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

IMPLEMENT_SERIAL(CWind,CFixture,1)
CWind::CWind()
{

}

CWind::~CWind()
{

}

void CWind::Serialize(CArchive &ar)
{
	
	CFixture ::Serialize(ar);

		if(ar.IsStoring())
		{
			ar << m_rectframe
               << m_Color
			   << m_uiType
			   << m_ConnectedPoint;
		}
		else
		{
			ar >> m_rectframe
               >> m_Color
			   >> m_uiType
			   >> m_ConnectedPoint;
		}
}

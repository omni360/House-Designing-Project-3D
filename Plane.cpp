// Plane.cpp: implementation of the CPlane class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Plane.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_SERIAL(CPlane,CObject,1)
CPlane::CPlane()
{
	m_Color = RGB(200,200,200);
	m_IsTexturized = FALSE;

}

CPlane::~CPlane()
{

}

void CPlane::Serialize(CArchive &ar)
{
	CObject::Serialize(ar);
	m_BoundaryPoints.Serialize(ar);
	m_TextureFile.Serialize(ar);
		if (ar.IsStoring())
	{
		// TODO: add storing code here
		ar << m_Color
		   <<  m_IsTexturized;
		   //<< m_TextureFile;
	}
	else
	{
		// TODO: add loading code here
		ar >> m_Color
		   >> m_IsTexturized;
		   //>> m_TextureFile;
	}
}

void CPlane::AddBoundary(CPoint m_ptList[], int N)
{
	int i;
	for (i=0;i<N;i++)
		m_BoundaryPoints.Add(m_ptList[i]);
}

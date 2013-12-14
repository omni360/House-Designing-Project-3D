// Building.cpp: implementation of the CBuilding class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "Arch.h"
#include "Building.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_SERIAL(CBuilding,CObject,1)
CBuilding::CBuilding()
{

}

CBuilding::~CBuilding()
{
	int i;
	for (i=0;i<m_Floor.GetSize();i++)
	{
		delete m_Floor[i];
	}
	if (m_Floor.GetSize()>0) m_Floor.RemoveAll();
}



int CBuilding::GetFloorCount()
{
	return m_Floor.GetSize();
}

void CBuilding::AddFloor(CPoint points[],int n)
{
	CFloor *floor= new CFloor(points,n);
	try
	{
		
		m_Floor.Add(floor);
	} catch (CException *ce)
	{
		ce->ReportError();
		ce->Delete();
	}
}

CFloor* CBuilding::GetFloorAt(int nIndex)
{
	CFloor* floor=0;
	floor = static_cast<CFloor*>(m_Floor.GetAt(nIndex));
	return floor;
}

void CBuilding::Serialize(CArchive &ar)
{
	
	CObject::Serialize(ar);
	m_Floor.Serialize(ar);
	if (ar.IsStoring())
	{
		// TODO: add storing code here
		
	
	}
	else
	{
		// TODO: add loading code here
	
	}	
}

void CBuilding::RemoveFloorAll()
{
	int i;
	for (i=0;i<m_Floor.GetSize();i++)
	{
		delete m_Floor[i];
	}
	if (m_Floor.GetSize()>0) m_Floor.RemoveAll();
}

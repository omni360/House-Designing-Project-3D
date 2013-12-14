// Floor.cpp: implementation of the CFloor class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Building.h"
#include "Floor.h"
#include "Plane.h"	// Added by ClassView
#include "Element.h"
#include "FixtureWall.h"
#include "Tableobject.h"


//#include "CoveredPlane.h" 
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_SERIAL(CFloor,CObject,1)
CFloor::CFloor()
{

}

CFloor::~CFloor()
{

}

CFloor::CFloor(CPoint ptList[], int N)
{
	ASSERT(N>0);
//	m_BasePlane.AddBoundary(ptList,N);
//	m_BasePlane.m_Color = RGB(200,235,255);
}

void CFloor::AddCeilling(CPoint ListOfPoints[],int N)
{
	ASSERT(N>0);
	m_CeillingPlane.AddBoundary(ListOfPoints,N);
}



CBuildingElement* CFloor::GetElement(int nIndex)
{
	CBuildingElement* pElement=static_cast<CBuildingElement*>(m_BuildingElement.GetAt(nIndex));
	return pElement;
}

void CFloor::RemoveElement(CBuildingElement *pBE)
{
	int i,position=-1;
	CBuildingElement* pRemoveElement=0;
	for (i=0;i<m_BuildingElement.GetSize();i++)
	{
		pRemoveElement = static_cast<CBuildingElement*>(m_BuildingElement.ElementAt(i));
		if (pRemoveElement==pBE)
		{
			position=i;
		    break;
		}
	}
	if (position>=0)
	{
		m_BuildingElement.RemoveAt(position);
		delete pRemoveElement;
	}
}

int CFloor::GetElementCount()
{
	return m_BuildingElement.GetSize();
}

void CFloor::AddElement(CWall w)
{
	CBuildingElement* pBE= new CWall(w);
	try {
		m_BuildingElement.Add(pBE);
	}
	catch (CException e)
	{
		delete pBE;
		e.Delete();
	}
}

void CFloor::AddElement(CCurvedWall cw)
{
	CBuildingElement* pBE= new CCurvedWall(cw);
	try {
		m_BuildingElement.Add(pBE);
	}
	catch (CException e)
	{
		delete pBE;
		e.Delete();
	}

}

void CFloor::AddElement(CPillar p)
{
	CBuildingElement* pBE= new CPillar(p);
	try {
		m_BuildingElement.Add(pBE);
	}
	catch (CException e)
	{
		delete pBE;
		e.Delete();
	}
}
void CFloor::AddElement(CTableobject ta_o)
{
	CBuildingElement* pBE= new CTableobject(ta_o);
	try {
		m_BuildingElement.Add(pBE);
	}
	catch (CException e)
	{
		delete pBE;
		e.Delete();
	}
}

void CFloor::AddElement(CStairs s)
{
	CBuildingElement* pBE= new CStairs(s);
	try {
		m_BuildingElement.Add(pBE);
	}
	catch (CException e)
	{
		delete pBE;
		e.Delete();
	}
}

void CFloor::Serialize(CArchive &ar)
{
	CObject::Serialize(ar);
	m_BuildingElement.Serialize(ar);
	
}

void CFloor::DrawBase(CDC *pDC)
{
	int N=m_BasePlane.m_BoundaryPoints.GetSize();
	CPoint *temp=new CPoint[N];
	for (int i=0;i<N;i++)
		temp[i]=m_BasePlane.m_BoundaryPoints.GetAt(i);
	CPen *op, p;
	CBrush *ob, b;
	p.CreatePen(PS_SOLID,1,RGB(200,200,200));
	b.CreateSolidBrush(RGB(200,200,200));
	op=pDC->SelectObject(&p);
	ob=pDC->SelectObject(&b);
		pDC->Polygon(temp,N);
	pDC->SelectObject(op);
	pDC->SelectObject(ob);
	delete[] temp;
}

void CFloor::AddElement(CCeiling c)
{
	CBuildingElement* pBE= new CCeiling(c);
	try {
		m_BuildingElement.Add(pBE);
	}
	catch (CException e)
	{
		delete pBE;
		e.Delete();
	}
}
void CFloor::AddElement(CChairObject ch_ob)
{
	CBuildingElement* pBE= new CChairObject(ch_ob);
	try {
		m_BuildingElement.Add(pBE);
	}
	catch (CException e)
	{
		delete pBE;
		e.Delete();
	}
}
void CFloor::AddElement(CFixtureWall fw)
{
	CBuildingElement* pBE= new CFixtureWall(fw);
	try {
		m_BuildingElement.Add(pBE);
	}
	catch (CException e)
	{
		delete pBE;
		e.Delete();
	}
}
void CFloor::AddElement(CSofaobject sf_ob)
{
	CBuildingElement* pBE= new CSofaobject(sf_ob);
	try {
		m_BuildingElement.Add(pBE);
	}
	catch (CException e)
	{
		delete pBE;
		e.Delete();
	}
}
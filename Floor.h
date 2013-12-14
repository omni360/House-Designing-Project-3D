// Floor.h: interface for the CFloor class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FLOOR_H__059AD3FE_012D_4B03_A7D2_18B1723F7F63__INCLUDED_)
#define AFX_FLOOR_H__059AD3FE_012D_4B03_A7D2_18B1723F7F63__INCLUDED_

	// Added by ClassView
#include "Element.h"
#include "Stairs.h"
#include "Wall.h"
#include "pillar.h"
#include "curvedwall.h"
#include "Ceiling.h"
#include "Plane.h"
#include "Spiralstair.h"
#include "ChairObject.h"
#include "FixtureWall.h"
#include "Tableobject.h"
#include "Sofaobject.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CFloor : public CObject
{

	DECLARE_SERIAL(CFloor);
    
public:
	
	CObArray m_BuildingElement;
//	CPlane   m_BasePlane;
//	CPlane   m_CeillingPlane;

	void RemoveElement(CBuildingElement* pBE);
	CBuildingElement* GetElement(int Index);
	int GetElementCount();
	void AddCeilling(CPoint ListOfPoints[], int N);
	CFloor(CPoint m_ptList[], int N);
public:
	void AddElement(CStairs s);
	void AddElement(CPillar p);
	void AddElement(CCurvedWall cw);
	void AddElement(CWall w);
    void AddElement(CFixtureWall fw);
	void AddElement(CSofaobject sf_ob);
	void Serialize(CArchive &ar);
	void DrawBase(CDC* pDC);
	CFloor();
	virtual ~CFloor();
public:

	void AddElement(CChairObject ch_ob);
	void AddElement(CTableobject ta_o);
	void AddElement(CCeiling c);
	void AddElement(CSpiralstair sp);

//	CCoveredPlane m_CeillingPlane;
//	CCoveredPlane m_BasePlane;
	

};

#endif // !defined(AFX_FLOOR_H__059AD3FE_012D_4B03_A7D2_18B1723F7F63__INCLUDED_)

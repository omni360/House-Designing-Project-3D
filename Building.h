// Building.h: interface for the CBuilding class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BUILDING_H__A867E82A_EF85_4472_90EA_547245388F71__INCLUDED_)
#define AFX_BUILDING_H__A867E82A_EF85_4472_90EA_547245388F71__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Floor.h"

class CBuilding : public CObject  
{
	DECLARE_SERIAL(CBuilding)
public:
	CBuilding();
	virtual ~CBuilding();

public:
	void RemoveFloorAll();
	void Serialize(CArchive& ar);
	CFloor* GetFloorAt(int nIndex);
	void AddFloor(CPoint points[], int n);
	int GetFloorCount();
	CObArray m_Floor;

};

#endif // !defined(AFX_BUILDING_H__A867E82A_EF85_4472_90EA_547245388F71__INCLUDED_)

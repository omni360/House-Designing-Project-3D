// Door.h: interface for the CDoor class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DOOR_H__BEDD0179_D7B7_4D6D_8139_32A628166AEB__INCLUDED_)
#define AFX_DOOR_H__BEDD0179_D7B7_4D6D_8139_32A628166AEB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Fixture.h"
#include "ArchCons.h"

class CDoor : public CFixture  
{
	DECLARE_SERIAL(CDoor)
public:
	COLORREF m_Color;
	CRect m_rectframe;
	UINT m_uiType;
	CPoint m_ConnectedPoint;
	CPoint m_bottompoint;
	CDoor();
	CDoor(CRect rect);
	virtual void Draw(CDC* pDC, bool bSELECTED=FALSE);
	virtual void Serialize(CArchive &ar);
	virtual ~CDoor();
};

#endif // !defined(AFX_DOOR_H__BEDD0179_D7B7_4D6D_8139_32A628166AEB__INCLUDED_)

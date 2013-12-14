// FixtureWall.h: interface for the CFixtureWall class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FIXTUREWALL_H__3EC69600_859A_11D9_A1DD_B797C69CCA28__INCLUDED_)
#define AFX_FIXTUREWALL_H__3EC69600_859A_11D9_A1DD_B797C69CCA28__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Element.h"
//#include "Element.h"
#include "Fixture.h"
#include "Door.h"	// Added by ClassView
#include "Wind.h"
class CFixtureWall : public CBuildingElement   
{	DECLARE_SERIAL(CFixtureWall)
public:
	int left,right;
	int calculate2(CFixtureWall fw);
	int value;
	int diff;
	float m_basep;
	CPoint m_ptdoortop,m_ptdoorbottom;
	CPoint pdoor_y;
	CPoint pdoor;
	CString m_SideATexture;
	CString m_SideBTexture;
//	CEnBitmap m_SideBTexture;
//	CEnBitmap m_SideATexture;
	CWind m_window;
	CDoor m_door;
    int loc1;  
	int m_iswindow;
	int m_isdoor;
	virtual UINT GetType();
	void Serialize(CArchive& ar);
	UINT FixtureCount() const;
	void RemoveFixture(CFixture *pFix);
	void AddFixture(CFixture *pFix);
	CObArray m_FixtureList;
	CFixtureWall(CFixtureWall& fw);
	CFixtureWall(CPoint p1, CPoint p2);
	virtual BOOL HitTest(CPoint ptHit);
	virtual void Draw(CDC* pDC, BOOL bSelected=FALSE);
	CPoint   m_ptSecondPosition;
	CPoint   m_ptFirstPosition;
	UINT     m_uiHeight;
	UINT     m_uiWidth;
	BOOL     m_IsTexturizedSideA;
	BOOL     m_IsTexturizedSideB;
	//CEnBitmap  m_SideATexture;
//	CEnBitmap  m_SideBTexture;
	COLORREF m_SideAColor;
	COLORREF m_SideBColor;
	CFixtureWall();
	virtual ~CFixtureWall();
//////////////////////

};

#endif // !defined(AFX_FIXTUREWALL_H__3EC69600_859A_11D9_A1DD_B797C69CCA28__INCLUDED_)

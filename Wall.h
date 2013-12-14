// Wall.h: interface for the CWall class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WALL_H__E5303FAF_A4E9_4D1B_A766_D04D260F52E9__INCLUDED_)
#define AFX_WALL_H__E5303FAF_A4E9_4D1B_A766_D04D260F52E9__INCLUDED_

#include "EnBitmap.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Element.h"
#include "Fixture.h"
#include "Door.h"	// Added by ClassView
#include "Wind.h"	// Added by ClassView
//#include "StraightWallDlg.h"




class CWall : public CBuildingElement  
{
	DECLARE_SERIAL(CWall)
public:
	int left,right;
	int calculate2(CWall w);
	int value;
	int diff;
	float m_basep;
	float m_topp;
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
	CWall(CWall& w);
	CWall(CPoint p1, CPoint p2);
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
	CWall();
	virtual ~CWall();

};

#endif // !defined(AFX_WALL_H__E5303FAF_A4E9_4D1B_A766_D04D260F52E9__INCLUDED_)

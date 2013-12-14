// CurvedWall.h: interface for the CCurvedWall class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CURVEDWALL_H__4E6FC588_7AC5_48D9_8DEB_89DA5F2E5F18__INCLUDED_)
#define AFX_CURVEDWALL_H__4E6FC588_7AC5_48D9_8DEB_89DA5F2E5F18__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Wall.h"

class CCurvedWall : public CWall  
{
	DECLARE_SERIAL(CCurvedWall)
public:
	CCurvedWall();
	virtual ~CCurvedWall();
public:
	virtual UINT GetType();
	virtual void Serialize(CArchive& ar);

	CCurvedWall(CCurvedWall& cw);
	CCurvedWall(CPoint pointlist[],int n=4);
	virtual BOOL HitTest(CPoint ptHit);
	virtual void Draw(CDC* pDC, BOOL bSelected=FALSE);
	CPoint m_ptControlPosition1;
	CPoint m_ptControlPosition2;
};

#endif // !defined(AFX_CURVEDWALL_H__4E6FC588_7AC5_48D9_8DEB_89DA5F2E5F18__INCLUDED_)

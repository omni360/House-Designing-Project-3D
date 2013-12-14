// Stairs.h: interface for the CStairs class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STAIRS_H__3F98BE0E_F9B5_41D1_BB1C_1D7E413D0B20__INCLUDED_)
#define AFX_STAIRS_H__3F98BE0E_F9B5_41D1_BB1C_1D7E413D0B20__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Element.h"

class CStairs : public CBuildingElement  
{
	DECLARE_SERIAL(CStairs)
public:
	
	COLORREF m_StairColor;
	UINT m_uiWidth;
	UINT m_uiHeight;
	CPoint m_ptSecondPosition;
	CPoint m_ptFirstPosition;
	CStairs(CPoint pt1,CPoint pt2);
	CStairs();
	virtual ~CStairs();
public:
	virtual unsigned int GetType();
	virtual void Serialize(CArchive &ar);
	CStairs(CStairs& s);
	virtual BOOL HitTest(CPoint ptHit);
	virtual void Draw(CDC* pDC, BOOL bSelected=FALSE);

};

#endif // !defined(AFX_STAIRS_H__3F98BE0E_F9B5_41D1_BB1C_1D7E413D0B20__INCLUDED_)

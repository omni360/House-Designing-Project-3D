// Ceiling.h: interface for the CCeiling class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CEILING_H__3AEF74C0_3E10_11D8_BA23_86B7EA0E7F5F__INCLUDED_)
#define AFX_CEILING_H__3AEF74C0_3E10_11D8_BA23_86B7EA0E7F5F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Element.h"

class CCeiling : public CBuildingElement  
{
	DECLARE_SERIAL(CCeiling)
public:
	CCeiling(CCeiling& c);
	CCeiling(CPoint p1, CPoint p2);
	void Serialize(CArchive& ar);
	virtual UINT  GetType();
	virtual BOOL HitTest(CPoint ptHit);
	virtual void Draw(CDC* pDC, BOOL bSelected=FALSE);
	CCeiling();
	virtual ~CCeiling();
	CPoint   m_ptSecondPosition;
	CPoint   m_ptFirstPosition;
    
	COLORREF m_SideAColor;
	COLORREF m_SideBColor;
	UINT     m_uiHeight;
	UINT     m_uiWidth;
/////////////////////////////////////


};

#endif // !defined(AFX_CEILING_H__3AEF74C0_3E10_11D8_BA23_86B7EA0E7F5F__INCLUDED_)

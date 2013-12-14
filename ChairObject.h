// ChairObject.h: interface for the CChairObject class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CHAIROBJECT_H__3D41D862_4C36_11D8_BA23_A7571186B25E__INCLUDED_)
#define AFX_CHAIROBJECT_H__3D41D862_4C36_11D8_BA23_A7571186B25E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Element.h"
#include "Sport.h"

class CChairObject :public CBuildingElement
{
		DECLARE_SERIAL(CChairObject)
public:
	void Serialize(CArchive& ar);
	virtual UINT  GetType();
	virtual BOOL HitTest(CPoint ptHit);
	virtual void Draw(CDC* pDC, BOOL bSelected=FALSE);
	CChairObject(CChairObject& ch);
	CChairObject(CPoint);
	CPoint m_ptPosition;
	UINT     m_uiHeight;
	UINT     m_uiWidth;
  
	COLORREF m_Color;
	unsigned int m_uiType;
	CChairObject();
	virtual ~CChairObject();

/////////////////Newly Added 
//  BOOL b_Selection; 

};

#endif // !defined(AFX_CHAIROBJECT_H__3D41D862_4C36_11D8_BA23_A7571186B25E__INCLUDED_)

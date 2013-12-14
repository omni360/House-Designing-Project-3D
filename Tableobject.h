// Tableobject.h: interface for the CTableobject class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TABLEOBJECT_H__20BE2BC1_8606_11D9_A1DD_A846B8DBC128__INCLUDED_)
#define AFX_TABLEOBJECT_H__20BE2BC1_8606_11D9_A1DD_A846B8DBC128__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Element.h"
class CTableobject : public CBuildingElement    
{
//DECLARE_SERIAL(CTableobject)
public:
	void Serialize(CArchive& ar);
	virtual UINT  GetType();
	virtual BOOL HitTest(CPoint ptHit);
	virtual void Draw(CDC* pDC, BOOL bSelected=FALSE);
	CTableobject(CTableobject& ta);
	CTableobject(CPoint);
	CPoint m_ptPosition;
	UINT     m_uiHeight;
	UINT     m_uiWidth;
	COLORREF m_Color;
	unsigned int m_uiType;
	CTableobject();
	virtual ~CTableobject();
/////////////////////////////////New Code

};

#endif // !defined(AFX_TABLEOBJECT_H__20BE2BC1_8606_11D9_A1DD_A846B8DBC128__INCLUDED_)

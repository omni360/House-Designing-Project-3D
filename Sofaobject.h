// Sofaobject.h: interface for the CSofaobject class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SOFAOBJECT_H__5DBCF581_86A9_11D9_A1DD_9DF3117FA528__INCLUDED_)
#define AFX_SOFAOBJECT_H__5DBCF581_86A9_11D9_A1DD_9DF3117FA528__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Build\Element.h"
class CSofaobject : public CBuildingElement    
{
public:
	public:
	void Serialize(CArchive& ar);
	virtual UINT  GetType();
	virtual BOOL HitTest(CPoint ptHit);
	virtual void Draw(CDC* pDC, BOOL bSelected=FALSE);
	CSofaobject(CSofaobject& sf);
	CSofaobject(CPoint);
	CPoint m_ptPosition;
	UINT     m_uiHeight;
	UINT     m_uiWidth;
	unsigned int m_uiType;
	COLORREF m_Color;
	CSofaobject();
	virtual ~CSofaobject();
///////////////////////New Code
    
};

#endif // !defined(AFX_SOFAOBJECT_H__5DBCF581_86A9_11D9_A1DD_9DF3117FA528__INCLUDED_)

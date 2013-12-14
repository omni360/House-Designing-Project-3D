// Wind.h: interface for the CWindow class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WIND_H__D8C11D62_4D93_46DC_9F5F_C2E779DECB46__INCLUDED_)
#define AFX_WIND_H__D8C11D62_4D93_46DC_9F5F_C2E779DECB46__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
//#include "Arch.h"
#include "Fixture.h"

class CWind : public CFixture  
{
	DECLARE_SERIAL(CWind)
public:
	CPoint m_ConnectedPoint;
   
	CPoint m_bottompoint;
	void Serialize(CArchive &ar);
	COLORREF m_Color;
	CRect m_rectframe;
	UINT m_uiType;
	CWind();
	virtual ~CWind();

};

#endif // !defined(AFX_WIND_H__D8C11D62_4D93_46DC_9F5F_C2E779DECB46__INCLUDED_)

// Pillar.h: interface for the CPillar class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PILLAR_H__C1C3A860_B650_4D2C_BE64_EE3E47BF6768__INCLUDED_)
#define AFX_PILLAR_H__C1C3A860_B650_4D2C_BE64_EE3E47BF6768__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Element.h"

class CPillar : public CBuildingElement  
{
	DECLARE_SERIAL(CPillar)
public:
	virtual unsigned int GetType();
	
	virtual void Serialize(CArchive& ar);
	
	CPillar(CPillar& p);
	CPillar(CPoint);
	virtual BOOL HitTest(CPoint ptHit);
	virtual void Draw(CDC *pDC, BOOL bSelected=FALSE);
	unsigned int m_uiType; //0 for cubical and 1 for cylandric
	CPoint m_ptPosition;
	UINT     m_uiHeight;
	UINT     m_uiWidth;
	COLORREF m_Color;
	CPillar();
	virtual ~CPillar();

};

#endif // !defined(AFX_PILLAR_H__C1C3A860_B650_4D2C_BE64_EE3E47BF6768__INCLUDED_)

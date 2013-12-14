// Spiralstair.h: interface for the CSpiralstair class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SPIRALSTAIR_H__39C4B3A1_61EF_11D8_B190_90667EB8045E__INCLUDED_)
#define AFX_SPIRALSTAIR_H__39C4B3A1_61EF_11D8_B190_90667EB8045E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Element.h"
class CSpiralstair : public CBuildingElement   
{
//	DECLARE_SERIAL(CSpiralstair)
public:
	virtual unsigned int GetType();
	
	virtual void Serialize(CArchive& ar);
	
	CSpiralstair(CSpiralstair& sp);
	CSpiralstair(CPoint);
	virtual BOOL HitTest(CPoint ptHit);
	virtual void Draw(CDC *pDC, BOOL bSelected=FALSE);
	unsigned int m_uiType; //0 for cubical and 1 for cylandric
	CPoint m_ptPosition;
	UINT     m_uiHeight;
	UINT     m_uiWidth;
	COLORREF m_Color;
	CSpiralstair();
	virtual ~CSpiralstair();

};

#endif // !defined(AFX_SPIRALSTAIR_H__39C4B3A1_61EF_11D8_B190_90667EB8045E__INCLUDED_)

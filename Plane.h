// Plane.h: interface for the CPlane class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PLANE_H__1B907757_2D1D_4C11_BAB6_C3958D17E670__INCLUDED_)
#define AFX_PLANE_H__1B907757_2D1D_4C11_BAB6_C3958D17E670__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Building.h"

#include <afxtempl.h>



class CPlane : public CObject  
{
	DECLARE_SERIAL(CPlane)
public:
	BOOL     m_IsTexturized;
	COLORREF m_Color;
	CBitmap  m_TextureFile;
	CArray<CPoint,CPoint&> m_BoundaryPoints;
	//CList<CPoint, CPoint&> m_BoundaryPoints;

public:
	void AddBoundary(CPoint m_ptList[], int N);
	void Serialize(CArchive& ar);
	CPlane();
	virtual ~CPlane();

};

#endif // !defined(AFX_PLANE_H__1B907757_2D1D_4C11_BAB6_C3958D17E670__INCLUDED_)

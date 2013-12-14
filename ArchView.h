// ArchView.h : interface of the CArchView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_ARCHVIEW_H__BB7352E2_D1BF_4ED8_994E_375BF4F4F53C__INCLUDED_)
#define AFX_ARCHVIEW_H__BB7352E2_D1BF_4ED8_994E_375BF4F4F53C__INCLUDED_

#include "Wall.h"	// Added by ClassView
#include "CurvedWall.h"	// Added by ClassView
#include "Pillar.h"	// Added by ClassView
#include "Plane.h"
#include <afxtempl.h>
#include "Door.h"	// Added by ClassView
#include "Ceiling.h"	// Added by ClassView
#include "chair_type.h"
#include "vfd.h"
#include "pillardlg.h"	// Added by ClassView
#include "ArchCons.h"	// Added by ClassView
#include "StraightWallDlg.h"	// Added by ClassView
#include "StairDlg.h"	// Added by ClassView
#include "CurvedWallDlg.h"	// Added by ClassView
#include "ArchDoc.h"
#include "EnBitmap.h"	// Added by ClassView
#include "ChairObject.h"
#include "Ceilingdlg.h"
#include "FixtureWall.h"
#include "SimpleWall.h"
#include "Tableobject.h"
#include "SpiralDlg.h"
#include "Tabledlg.h"
#include "Sofadlg.h"
#include "Sofaobject.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CArchView : public CScrollView
{
protected: // create from serialization only
	CArchView();
	DECLARE_DYNCREATE(CArchView)

// Attributes
public:
	CArchDoc*  GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CArchView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	void ConstructSofaObj(UINT nFlags, CPoint point, UINT messagefrom);
	void ShowDialogSofa();
	void ShowDialogTable();
	void ConstructTableObj(UINT nFlags, CPoint point, UINT messagefrom);
	void ShowSimpleWallDialog();
	void ConstructFixtureWall(UINT nFlags, CPoint point, UINT messagefrom);
	void ConstructSpiralstair(UINT nFlags, CPoint point, UINT messagefrom);
	void ShowCeilingDlg();
	void ShowDialogChair();
	void ConstructChairObj(UINT nFlags, CPoint point, UINT messagefrom);
	int cal;
	int diff1;
	
	void ConstructCCeiling(UINT nFlags, CPoint point, UINT messagefrom);
	void ShowSpiralDlg();
	void ShowDialogCuWall();
	void ShowDialogStairs();
	void ShowDialogPillar();
	void ShowDialogStWall();
	CCurvedWallDlg m_cuwalldlg;
	CSpiralDlg m_spiraldlg;
	CStairDlg m_stairdlg;
	CStraightWallDlg m_stwalldlg;
	CPillarDlg m_pillardlg;
	Cchair_type m_chairdlg;
	CCeilingdlg m_ceildlg;
	CSimpleWall m_swalldlg;
	CTabledlg m_tabdlg;
	CSofadlg m_sofadlg;
	ViewFloorDialog m_dlgViewFloor;
	void ConstructCPlane(UINT nFlags, CPoint point, UINT messagefrom);
	void ConstructStairs(UINT nFlags, CPoint point, UINT messagefrom);
	CDoor m_tempDoor;
	void ConstructPillar(UINT nFlags, CPoint point, UINT messagefrom);
	void ConstructCWall(UINT nFlags, CPoint point, UINT messagefrom);
	void ConstructWall(UINT nFlags, CPoint point, UINT messagefrom);
	HCURSOR m_CCursor;
	CBuildingElement* SelecteElement(CPoint point);
	CPillar m_PillarTemp;
	CCurvedWall m_walltempc;
	CWall m_wallTemp;
	CFixtureWall m_fixturewallTemp;
	CChairObject m_chairTemp;
	CArray<CPoint,CPoint&> m_ptList;
	UINT m_ptCounter;
	virtual ~CArchView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CArchView)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnViewFloor();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnViewconstructedfloor();
	afx_msg void OnUpdateConstructedViewfloor(CCmdUI* pCmdUI);
	afx_msg void OnBuildNewfloor();
	afx_msg void OnUpdateNewfloor(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ArchView.cpp
inline CArchDoc* CArchView::GetDocument()
   { return (CArchDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ARCHVIEW_H__BB7352E2_D1BF_4ED8_994E_375BF4F4F53C__INCLUDED_)

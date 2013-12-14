// ArchDoc.h : interface of the CArchDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_ARCHDOC_H__EFE130EB_002F_409D_A6C4_98F3264A8194__INCLUDED_)
#define AFX_ARCHDOC_H__EFE130EB_002F_409D_A6C4_98F3264A8194__INCLUDED_

#include "Building.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Element.h"
#include "Floor.h"
class CArchDoc : public CDocument
{
	DECLARE_SERIAL(CArchDoc)
protected: // create from serialization only


	

// Attributes
public:
	CArchDoc();
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CArchDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual void DeleteContents();
	//}}AFX_VIRTUAL

// Implementation
public:
	CPoint top,bottom;
	int val;
	int calculate1();
	UINT m_AppMode;
	UINT m_AppTool;
	CFloor* m_CurrentFloor;
	CBuilding m_Building;
	int loc2, s_count2,loc1,loc3,loc4; 
//	int m_CurrentFloor;
	CBuildingElement* m_BESelected;
	virtual ~CArchDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CArchDoc)
	afx_msg void OnBuildWall();
	afx_msg void OnUpdateBuildWall(CCmdUI* pCmdUI);
	afx_msg void OnBuildCurvedwall();
	afx_msg void OnUpdateBuildCurvedwall(CCmdUI* pCmdUI);
	afx_msg void OnBuildPillar();
	afx_msg void OnUpdateBuildPillar(CCmdUI* pCmdUI);
	afx_msg void OnBuildStairs();
	afx_msg void OnUpdateBuildStairs(CCmdUI* pCmdUI);
	afx_msg void OnEditRotateelement();
	afx_msg void OnUpdateEditRotateelement(CCmdUI* pCmdUI);
	afx_msg void OnEditResizeelement();
	afx_msg void OnUpdateEditResizeelement(CCmdUI* pCmdUI);
	afx_msg void OnEditDeleteelement();
	afx_msg void OnUpdateEditDeleteelement(CCmdUI* pCmdUI);
	afx_msg void OnEditMoveelement();
	afx_msg void OnUpdateEditMoveelement(CCmdUI* pCmdUI);
	afx_msg void OnEditSelectelement();
	afx_msg void OnUpdateEditSelectelement(CCmdUI* pCmdUI);
	afx_msg void OnBuildFloor();
	afx_msg void OnBuildCeil();
	afx_msg void OnUpdateBuildCeil(CCmdUI* pCmdUI);
	afx_msg void OnObjectChair();
	afx_msg void OnUpdateObjectChair(CCmdUI* pCmdUI);
	afx_msg void OnBbuildSpiralstair();
	afx_msg void OnUpdateBbuildSpiralstair(CCmdUI* pCmdUI);
	afx_msg void OnBuildFixture();
	afx_msg void OnUpdateBuildFixture(CCmdUI* pCmdUI);
	afx_msg void OnObjectTable();
	afx_msg void OnUpdateObjectTable(CCmdUI* pCmdUI);
	afx_msg void OnObjectSofa();
	afx_msg void OnUpdateObjectSofa(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ARCHDOC_H__EFE130EB_002F_409D_A6C4_98F3264A8194__INCLUDED_)

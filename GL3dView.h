#if !defined(AFX_GL3DVIEW_H__4AD7B5C1_86BD_11D6_972E_AEDB600EA44A__INCLUDED_)
#define AFX_GL3DVIEW_H__4AD7B5C1_86BD_11D6_972E_AEDB600EA44A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GL3DView.h : header file
//
#include "gl\gl.h"
#include "gl3d\camera.h"
#include "Wall.h"
#include "Pillar.h"
#include "Plane.h"
#include "Ceiling.h"
#include "CurvedWall.h"
#include "ArchCons.h"
#include "GL3D\Vector3.h"	// Added by ClassView
#include "StraightWallDlg.h"
#include "ArchDoc.h"
#include <vector>
#define kSpeed  0.02 //0.03f

using namespace std;
/////////////////////////////////////////////////////////////////////////////
// GL3DView view

class GL3dView : public CView
{
private:
	HGLRC m_hRC;
	CDC* m_pDC;
	const char * m_ErrorString;
	static const char* const _ErrorStrings[];

public:
	GL3dView();           
	DECLARE_DYNCREATE(GL3dView)

public:
//	void OnKeyDown(int key, int x ,int y);
	virtual BOOL SetupPixelFormat(void);
	virtual BOOL SetupViewport(int cx,int cy);
	virtual BOOL SetupViewingFrustum(GLint aspect_ratio);
	virtual BOOL setupViewingTransform(void);
	virtual BOOL PreRenderScene(void){return TRUE;}
	virtual void RenderStockScene(void);
	virtual BOOL RenderScene(void);
	BOOL InitializeOpenGL();

private:
	void DrawCeiling(CPlane *pPlane);
	void DrawStairs(CStairs *pStair);
	void DrawBlock(CVector3 P1, CVector3 P2, float Width, float Height, COLORREF aColor, COLORREF bColor);
	void DrawPillar(CPillar *pPillar,int i);
	void ChangeGLColor(COLORREF color);
	void DrawWall(CWall *pWall,int i);
	void DrawCurvedWall(CCurvedWall* pCWall);
	void DrawFixtureWall(CFixtureWall* pfWall);
	CVector3 ConvertPoint(long x,long y, long z);
	void DrawGrid(void);
	void Stairs(void);
	void SetError(int e);

	
public:
    int s_count,loc,fw_count,sp_count,cw_count,loc1,loc2,count_loc;
	int s_count1[5000],fw_count1[5000],w_count1[5000];
    int pflag;
	CVector3 CV1[15000],CV2[15000],CV3[15000],CV4[15000],CV5[15000],CV6[15000];
    CVector3 CV7[15000],CV8[15000],CV9[15000],CV10[15000],CV11[15000],CV12[15000];
vector<CVector3> *collosionPoints;	
    float xSpeed;    

	int count_fs,count_element,total_element,fc;
	CPoint C1,C2;
	CCamera g_Camera;
	const float piover180;
	float heading;
	float xpos;
	float zpos;
    float fHeight;
	int i,j;
	boolean Rflag;
	GLfloat	yrot;				// Y Rotation
	GLfloat walkbias;
	GLfloat walkbiasangle;
	GLfloat lookupdown ;
	GLfloat	z;				// Depth Into The Screen
	float zaxis;
	GLuint	filter;		
	GLfloat rotS;
	int chairvalue1,chairvalue2,chairvalue3,chairvalue4,chairvalue5;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(GL3dView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL
	 
// Implementation
public:
	void DrawWidowBlock(CVector3 P1, CVector3 P2, float Width, float Height,float Height1, COLORREF aColor, COLORREF bColor);
	void DrawSpiralStair(CSpiralstair *pstair);
	int collision_detect(int e_count);
	void DrawBlockTex(CVector3 P1, CVector3 P2, float Width, float Height, CString aTexture, CString bTexture);
	void DrawBothBlock(CVector3 P1, CVector3 P2,CVector3 P3, CVector3 P4,CVector3 P5, CVector3 P6, float Width, float Height, COLORREF aColor, COLORREF bColor);
	void DrawBlockWindow(CVector3 P1, CVector3 P2,CVector3 P3, CVector3 P4, float Width, float Height, COLORREF aColor, COLORREF bColor);
	void DrawBlockDoor(CVector3 P1, CVector3 P2,CVector3 P3, CVector3 P4, float Width, float Height, COLORREF aColor, COLORREF bColor);
	void DrawBlock1(CVector3 P1, CVector3 P2, float Width, float Height,float Length, COLORREF aColor, COLORREF bColor);
	void DrawCeiling(CCeiling *pCeil,int i);

//>>>>>>>>>>>>Furniture Drawing functions<<<<<<<<<<<<<
	void DrawChair(CChairObject* pChair,int chair_v);
	void DrawTable(CTableobject* pTable);
	void DrawSofa(CSofaobject* pSofa);
//>>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<<<
	void CSTCube(CVector3 initVec,float xLent,float yLent,float zLent,char texFile[20]);
	void CSTCube(CVector3 initVec,float xLent,float yLent,float zLent);
	virtual ~GL3dView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(GL3dView)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GL3DVIEW_H__4AD7B5C1_86BD_11D6_972E_AEDB600EA44A__INCLUDED_)

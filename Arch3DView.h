// Arch3DView.h: interface for the CArch3DView class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ARCH3DVIEW_H__CDC2A118_20B9_4733_A855_A64806089F5A__INCLUDED_)
#define AFX_ARCH3DVIEW_H__CDC2A118_20B9_4733_A855_A64806089F5A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CArch3DView : public CView  
{
public:
	virtual void OnDraw(CDC *pDC);
	CArch3DView();
	virtual ~CArch3DView();

};

#endif // !defined(AFX_ARCH3DVIEW_H__CDC2A118_20B9_4733_A855_A64806089F5A__INCLUDED_)

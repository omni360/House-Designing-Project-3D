// Element.h: interface for the CBuildingElement class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ELEMENT_H__861DA94F_1F20_43BF_8090_2C0795375539__INCLUDED_)
#define AFX_ELEMENT_H__861DA94F_1F20_43BF_8090_2C0795375539__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CBuildingElement : public CObject 
{
	DECLARE_SERIAL(CBuildingElement)
public:
	virtual unsigned int GetType();
	virtual void Serialize(CArchive& ar);
	virtual BOOL HitTest(CPoint ptHit) ;//=0
	virtual void Draw(CDC *pDC, BOOL bSelected=FALSE);//=0
	CBuildingElement();
	virtual ~CBuildingElement();
	

};

#endif // !defined(AFX_ELEMENT_H__861DA94F_1F20_43BF_8090_2C0795375539__INCLUDED_)

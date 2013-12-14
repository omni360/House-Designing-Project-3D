// Fixture.h: interface for the CFixture class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FIXTURE_H__35137ED1_F8B0_44B4_846C_DA2A57A149C6__INCLUDED_)
#define AFX_FIXTURE_H__35137ED1_F8B0_44B4_846C_DA2A57A149C6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CFixture : public CObject  
{
	DECLARE_SERIAL(CFixture)
public:
	virtual void Serialize(CArchive &ar);
	virtual void Draw(CDC *pDC, boolean bSELECTED=FALSE) ;
	CFixture();
	
	virtual ~CFixture();

};

#endif // !defined(AFX_FIXTURE_H__35137ED1_F8B0_44B4_846C_DA2A57A149C6__INCLUDED_)

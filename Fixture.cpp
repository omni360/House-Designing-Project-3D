// Fixture.cpp: implementation of the CFixture class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Fixture.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_SERIAL(CFixture,CObject,1)
CFixture::CFixture()
{

}

CFixture::~CFixture()
{

}

void CFixture::Draw(CDC *pDC, boolean bSELECTED)
{

}

void CFixture::Serialize(CArchive &ar)
{
	CObject::Serialize(ar);
	if(ar.IsStoring())
	{
		
	}
	else
	{
		
	}
	
}
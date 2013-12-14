// Element.cpp: implementation of the CBuildingElement class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "Arch.h"
#include "Element.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
	IMPLEMENT_SERIAL(CBuildingElement,CObject,1)
CBuildingElement::CBuildingElement()
{

}

CBuildingElement::~CBuildingElement()
{

}

void CBuildingElement::Draw(CDC *pDC, BOOL bSelected)
{

}



void CBuildingElement::Serialize(CArchive &ar)
{
	CObject::Serialize(ar);
	if(ar.IsStoring())
	{
	
	}
	else
	{
		
	}
}

BOOL CBuildingElement::HitTest(CPoint ptHit)
{
 return 0;
}

unsigned int CBuildingElement::GetType()
{
 return 0;
}

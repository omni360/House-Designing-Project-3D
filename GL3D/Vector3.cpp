// Vector3.cpp: implementation of the CVector3 class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Vector3.h"
#include "Math.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CVector3::CVector3()
{

}

CVector3::~CVector3()
{

}

CVector3::CVector3(float X, float Y, float Z)
{
	x=X; y=Y; z=Z;
}

CVector3 CVector3::operator +(CVector3 v)
{
	return CVector3(x+v.x,y+v.y,z+v.z);
}

CVector3 CVector3::operator -(CVector3 v)
{
	return CVector3(x-v.x,y-v.y,z-v.z);
}

CVector3 CVector3::operator *(float num)
{
	return CVector3(x * num, y * num, z * num);
}

CVector3 CVector3::operator /(float num)
{
	return CVector3(x / num, y / num, z / num);
}
/************************************************************************************************/
/************************************************************************************************/
float CVector3::Difference(CVector3 v)
{

	float r;
	r=(float) sqrt((v.x-x)*(v.x-x)+(v.y-y)*(v.y-y)+(v.z-z)*(v.z-z));
	return r;
}

/************************************************************************************************/
//                                      New Code
/************************************************************************************************/
/*void CVector3::operator =(CVector3 eql)
{
	eql.x = this->x;
	eql.y = this->y;
	eql.z = this->z;

}*/
/************************************************************************************************/
/************************************************************************************************/

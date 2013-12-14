// Vector3.h: interface for the CVector3 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VECTOR3_H__6F3D797A_8A7D_41E1_BCCF_E48016DABDDB__INCLUDED_)
#define AFX_VECTOR3_H__6F3D797A_8A7D_41E1_BCCF_E48016DABDDB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


// This is our 2D point class.  This will be used to store the UV coordinates.
class CVector2 
{
public:
	float x, y;
};

class CVector3  
{
public:
	float Difference(CVector3 v);
	CVector3 operator - (CVector3 v);
	CVector3 operator + (CVector3 v);
	CVector3 operator * (float num);
	CVector3 operator / (float num);
//    void operator = (CVector3);

	CVector3 (float X, float Y, float Z);
	float x;
	float y;
	float z;
	CVector3();
	virtual ~CVector3();

};

#endif // !defined(AFX_VECTOR3_H__6F3D797A_8A7D_41E1_BCCF_E48016DABDDB__INCLUDED_)

// Camera.h: interface for the CCamera class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CAMERA_H__0E8A53F1_98C7_4320_A938_B43CBD45A2AE__INCLUDED_)
#define AFX_CAMERA_H__0E8A53F1_98C7_4320_A938_B43CBD45A2AE__INCLUDED_

#include "Vector3.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CCamera  
{
public:
	void MoveCamera(long double speed);
	void RotateAroundPoint(CVector3 vCenter, float angle, float x, float y, float z);
	void RotateView(float angle, float X, float Y, float Z);
	void PositionCamera(float positionX, float positionY, float positionZ,float viewX,     float viewY,     float viewZ,float upVectorX, float upVectorY, float upVectorZ);
	CVector3 m_vPosition,m_vPosition_pre;
	CVector3 m_vView,m_vView_pre;
	CVector3 m_vUpVector;
	CCamera();
	virtual ~CCamera();

};

#endif // !defined(AFX_CAMERA_H__0E8A53F1_98C7_4320_A938_B43CBD45A2AE__INCLUDED_)

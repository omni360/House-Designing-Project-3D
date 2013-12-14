// Camera.cpp: implementation of the CCamera class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Camera.h"
#include <math.h>


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCamera::CCamera()
{

}

CCamera::~CCamera()
{

}

void CCamera::PositionCamera(float positionX, float positionY, float positionZ, float viewX, float viewY, float viewZ, float upVectorX, float upVectorY, float upVectorZ)
{
	CVector3 vPosition	= CVector3(positionX, positionY, positionZ);
	CVector3 vView		= CVector3(viewX, viewY, viewZ);
	CVector3 vUpVector	= CVector3(upVectorX, upVectorY, upVectorZ);

	// The code above just makes it cleaner to set the variables.
	// Otherwise we would have to set each variable x y and z.

	m_vPosition = vPosition;					// Assign the position
	m_vView     = vView;						// Assign the view
	m_vUpVector = vUpVector;					// Assign the up vector
}

void CCamera::RotateView(float angle, float X, float Y, float Z)
{
	CVector3 vNewView;

	// Get the view vector (The direction we are facing)
	CVector3 vView = m_vView - m_vPosition;		

	// Calculate the sine and cosine of the angle once
	float cosTheta = (float)cos(angle);
	float sinTheta = (float)sin(angle);

	// Find the new x position for the new rotated point
	vNewView.x  = (cosTheta + (1 - cosTheta) * X * X)		* vView.x;
	vNewView.x += ((1 - cosTheta) * X * Y - Z * sinTheta)	* vView.y;
	vNewView.x += ((1 - cosTheta) * X * Z + Y * sinTheta)	* vView.z;

	// Find the new y position for the new rotated point
	vNewView.y  = ((1 - cosTheta) * X * Y + Z * sinTheta)	* vView.x;
	vNewView.y += (cosTheta + (1 - cosTheta) * Y * Y)		* vView.y;
	vNewView.y += ((1 - cosTheta) * Y * Z - X * sinTheta)	* vView.z;

	// Find the new z position for the new rotated point
	vNewView.z  = ((1 - cosTheta) * X * Z - Y * sinTheta)	* vView.x;
	vNewView.z += ((1 - cosTheta) * Y * Z + X * sinTheta)	* vView.y;
	vNewView.z += (cosTheta + (1 - cosTheta) * Z * Z)		* vView.z;

	// Now we just add the newly rotated vector to our position to set
	// our new rotated view of our camera.
	m_vView = m_vPosition + vNewView;
}

void CCamera::RotateAroundPoint(CVector3 vCenter, float angle, float x, float y, float z)
{
	CVector3 vNewPosition;			

	// To rotate our position around a point, what we need to do is find
	// a vector from our position to the center point we will be rotating around.
	// Once we get this vector, then we rotate it along the specified axis with
	// the specified degree.  Finally the new vector is added center point that we
	// rotated around (vCenter) to become our new position.  That's all it takes.

	// Get the vVector from our position to the center we are rotating around
	CVector3 vPos = m_vPosition - vCenter;

	// Calculate the sine and cosine of the angle once
	float cosTheta = (float)cos(angle);
	float sinTheta = (float)sin(angle);

	// Find the new x position for the new rotated point
	vNewPosition.x  = (cosTheta + (1 - cosTheta) * x * x)		* vPos.x;
	vNewPosition.x += ((1 - cosTheta) * x * y - z * sinTheta)	* vPos.y;
	vNewPosition.x += ((1 - cosTheta) * x * z + y * sinTheta)	* vPos.z;

	// Find the new y position for the new rotated point
	vNewPosition.y  = ((1 - cosTheta) * x * y + z * sinTheta)	* vPos.x;
	vNewPosition.y += (cosTheta + (1 - cosTheta) * y * y)		* vPos.y;
	vNewPosition.y += ((1 - cosTheta) * y * z - x * sinTheta)	* vPos.z;

	// Find the new z position for the new rotated point
	vNewPosition.z  = ((1 - cosTheta) * x * z - y * sinTheta)	* vPos.x;
	vNewPosition.z += ((1 - cosTheta) * y * z + x * sinTheta)	* vPos.y;
	vNewPosition.z += (cosTheta + (1 - cosTheta) * z * z)		* vPos.z;

	// Now we just add the newly rotated vector to our position to set
	// our new rotated position of our camera.
	m_vPosition = vCenter + vNewPosition;
}

void CCamera::MoveCamera(long double speed)
{

	if(speed==0)
	{ m_vPosition.x =m_vPosition_pre.x ;	// Add our acceleration to our position's X
	  m_vPosition.z =m_vPosition_pre.z ;		// Add our acceleration to our position's Z
	  m_vView.x =m_vView_pre.x ;			// Add our acceleration to our view's X
	  m_vView.z =m_vView_pre.z ;			// Add our acceleration to our view's Z
	}	
else
{
	CVector3 vVector = m_vView - m_vPosition;
	//CVector3 vVector = m_vPosition;
	
	m_vPosition.x += vVector.x * speed;		// Add our acceleration to our position's X
	m_vPosition.z += vVector.z * speed;		// Add our acceleration to our position's Z
	m_vView.x += vVector.x * speed;			// Add our acceleration to our view's X
	m_vView.z += vVector.z * speed;			// Add our acceleration to our view's Z
    
	m_vPosition_pre.x=m_vPosition.x  ;	// Add our acceleration to our position's X
	m_vPosition_pre.z=m_vPosition.z ;		// Add our acceleration to our position's Z
	m_vView_pre.x= m_vView.x ;			// Add our acceleration to our view's X
    m_vView_pre.z=	m_vView.z ;			// Add our acceleration to our view's Z
	
}	
}

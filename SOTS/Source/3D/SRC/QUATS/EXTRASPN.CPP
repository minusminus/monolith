// MAGIC Software
// http://www.cs.unc.edu/~eberly
//
// This free software is supplied under the following terms:
// 1. You may distribute the original source code to others at no charge.
// 2. You may modify the original source code and distribute it to others at
//    no charge.  The modified code must be documented to indicate that it is
//    not part of the original package.
// 3. You may use this code for non-commercial purposes.  You may also
//    incorporate this code into commercial packages.  However, you may not
//    sell any of your source code which contains my original and/or modified
//    source code (see items 1 and 2).	In such a case, you would need to
//    factor out my code and freely distribute it.
// 4. The original code comes with absolutely no warranty and no guarantee is
//    made that the code is bug-free.

#include <math.h>
#include "extraspn.h"

static double g_dTwoPi = 8.0*atan(1.0);

//---------------------------------------------------------------------------
RotationKey::RotationKey () :
    m_kAxis(0.0,0.0,0.0),
    m_kQuat(0.0,0.0,0.0,0.0)
{
    m_dAngle = 0.0;
    m_iExtraSpins = 0;
    m_eInfo = NONE;
}
//---------------------------------------------------------------------------
void RotationKey::PreprocessKeys (int iNumKeys, RotationKey* aKey)
{
    // Determine interpolation type, compute extra spins, and adjust
    // angles accordingly.
    int i;
    for (i = 0; i < iNumKeys-1; i++)
    {
	RotationKey& rkKey0 = aKey[i];
	RotationKey& rkKey1 = aKey[i+1];
	double dDiff = rkKey1.m_dAngle - rkKey0.m_dAngle;
	if ( fabs(dDiff) < g_dTwoPi )
	{
	    rkKey0.m_iExtraSpins = 0;
	    rkKey0.m_eInfo = NONE;
	}
	else
	{
	    rkKey0.m_iExtraSpins = int(dDiff/g_dTwoPi);

	    if ( rkKey0.m_kAxis == rkKey1.m_kAxis )
		rkKey0.m_eInfo = SAME_AXIS;
	    else if ( rkKey0.m_dAngle != 0.0 )
		rkKey0.m_eInfo = DIFF_AXIS_NO_ZERO;
	    else
		rkKey0.m_eInfo = DIFF_AXIS_ZERO;
	}
    }

    // Eliminate any non-acute angles between successive quaternions.  This
    // is done to prevent potential discontinuities that are the result of
    // invalid intermediate value quaternions.
    for (i = 0; i < iNumKeys-1; i++)
    {
	RotationKey& rkKey0 = aKey[i];
	RotationKey& rkKey1 = aKey[i+1];
	if ( rkKey0.m_kQuat.Dot(rkKey1.m_kQuat) < 0.0 )
	    rkKey1.m_kQuat = -rkKey1.m_kQuat;
    }

    // Clamp identity quaternions so that |w| <= 1 (avoids problems with
    // call to acos in SlerpExtraSpins).
    for (i = 0; i < iNumKeys; i++)
    {
	RotationKey& rkKey = aKey[i];
	if ( rkKey.m_kQuat.w < -1.0 )
	    rkKey.m_kQuat.w = -1.0;
	else if ( rkKey.m_kQuat.w > 1.0 )
	    rkKey.m_kQuat.w = 1.0;
    }
}
//---------------------------------------------------------------------------
void RotationKey::Interpolate (double dTime, const RotationKey& rkNextKey,
    RotationKey& rkInterpKey)
{
    // assert:	0 <= dTime <= 1

    switch ( m_eInfo )
    {
	case NONE:
	{
	    rkInterpKey.m_kQuat = Quaternion::Slerp(dTime,m_kQuat,
		rkNextKey.m_kQuat);
	    break;
	}
	case SAME_AXIS:
	{
	    rkInterpKey.m_dAngle = (1.0-dTime)*m_dAngle +
		dTime*rkNextKey.m_dAngle;
	    rkInterpKey.m_kAxis = m_kAxis;
	    rkInterpKey.m_kQuat.FromAngleAxis(rkInterpKey.m_dAngle,
		rkInterpKey.m_kAxis);
	    break;
	}
	case DIFF_AXIS_NO_ZERO:
	{
	    rkInterpKey.m_kQuat = Quaternion::SlerpExtraSpins(dTime,
		m_kQuat,rkNextKey.m_kQuat,m_iExtraSpins);
	    break;
	}
	case DIFF_AXIS_ZERO:
	{
	    rkInterpKey.m_dAngle = (1.0-dTime)*m_dAngle +
		dTime*rkNextKey.m_dAngle;
	    InterpolateAxis(dTime,m_kAxis,rkNextKey.m_kAxis,
		rkInterpKey.m_kAxis);
	    rkInterpKey.m_kQuat.FromAngleAxis(rkInterpKey.m_dAngle,
		rkInterpKey.m_kAxis);
	    break;
	}
    }
}
//---------------------------------------------------------------------------
void RotationKey::InterpolateAxis (double dTime, const Point3& rkAxis0,
    const Point3& rkAxis1, Point3& rkInterpAxis)
{
    // assert:	rkAxis0 and rkAxis1 are unit length
    // assert:	rkAxis0.Dot(rkAxis1) >= 0
    // assert:	0 <= dTime <= 1

    double dCos = rkAxis0.Dot(rkAxis1);  // >= 0 by assertion
    if ( dCos > 1.0f ) // round-off error might create problems in acos call
	dCos = 1.0f;

    double dAngle = acos(dCos);
    double dInvSin = 1.0/sin(dAngle);
    double dTimeAngle = dTime*dAngle;
    double dCoeff0 = sin(dAngle - dTimeAngle)*dInvSin;
    double dCoeff1 = sin(dTimeAngle)*dInvSin;

    rkInterpAxis = dCoeff0*rkAxis0 + dCoeff1*rkAxis1;
}
//---------------------------------------------------------------------------

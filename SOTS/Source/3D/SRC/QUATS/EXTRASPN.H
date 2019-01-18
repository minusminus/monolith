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
//    source code (see items 1 and 2).  In such a case, you would need to
//    factor out my code and freely distribute it.
// 4. The original code comes with absolutely no warranty and no guarantee is
//    made that the code is bug-free.

#ifndef EXTRASPN_H
#define EXTRASPN_H

#include "quat.h"

class RotationKey
{
public:
    RotationKey ();
    ~RotationKey () { /**/ }

    // attributes
    void SetAngle (double dAngle) { m_dAngle = dAngle; }
    double GetAngle () const { return m_dAngle; }
    void SetAxis (const Point3& rkAxis) { m_kAxis = rkAxis; }
    const Point3& GetAxis () const { return m_kAxis; }
    void SetQuaternion (const Quaternion& rkQuat) { m_kQuat = rkQuat; }
    const Quaternion& GetQuaternion () const { return m_kQuat; }
    void SetExtraSpins (int iExtraSpins) { m_iExtraSpins = iExtraSpins; }
    int GetExtraSpins () const { return m_iExtraSpins; }

    // Preprocess sequence of rotation keys.  This call determines if extra
    // spins are required and what type of interpolation should occur between
    // consecutive pairs of keys.  This must be called before interpolation
    // of pairs of keys in the sequence.
    static void PreprocessKeys (int iNumKeys, RotationKey* aKey);

    // linear-style interpolation of two rotation keys
    void Interpolate (double dTime, const RotationKey& rkNextKey,
        RotationKey& rkInterpKey);

protected:
    double m_dAngle;
    Point3 m_kAxis;
    Quaternion m_kQuat;

    typedef enum
    {
        NONE,               // no extra spins
        SAME_AXIS,          // extra spins, same axis of rotation
        DIFF_AXIS_NO_ZERO,  // extra spins, different axes, no zero angles
        DIFF_AXIS_ZERO,     // extra spins, different axes, zero angles
    }
    ExtraSpinInfo;
    int m_iExtraSpins;
    ExtraSpinInfo m_eInfo;

    static void InterpolateAxis (double dTime, const Point3& rkAxis0,
        const Point3& rkAxis1, Point3& rkInterpAxis);
};

#endif



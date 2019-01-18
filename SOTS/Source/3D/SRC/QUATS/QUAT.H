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

#ifndef QUAT_H
#define QUAT_H

class Point3
{
public:
    // point or vector in 3-space
    double x, y, z;

    Point3 () { /* uninitialized*/ }

    Point3 (double _x, double _y, double _z)
    {
        x = _x;
        y = _y;
        z = _z;
    }

    Point3 (const Point3& rkPoint)
    {
        x = rkPoint.x;
        y = rkPoint.y;
        z = rkPoint.z;
    }

    Point3& operator= (const Point3& rkPoint)
    {
        x = rkPoint.x;
        y = rkPoint.y;
        z = rkPoint.z;
        return *this;
    }

    bool operator== (const Point3& rkPoint)
    {
        return (x == rkPoint.x && y == rkPoint.y && z == rkPoint.z);
    }

    bool operator!= (const Point3& rkPoint)
    {
        return (x != rkPoint.x || y != rkPoint.y || z != rkPoint.z);
    }

    Point3 operator+ (const Point3& rkPoint)
    {
        return Point3(x+rkPoint.x,y+rkPoint.y,z+rkPoint.z);
    }

    Point3 operator- (const Point3& rkPoint)
    {
        return Point3(x-rkPoint.x,y-rkPoint.y,z-rkPoint.z);
    }

    Point3 operator* (double dCoeff)
    {
        return Point3(dCoeff*x,dCoeff*y,dCoeff*z);
    }

    friend Point3 operator* (double dCoeff, const Point3& rkPoint)
    {
        return Point3(dCoeff*rkPoint.x,dCoeff*rkPoint.y,dCoeff*rkPoint.z);
    }

    double Dot (const Point3& rkPoint) const
    {
        return x*rkPoint.x + y*rkPoint.y + z*rkPoint.z;
    }

    Point3 Cross (const Point3& rkPoint)
    {
        return Point3
        (
            y*rkPoint.z - z*rkPoint.y,
            z*rkPoint.x - x*rkPoint.z,
            x*rkPoint.y - y*rkPoint.x
        );
    }

    double Length () { return sqrt(x*x+y*y+z*z); }
};


class Quaternion
{
public:
    double w, x, y, z;

    // construction and destruction
    Quaternion () {}
    Quaternion (double _w, double _x, double _y, double _z);
    Quaternion (const Quaternion& q);

    // conversion between quaternions, matrices, and angle-axes
    void FromRotationMatrix (const double R[3][3]);
    void ToRotationMatrix (double R[3][3]) const;
    void FromAngleAxis (const double& angle, const double& ax,
        const double& ay, const double& az);
    void FromAngleAxis (const double& rdAngle, const Point3& rkPoint);
    void ToAngleAxis (double& angle, double& ax, double& ay, double& az) const;
    void ToAngleAxis (double& rkAngle, Point3& rkPoint) const;

    // arithmetic operations
    Quaternion& operator= (const Quaternion& q);
    Quaternion operator+ (const Quaternion& q) const;
    Quaternion operator- (const Quaternion& q) const;
    Quaternion operator* (const Quaternion& q) const;
    Quaternion operator* (double c) const;
    friend Quaternion operator* (double c, const Quaternion& q);
    Quaternion operator- () const;

    // functions of a quaternion
    double Dot (const Quaternion& q) const;  // dot product of quaternions
    double Norm () const;  // squared-length of quaternion
    Quaternion Inverse () const;  // apply to non-zero quaternion
    Quaternion UnitInverse () const;  // apply to unit-length quaternion
    Quaternion Exp () const;
    Quaternion Log () const;

    // rotation of a point by a quaternion
    Point3 operator* (const Point3& pt) const;

    // spherical linear interpolation
    static Quaternion Slerp (double t, const Quaternion& p,
        const Quaternion& q);

    static Quaternion SlerpExtraSpins (double t, const Quaternion& p,
        const Quaternion& q, int iExtraSpins);

    // setup for spherical quadratic interpolation
    static void Intermediate (const Quaternion& q0, const Quaternion& q1,
        const Quaternion& q2, Quaternion& a, Quaternion& b);

    // spherical quadratic interpolation
    static Quaternion Squad (double t, const Quaternion& p,
        const Quaternion& a, const Quaternion& b, const Quaternion& q);

    static Quaternion ZERO;
    static Quaternion IDENTITY;
};

#endif


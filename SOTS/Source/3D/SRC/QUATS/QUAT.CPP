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

#include <math.h>
#include "quat.h"

static double g_dEpsilon = 1e-03;  // cutoff for sin(angle) near zero
static double g_dPi = 4.0*atan(1.0);

Quaternion Quaternion::ZERO(0,0,0,0);
Quaternion Quaternion::IDENTITY(1,0,0,0);

//---------------------------------------------------------------------------
Quaternion::Quaternion (double _w, double _x, double _y, double _z)
{
    w = _w;
    x = _x;
    y = _y;
    z = _z;
}
//---------------------------------------------------------------------------
Quaternion::Quaternion (const Quaternion& q)
{
    w = q.w;
    x = q.x;
    y = q.y;
    z = q.z;
}
//---------------------------------------------------------------------------
void Quaternion::FromRotationMatrix (const double R[3][3])
{
    // Algorithm in Ken Shoemake's article in 1987 SIGGRAPH course notes
    // article "Quaternion Calculus and Fast Animation".

    double trace = R[0][0]+R[1][1]+R[2][2];
    double root;

    if ( trace > 0.0 )
    {
        // |w| > 1/2, may as well choose w > 1/2
        root = sqrt(trace+1.0);  // 2w
        w = 0.5*root;
        root = 0.5/root;  // 1/(4w)
        x = (R[2][1]-R[1][2])*root;
        y = (R[0][2]-R[2][0])*root;
        z = (R[1][0]-R[0][1])*root;
    }
    else
    {
        // |w| <= 1/2
        static int next[3] = { 1, 2, 0 };
        int i = 0;
        if ( R[1][1] > R[0][0] )
            i = 1;
        if ( R[2][2] > R[i][i] )
            i = 2;
        int j = next[i];
        int k = next[j];

        root = sqrt(R[i][i]-R[j][j]-R[k][k]+1.0);
        double* quat[3] = { &x, &y, &z };
        *quat[i] = 0.5*root;
        root = 0.5/root;
        w = (R[k][j]-R[j][k])*root;
        *quat[j] = (R[j][i]+R[i][j])*root;
        *quat[k] = (R[k][i]+R[i][k])*root;
    }
}
//---------------------------------------------------------------------------
void Quaternion::ToRotationMatrix (double R[3][3]) const
{
    double tx  = 2.0*x;
    double ty  = 2.0*y;
    double tz  = 2.0*z;
    double twx = tx*w;
    double twy = ty*w;
    double twz = tz*w;
    double txx = tx*x;
    double txy = ty*x;
    double txz = tz*x;
    double tyy = ty*y;
    double tyz = tz*y;
    double tzz = tz*z;

    R[0][0] = 1.0-(tyy+tzz);
    R[0][1] = txy-twz;
    R[0][2] = txz+twy;
    R[1][0] = txy+twz;
    R[1][1] = 1.0-(txx+tzz);
    R[1][2] = tyz-twx;
    R[2][0] = txz-twy;
    R[2][1] = tyz+twx;
    R[2][2] = 1.0-(txx+tyy);
}
//---------------------------------------------------------------------------
void Quaternion::FromAngleAxis (const double& angle, const double& ax,
                                const double& ay, const double& az)
{
    // assert:  axis[] is unit length
    //
	// The quaternion representing the rotation is
	//   q = cos(A/2)+sin(A/2)*(x*i+y*j+z*k)

    double halfAngle = 0.5*angle;
    double sn = sin(halfAngle);
    w = cos(halfAngle);
    x = sn*ax;
    y = sn*ay;
    z = sn*az;
}
//---------------------------------------------------------------------------
void Quaternion::FromAngleAxis (const double& rdAngle, const Point3& rkPoint)
{
    FromAngleAxis(rdAngle,rkPoint.x,rkPoint.y,rkPoint.z);
}
//---------------------------------------------------------------------------
void Quaternion::ToAngleAxis (double& angle, double& ax, double& ay,
                              double& az) const
{
	// The quaternion representing the rotation is
	//   q = cos(A/2)+sin(A/2)*(x*i+y*j+z*k)

    double length2 = x*x+y*y+z*z;
    if ( length2 > 0.0 )
    {
        angle = 2.0*acos(w);
        double invlen = 1.0/sqrt(length2);
        ax = x*invlen;
        ay = y*invlen;
        az = z*invlen;
    }
    else
    {
        // angle is 0 (mod 2*pi), so any axis will do
        angle = 0;
        ax = 1.0;
        ay = 0.0;
        az = 0.0;
    }
}
//---------------------------------------------------------------------------
void Quaternion::ToAngleAxis (double& rdAngle, Point3& rkPoint) const
{
    ToAngleAxis(rdAngle,rkPoint.x,rkPoint.y,rkPoint.z);
}
//---------------------------------------------------------------------------
Quaternion& Quaternion::operator= (const Quaternion& q)
{
    w = q.w;
    x = q.x;
    y = q.y;
    z = q.z;

    return *this;
}
//---------------------------------------------------------------------------
Quaternion Quaternion::operator+ (const Quaternion& q) const
{
    return Quaternion(w+q.w,x+q.x,y+q.y,z+q.z);
}
//---------------------------------------------------------------------------
Quaternion Quaternion::operator- (const Quaternion& q) const
{
    return Quaternion(w-q.w,x-q.x,y-q.y,z-q.z);
}
//---------------------------------------------------------------------------
Quaternion Quaternion::operator* (const Quaternion& q) const
{
    // NOTE:  Multiplication is not generally commutative, so in most
    // cases p*q != q*p.

#if 1
    return Quaternion
    (
		w*q.w-x*q.x-y*q.y-z*q.z,
		w*q.x+x*q.w+y*q.z-z*q.y,
		w*q.y+y*q.w+z*q.x-x*q.z,
		w*q.z+z*q.w+x*q.y-y*q.x
    );
#else
    // The above code uses 16 multiplications and 12 additions.  The code
    // below uses 12 multiplications (you might be able to avoid the
    // divisions by 2 and manipulate the floating point exponent directly)
    // and 28 additions.  For an architecture where multiplications are more
    // expensive than additions, you should do the cycle count and consider
    // using the code below.  On an Intel Pentium, multiplications and
    // additions cost the same, so the code below is slower than the code
    // above.

    double A = (w+x)*(q.w+q.x);
    double B = (z-y)*(q.y-q.z);
    double C = (x-w)*(q.y+q.z);
    double D = (y+z)*(q.x-q.w);
    double E = (x+z)*(q.x+q.y);
    double F = (x-z)*(q.x-q.y);
    double G = (w+y)*(q.w-q.z);
    double H = (w-y)*(q.w+q.z);

    double EpF = E+F, EmF = E-F;
    double GpH = G+H, GmH = G-H;

    return Quaternion
    (
         B+0.5*(GpH-EpF),
         A-0.5*(GpH+EpF),
        -C+0.5*(EmF+GmH),
        -D+0.5*(EmF-GmH)
    );
#endif
}
//---------------------------------------------------------------------------
Quaternion Quaternion::operator* (double c) const
{
    return Quaternion(c*w,c*x,c*y,c*z);
}
//---------------------------------------------------------------------------
Quaternion operator* (double c, const Quaternion& q)
{
    return Quaternion(c*q.w,c*q.x,c*q.y,c*q.z);
}
//---------------------------------------------------------------------------
Quaternion Quaternion::operator- () const
{
    return Quaternion(-w,-x,-y,-z);
}
//---------------------------------------------------------------------------
double Quaternion::Dot (const Quaternion& q) const
{
    return w*q.w+x*q.x+y*q.y+z*q.z;
}
//---------------------------------------------------------------------------
double Quaternion::Norm () const
{
    return w*w+x*x+y*y+z*z;
}
//---------------------------------------------------------------------------
Quaternion Quaternion::Inverse () const
{
    double norm = w*w+x*x+y*y+z*z;
    if ( norm > 0.0 )
    {
        norm = 1.0/norm;
        return Quaternion(w*norm,-x*norm,-y*norm,-z*norm);
    }
    else
    {
        // return an invalid result to flag the error
        return ZERO;
    }
}
//---------------------------------------------------------------------------
Quaternion Quaternion::UnitInverse () const
{
    // assert:  'this' is unit length
    return Quaternion(w,-x,-y,-z);
}
//---------------------------------------------------------------------------
Quaternion Quaternion::Exp () const
{
    // If q = A*(x*i+y*j+z*k) where (x,y,z) is unit length, then
    // exp(q) = cos(A)+sin(A)*(x*i+y*j+z*k).  If sin(A) is near zero,
    // use exp(q) = cos(A)+A*(x*i+y*j+z*k) since A/sin(A) has limit 1.

    double angle = sqrt(x*x+y*y+z*z);
    double sn = sin(angle);

    Quaternion result;
    result.w = cos(angle);

    if ( fabs(sn) >= g_dEpsilon )
    {
        double coeff = sn/angle;
        result.x = coeff*x;
        result.y = coeff*y;
        result.z = coeff*z;
    }
    else
    {
        result.x = x;
        result.y = y;
        result.z = z;
    }

    return result;
}
//---------------------------------------------------------------------------
Quaternion Quaternion::Log () const
{
    // If q = cos(A)+sin(A)*(x*i+y*j+z*k) where (x,y,z) is unit length, then
    // log(q) = A*(x*i+y*j+z*k).  If sin(A) is near zero, use log(q) =
    // sin(A)*(x*i+y*j+z*k) since sin(A)/A has limit 1.

    Quaternion result;
    result.w = 0.0;

    if ( fabs(w) < 1.0 )
    {
        double angle = acos(w);
        double sn = sin(angle);
        if ( fabs(sn) >= g_dEpsilon )
        {
            double coeff = angle/sn;
            result.x = coeff*x;
            result.y = coeff*y;
            result.z = coeff*z;
            return result;
        }
    }

    result.x = x;
    result.y = y;
    result.z = z;

    return result;
}
//---------------------------------------------------------------------------
Point3 Quaternion::operator* (const Point3& pt) const
{
    // Given a vector u = (x0,y0,z0) and a unit length quaternion
    // q = <w,x,y,z>, the vector v = (x1,y1,z1) which represents the
    // rotation of u by q is v = q*u*q^{-1} where * indicates quaternion
    // multiplication and where u is treated as the quaternion <0,x0,y0,z0>.
    // Note that q^{-1} = <w,-x,-y,-z>, so no real work is required to
    // invert q.  Now
    //
    //   q*u*q^{-1} = q*<0,x0,y0,z0>*q^{-1}
    //     = q*(x0*i+y0*j+z0*k)*q^{-1}
    //     = x0*(q*i*q^{-1})+y0*(q*j*q^{-1})+z0*(q*k*q^{-1})
    //
    // As 3-vectors, q*i*q^{-1}, q*j*q^{-1}, and 2*k*q^{-1} are the columns
    // of the rotation matrix computed in Quaternion::ToRotationMatrix.  The
    // vector v is obtained as the product of that rotation matrix with
    // vector u.  As such, the quaternion representation of a rotation
    // matrix requires less space than the matrix and more time to compute
    // the rotated vector.  Typical space-time tradeoff...

    double R[3][3];
    ToRotationMatrix(R);

    Point3 result;
    result.x = R[0][0]*pt.x+R[0][1]*pt.y+R[0][2]*pt.z;
    result.y = R[1][0]*pt.x+R[1][1]*pt.y+R[1][2]*pt.z;
    result.z = R[2][0]*pt.x+R[2][1]*pt.y+R[2][2]*pt.z;

    return result;
}
//---------------------------------------------------------------------------
Quaternion Quaternion::Slerp (double t, const Quaternion& p,
    const Quaternion& q)
{
    // assert:  p.Dot(q) >= 0 (guaranteed in NiRotKey::Interpolate methods)
    double dCos = p.Dot(q);

    // numerical round-off error could create problems in call to acos
    if ( dCos < -1.0 )
        dCos = -1.0;
    else if ( dCos > 1.0 )
        dCos = 1.0;

    double dAngle = acos(dCos);
    double dSin = sin(dAngle);  // fSin >= 0 since fCos >= 0

    if ( dSin < g_dEpsilon )
    {
        return p;
    }
    else
    {
        double dInvSin = 1.0/dSin;
        double dCoeff0 = sin((1.0-t)*dAngle)*dInvSin;
        double dCoeff1 = sin(t*dAngle)*dInvSin;
        return dCoeff0*p + dCoeff1*q;
    }
}
//---------------------------------------------------------------------------
Quaternion Quaternion::SlerpExtraSpins (double t, const Quaternion& p,
    const Quaternion& q, int iExtraSpins)
{
    // assert:  p.Dot(q) >= 0 (guaranteed in RotationKey::Preprocess)
    double dCos = p.Dot(q);

    // numerical round-off error could create problems in call to acos
    if ( dCos < -1.0 )
        dCos = -1.0;
    else if ( dCos > 1.0 )
        dCos = 1.0;

    double dAngle = acos(dCos);
    double dSin = sin(dAngle);  // fSin >= 0 since fCos >= 0

    if ( dSin < g_dEpsilon )
    {
        return p;
    }
    else
    {
        double dPhase = g_dPi*iExtraSpins*t;
        double dInvSin = 1.0/dSin;
        double dCoeff0 = sin((1.0-t)*dAngle - dPhase)*dInvSin;
        double dCoeff1 = sin(t*dAngle + dPhase)*dInvSin;
        return dCoeff0*p + dCoeff1*q;
    }
}
//---------------------------------------------------------------------------
void Quaternion::Intermediate (const Quaternion& q0, const Quaternion& q1,
    const Quaternion& q2, Quaternion& a, Quaternion& b)
{
    // assert:  q0, q1, q2 are unit quaternions

    Quaternion q0inv = q0.UnitInverse();
    Quaternion q1inv = q1.UnitInverse();
    Quaternion p0 = q0inv*q1;
    Quaternion p1 = q1inv*q2;
    Quaternion arg = 0.25*(p0.Log()-p1.Log());
    Quaternion marg = -arg;

    a = q1*arg.Exp();
    b = q1*marg.Exp();
}
//---------------------------------------------------------------------------
Quaternion Quaternion::Squad (double t, const Quaternion& p,
    const Quaternion& a, const Quaternion& b, const Quaternion& q)
{
    return Slerp(2*t*(1-t),Slerp(t,p,q),Slerp(t,a,b));
}
//---------------------------------------------------------------------------

#ifdef QUAT_TEST

#include <fstream.h>
#include <stdio.h>
#include <stdlib.h>

#define RAND (rand()/double(RAND_MAX))

ofstream ostr("data.txt");

typedef struct
{
    double t;
    Quaternion b;  // intermediate term before q
    Quaternion q;  // keyframe sample
    Quaternion a;  // intermediate term after q
}
Interpolant;

void main ()
{
    // build a sequence of quaternions
    ostr << "quaternions" << endl;
    const int N = 4;
    Quaternion q[N];
    double time[N];
    double sum = 0.0;
    int i;
    for (i = 0; i < N; i++)
    {
        sum += RAND;
        time[i] = sum;
        q[i] = Quaternion(RAND,RAND,RAND,RAND);
        double invlen = 1.0/sqrt(q[i].Norm());
        q[i].w *= invlen;
        q[i].x *= invlen;
        q[i].y *= invlen;
        q[i].z *= invlen;
    }
    double tmin = time[0], tmax = time[N-1], tran = tmax-tmin;

    // build the interpolants
    Interpolant intrp[N];
    intrp[0].t = time[0];
    intrp[0].q = q[0];
    for (i = 1; i < N; i++)
    {
        intrp[i].t = time[i];
        intrp[i].q = q[i];

        // Suggestion by bigneil@mediaone.net
        //
        // Make sure consecutive pairs of keyframe quaternions have
        // acute angle between them.  The choice of tangents should
        // guarantee that the intermediate 'a' and 'b' terms also form
        // acute angles with their respective sample points.
        if ( intrp[i-1].q.Dot(intrp[i].q) < 0.0 )
            intrp[i].q = -intrp[i].q;
    }

    Quaternion::Intermediate(intrp[0].q,intrp[0].q,intrp[1].q,
        intrp[0].a,intrp[0].b);
    for (i = 1; i <= N-2; i++)
    {
        Quaternion::Intermediate(intrp[i-1].q,intrp[i].q,intrp[i+1].q,
            intrp[i].a,intrp[i].b);
    }
    Quaternion::Intermediate(intrp[N-2].q,intrp[N-1].q,intrp[N-1].q,
        intrp[N-1].a,intrp[N-1].b);

    for (i = 0; i < N; i++)
    {
        ostr << i << endl;
        ostr << "  " << intrp[i].t << endl;
        ostr << "  "
             << intrp[i].b.w << ' '
             << intrp[i].b.x << ' '
             << intrp[i].b.y << ' '
             << intrp[i].b.z << ' ' << endl;
        ostr << "  "
             << intrp[i].q.w << ' '
             << intrp[i].q.x << ' '
             << intrp[i].q.y << ' '
             << intrp[i].q.z << ' ' << endl;
        ostr << "  "
             << intrp[i].a.w << ' '
             << intrp[i].a.x << ' '
             << intrp[i].a.y << ' '
             << intrp[i].a.z << ' ' << endl;
        ostr << endl;
    }

    // interpolate a few values
    ostr << endl << "interpolated values" << endl << endl;
    const int jmax = 100;
    for (int j = 0; j <= jmax; j++)
    {
        double t = tmin+j*tran/double(jmax);
        for (i = 0; i < N-1; i++)
        {
            if ( intrp[i].t <= t && t < intrp[i+1].t )
                break;
        }

        if ( i < N-2 ) // prevents a read one beyond the array bounds
        {       
            double relT = (t-intrp[i].t)/(intrp[i+1].t-intrp[i].t);
            Quaternion p = Quaternion::Squad(relT,intrp[i].q,intrp[i].a,
                intrp[i+1].b,intrp[i+1].q);
        
            ostr << t << " : " << p.w << ' ' << p.x << ' ' << p.y << ' '
                << p.z << endl;
        }
    }
}

#endif

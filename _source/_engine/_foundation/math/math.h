#ifndef __FOUNDATION_MATH_MATH__
#define __FOUNDATION_MATH_MATH__

#include <algorithm>
#include <math.h>
#include <stdint.h>

namespace raytracer
{

#define RT_NORMALIZATION_EPSILON float(1e-20f)

    // constants
    static const float RTPi = float(3.141592653589793);
    static const float RTHalfPi = float(1.57079632679489661923);
    static const float RTTwoPi = float(6.28318530717958647692);
    static const float RTInvPi = float(0.31830988618379067154);
    static const float RTInvTwoPi = float(0.15915494309189533577);
    static const float RTPiDivTwo = float(1.57079632679489661923);
    static const float RTPiDivFour = float(0.78539816339744830962);


    template <class T>
    inline T RTMax(T a, T b)
    {
        return a < b ? b : a;
    }

    //! overload for float to use fsel on xbox
    template <>
    inline float RTMax(float a, float b)
    {
        return std::max(a, b);
    }

    template <class T>
    inline T RTMin(T a, T b)
    {
        return a < b ? a : b;
    }

    template <>
    inline float RTMin(float a, float b)
    {
        return std::min(a, b);
    }

    inline float RTAbs(float a)
    {
        return std::abs(a);
    }

    inline bool RTEquals(float a, float b, float eps)
    {
        return (RTAbs(a - b) < eps);
    }

    inline double RTAbs(double a)
    {
        return ::fabs(a);
    }

    inline int32_t RTAbs(int32_t a)
    {
        return ::abs(a);
    }

    template <class T>
    inline T RTClamp(T v, T lo, T hi)
    {
        return RTMin(hi, RTMax(lo, v));
    }

    inline float RTSqrt(float a)
    {
        return ::sqrt(a);
    }

    inline double RTSqrt(double a)
    {
        return ::sqrt(a);
    }

    inline float RTRecipSqrt(float a)
    {
        return 1 / ::sqrt(a);
    }

    inline double RTRecipSqrt(double a)
    {
        return 1 / ::sqrt(a);
    }

    inline float RTSin(float a)
    {
        return ::sin(a);
    }

    inline double RTSin(double a)
    {
        return ::sin(a);
    }

    inline float RTCos(float a)
    {
        return ::cos(a);
    }

    inline double RTCos(double a)
    {
        return ::cos(a);
    }

    inline float RTTan(float a)
    {
        return ::tanf(a);
    }

    inline double RTTan(double a)
    {
        return ::tan(a);
    }

    inline float RTAsin(float f)
    {
        return ::asinf(RTClamp(f, -1.0f, 1.0f));
    }

    inline double RTAsin(double f)
    {
        return ::asin(RTClamp(f, -1.0, 1.0));
    }

    inline float RTAcos(float f)
    {
        return ::acosf(RTClamp(f, -1.0f, 1.0f));
    }

    inline double RTAcos(double f)
    {
        return ::acos(RTClamp(f, -1.0, 1.0));
    }

    inline float RTAtan(float a)
    {
        return ::atanf(a);
    }

    inline double RTAtan(double a)
    {
        return ::atan(a);
    }

    inline float RTAtan2(float x, float y)
    {
        return ::atan2f(x, y);
    }

    inline double RTAtan2(double x, double y)
    {
        return ::atan2(x, y);
    }

    inline bool RTIsFinite(float f)
    {
        return ::isfinite(f);
    }

    inline bool RTIsFinite(double f)
    {
        return ::isfinite(f);
    }

    inline float RTFloor(float a)
    {
        return ::floorf(a);
    }

    inline float RTExp(float a)
    {
        return ::expf(a);
    }

    inline float RTCeil(float a)
    {
        return ::ceilf(a);
    }

    inline float RTPow(float x, float y)
    {
        return ::powf(x, y);
    }

    inline float RTLog(float x)
    {
        return ::logf(x);
    }

}

#endif
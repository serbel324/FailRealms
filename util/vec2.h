#pragma once
#include <cmath>

/* define NO_USINGS before #include if you don't want Vec3f, Vec2d etc to be generated */
#ifndef NO_USINGS 
#define USINGS_FOR_TYPES
#endif
#undef NO_USINGS

/* define NO_IOSTREAM before #include if your type doesn't support iostream */
#ifndef NO_IOSTREAM 
#define IOSTREAM_SUPPORTED
#endif
#undef NO_IOSTREAM

template <typename T, typename FloatType = float> /* T must be algebraic field */
struct TVec2
{
    TVec2(T X = 0, T Y = 0);

    TVec2(const TVec2& other);
    TVec2(TVec2&& other);

    TVec2& operator=(const TVec2& other) = default;
    TVec2& operator=(TVec2&& other) = default;

    template <typename T1, typename FloatType1>
    TVec2(const TVec2<T1, FloatType1>& other);
    template <typename T1, typename FloatType1>
    TVec2(TVec2<T1, FloatType1>&& other);

    template <typename T1>
    void Set(T1 X, T1 Y);

    /* comparison without eps, be careful with floating types */
    bool operator==(const TVec2& other) const;
    bool operator!=(const TVec2& other) const;

    /* true if this' and other's coordinates differerence is no more than eps */
    bool CompareWithEps(const TVec2& other) const;

    template <typename T1, typename FloatType1>
    TVec2& operator=(const TVec2<T1, FloatType1>& other);
    template <typename T1, typename FloatType1>
    TVec2& operator=(TVec2<T1, FloatType1>&& other);

    ~TVec2() = default;

    TVec2 operator-() const;

    template <typename T1, typename FloatType1>
    TVec2& operator+=(TVec2<T1, FloatType1> r);
    template <typename T1, typename FloatType1>
    TVec2& operator-=(TVec2<T1, FloatType1> r);

    template <typename T1>
    TVec2& operator*=(T1 r);
    template <typename T1>
    TVec2& operator/=(T1 r);

    template <typename T1, typename FloatType1>
    TVec2 operator+(TVec2<T1, FloatType1> r) const;
    template <typename T1, typename FloatType1>
    TVec2 operator-(TVec2<T1, FloatType1> r) const;

    template <typename T1>
    TVec2 operator*(T1 r) const;
    template <typename T1>
    TVec2 operator/(T1 r) const;

    FloatType Abs();
    TVec2 Norm();

    TVec2 rotate(FloatType a);

    T X;
    T Y;

    static constexpr FloatType EPS = 1e-9f;
};

#ifdef USINGS_FOR_TYPES
using TVec2i = TVec2<int, float>;
using TVec2f = TVec2<float, float>;
using TVec2d = TVec2<double, float>;
#endif

/* returns scalar product */
template <typename T, typename FloatType>
T dot_prod(TVec2<T, FloatType> l, TVec2<T, FloatType> r);

/* returns vector product = |X|*|Y|*sin(Angle(X,Y)) */
template <typename T, typename FloatType>
T cross_prod(TVec2<T, FloatType> l, TVec2<T, FloatType> r);

/* returns distance between point a and b */
template <typename T, typename FloatType>
FloatType dist(TVec2<T, FloatType> a, TVec2<T, FloatType> b);

/* returns Angle between vectors a and b in range[-pi, pi] */
template <typename T, typename FloatType>
FloatType Angle(TVec2<T, FloatType> a, TVec2<T, FloatType> b);

/* returns true if a and b are collinear */
template <typename T, typename FloatType>
bool check_parallel(TVec2<T, FloatType> a, TVec2<T, FloatType> b);


#ifdef IOSTREAM_SUPPORTED
#include <iostream>
/* ------------------ I/O operators ------------------ */
template <typename T, typename FloatType>
std::istream& operator>>(std::istream& in, TVec2<T, FloatType>& v);

template <typename T, typename FloatType>
std::ostream& operator<<(std::ostream& out, const TVec2<T, FloatType>& v);
#endif

/* =========================================================================== */
/* =============================== DEFINITIONS =============================== */
/* =========================================================================== */

template<typename T, typename FloatType>
TVec2<T, FloatType>::TVec2(T x, T y)
    : X(x), Y(y)
{}

template<typename T, typename FloatType>
TVec2<T, FloatType>::TVec2(const TVec2& other)
    : X(other.X), Y(other.Y)
{}

template<typename T, typename FloatType>
TVec2<T, FloatType>::TVec2(TVec2&& other)
    : X(other.X), Y(other.Y)
{
    other.X = 0;
    other.Y = 0;
}

template<typename T, typename FloatType>
template<typename T1, typename FloatType1>
TVec2<T, FloatType>::TVec2(const TVec2<T1, FloatType1>& other)
    : X(other.X), Y(other.Y)
{}

template<typename T, typename FloatType>
template<typename T1, typename FloatType1>
TVec2<T, FloatType>::TVec2(TVec2<T1, FloatType1>&& other)
    : X(other.X), Y(other.Y)
{
    other.X = 0;
    other.Y = 0;
}

template<typename T, typename FloatType>
template<typename T1>
inline void TVec2<T, FloatType>::Set(T1 x, T1 y)
{
    X = x;
    Y = y;
}

template<typename T, typename FloatType>
bool TVec2<T, FloatType>::operator==(const TVec2& other) const
{
    return (X == other.X && Y == other.Y);
}

template<typename T, typename FloatType>
bool TVec2<T, FloatType>::operator!=(const TVec2& other) const
{
    return (X != other.X || Y != other.Y);
}

template<typename T, typename FloatType>
bool TVec2<T, FloatType>::CompareWithEps(const TVec2& other) const
{
    return (std::abs(X - other.X) < EPS && std::abs(Y - other.Y) < EPS);
}

template<typename T, typename FloatType>
template<typename T1, typename FloatType1>
TVec2<T, FloatType>& TVec2<T, FloatType>::operator=(const TVec2<T1, FloatType1>& other)
{
    X = other.X;
    Y = other.Y;

    return *this;
}

template<typename T, typename FloatType>
template<typename T1, typename FloatType1>
TVec2<T, FloatType>& TVec2<T, FloatType>::operator=(TVec2<T1, FloatType1>&& other)
{
    X = other.X;
    Y = other.Y;
    other.X = other.Y = 0;

    return *this;

}

template<typename T, typename FloatType>
TVec2<T, FloatType> TVec2<T, FloatType>::operator-() const
{
    return TVec2(-X, -Y);
}

template<typename T, typename FloatType>
template<typename T1, typename FloatType1>
TVec2<T, FloatType>& TVec2<T, FloatType>::operator+=(TVec2<T1, FloatType1> r)
{
    X += r.X;
    Y += r.Y;
    return *this;
}

template<typename T, typename FloatType>
template<typename T1, typename FloatType1>
TVec2<T, FloatType>& TVec2<T, FloatType>::operator-=(TVec2<T1, FloatType1> r)
{
    return *this += -r;
}

template<typename T, typename FloatType>
template<typename T1, typename FloatType1>
TVec2<T, FloatType> TVec2<T, FloatType>::operator+(TVec2<T1, FloatType1> r) const
{
    TVec2 v(*this);
    return v += r;
}

template<typename T, typename FloatType>
template<typename T1, typename FloatType1>
TVec2<T, FloatType> TVec2<T, FloatType>::operator-(TVec2<T1, FloatType1> r) const
{
    TVec2 v(*this);
    return v -= r;
}

template<typename T, typename FloatType>
FloatType TVec2<T, FloatType>::Abs()
{
    return std::sqrt(X * X + Y * Y);
}

template<typename T, typename FloatType>
TVec2<T, FloatType> TVec2<T, FloatType>::Norm()
{
    if (Abs() < EPS)
    {
        return *this;
    }
    return TVec2(X / Abs(), Y / Abs());
}

template<typename T, typename FloatType>
inline TVec2<T, FloatType> TVec2<T, FloatType>::rotate(FloatType a)
{
    return TVec2(
        X * std::cos(a) - Y * std::sin(a),
        X * std::sin(a) + Y * std::cos(a));
}

template<typename T, typename FloatType>
template<typename T1>
TVec2<T, FloatType>& TVec2<T, FloatType>::operator*=(T1 r)
{
    X *= r;
    Y *= r;
    return *this;
}

template<typename T, typename FloatType>
template<typename T1>
TVec2<T, FloatType>& TVec2<T, FloatType>::operator/=(T1 r)
{
    return *this *= 1 / r;
}

template<typename T, typename FloatType>
template<typename T1>
TVec2<T, FloatType> TVec2<T, FloatType>::operator*(T1 r) const
{
    TVec2 v(*this);
    return v *= r;
}


template<typename T, typename FloatType>
template<typename T1>
TVec2<T, FloatType> TVec2<T, FloatType>::operator/(T1 r) const
{
    TVec2 v(*this);
    return v /= r;
}

#ifdef IOSTREAM_SUPPORTED
template<typename T, typename FloatType>
std::istream& operator>>(std::istream& in, TVec2<T, FloatType>& v)
{
    in >> v.X >> v.Y;
    return in;
}

template<typename T, typename FloatType>
std::ostream& operator<<(std::ostream& out, const TVec2<T, FloatType>& v)
{
    out << v.X << ' ' << v.Y;
    return out;
}
#endif

template<typename T, typename FloatType>
T dot_prod(TVec2<T, FloatType> l, TVec2<T, FloatType> r)
{
    return l.X * r.X + l.Y * r.Y;
}

template<typename T, typename FloatType>
T cross_prod(TVec2<T, FloatType> l, TVec2<T, FloatType> r)
{
    return l.X * r.Y - l.Y * r.X;
}

template<typename T, typename FloatType>
FloatType dist(TVec2<T, FloatType> a, TVec2<T, FloatType> b)
{
    return (a - b).Abs();
}

template<typename T, typename FloatType>
FloatType Angle(TVec2<T, FloatType> a, TVec2<T, FloatType> b)
{
    return std::atan2(cross_prod(a, b), dot_prod(a, b));
}

template<typename T, typename FloatType>
bool check_parallel(TVec2<T, FloatType> a, TVec2<T, FloatType> b)
{
    double aabs = a.Abs();
    double babs = a.Abs();

    if (aabs < TVec2<T, FloatType>::EPS || babs < TVec2<T, FloatType>::EPS)
    {
        return true;
    }

    return (std::abs(cross_prod(a, b) / aabs / babs) < TVec2<T, FloatType>::EPS);
}

#undef FloatType
#undef USINGS_FOR_TYPES
#undef IOSTREAM_SUPPORRED
#undef EPS
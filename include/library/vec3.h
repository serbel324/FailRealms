#pragma once
#include <cmath>
#include <iostream>

/* T must be algebraic field */
template <typename T, class F = float>
struct Vec3
{
    Vec3();
    template<typename T1, typename T2, typename T3>
    Vec3(T1 x, T2 y, T3 z);
    template<typename T1, typename F1>
    Vec3(const Vec3<T1, F1>& other);
    template<typename T1, typename F1>
    Vec3(Vec3<T1, F1>&& other);
    
    /* comparison without eps, be careful with floating types */
    template<typename T1, typename F1>
    bool operator==(const Vec3<T1, F1>& other) const;
    template<typename T1, typename F1>
    bool operator!=(const Vec3<T1, F1>& other) const;

    /* true if this' and other's coordinates differerence is no more than eps */
    template<typename T1, typename F1>
    bool compare_with_eps(const Vec3<T1, F1>& other) const;

    template<typename T1, typename F1>
    Vec3& operator=(const Vec3<T1, F1>& other);
    template<typename T1, typename F1>
    Vec3& operator=(Vec3<T1, F1>&& other);

    template<typename T1, typename T2, typename T3>
    void Set(T1 x, T2 y, T3 z);

    Vec3 operator-() const;

    template <typename T1, typename F1>
    Vec3& operator+=(Vec3<T1, F1> r);
    template <typename T1, typename F1>
    Vec3& operator-=(Vec3<T1, F1> r);

    template <typename T1>
    Vec3& operator*=(T1 r);
    template <typename T1>
    Vec3& operator/=(T1 r);

    template <typename T1, typename F1>
    Vec3& operator*=(Vec3<T1, F1> r);
    template <typename T1, typename F1>
    Vec3& operator/=(Vec3<T1, F1> r);

    template <typename T1, typename F1>
    Vec3 operator+(Vec3<T1, F1> r) const;
    template <typename T1, typename F1>
    Vec3 operator-(Vec3<T1, F1> r) const;

    template <typename T1>
    Vec3 operator*(T1 r) const;
    template <typename T1>
    Vec3 operator/(T1 r) const;

    template <typename T1, typename F1>
    Vec3 operator*(Vec3<T1, F1> r) const;
    template <typename T1, typename F1>
    Vec3 operator/(Vec3<T1, F1> r) const;

    F magnitude() const;
    Vec3 normalized() const;

    T x;
    T y;
    T z;

    static constexpr long double EPS = 1e-9;
};

using Vec3i = Vec3<int>;
using Vec3f = Vec3<float>;
using Vec3d = Vec3<double>;

 /* returns scalar product */
template <typename T, typename F>
T dot_prod(Vec3<T, F> l, Vec3<T, F> r);

 /* returns vector product */
template <typename T, typename F>
Vec3<T, F> cross_prod(Vec3<T, F> l, Vec3<T, F> r);

/* returns distance between point a and b */
template <typename T, typename F>
F dist(Vec3<T, F> a, Vec3<T, F> b);

/* returns true if a and b are collinear */
template <typename T, typename F>
bool check_parallel(Vec3<T, F> a, Vec3<T, F> b);


/* ------------------ I/O operators ------------------ */
template <typename T, typename F>
std::istream& operator>>(std::istream& in, Vec3<T, F>& v);

template <typename T, typename F>
std::ostream& operator<<(std::ostream& out, const Vec3<T, F>& v);\

/* =========================================================================== */
/* =============================== DEFINITIONS =============================== */
/* =========================================================================== */

template <typename T, typename F>
Vec3<T, F>::Vec3()
    : x(0), y(0), z(0)
{}

template <typename T, typename F>
template<typename T1, typename T2, typename T3>
Vec3<T, F>::Vec3(T1 x, T2 y, T3 z)
    : x(x), y(y), z(z)
{}

template<typename T1, typename F1>
template<typename T2, typename F2>
Vec3<T1, F1>::Vec3(const Vec3<T2, F2>& other)
    : x(other.x), y(other.y), z(other.z)
{}

template<typename T1, typename F1>
template<typename T2, typename F2>
Vec3<T1, F1>::Vec3(Vec3<T2, F2>&& other)
    : x(other.x), y(other.y), z(other.z)
{
    other.x = 0;
    other.y = 0;
    other.z = 0;
}

template<typename T1, typename F1>
template<typename T2, typename F2>
bool Vec3<T1, F1>::operator==(const Vec3<T2, F2>& other) const
{
    return (x == other.x && y == other.y && z == other.z);
}

template<typename T1, typename F1>
template<typename T2, typename F2>
bool Vec3<T1, F1>::operator!=(const Vec3<T2, F2>& other) const
{
    return (x != other.x || y != other.y || z != other.z);
}

template<typename T1, typename F1>
template<typename T2, typename F2>
bool Vec3<T1, F1>::compare_with_eps(const Vec3<T2, F2>& other) const
{
    return std::abs(x - other.x) < EPS
        && std::abs(y - other.y) < EPS
        && std::abs(z - other.z) < EPS;
}

template<typename T1, typename F1>
template<typename T2, typename F2>
Vec3<T1, F1>& Vec3<T1, F1>::operator=(const Vec3<T2, F2>& other)
{
    x = other.x;
    y = other.y;
    z = other.z;

    return *this;
}

template<typename T1, typename F1>
template<typename T2, typename F2>
Vec3<T1, F1>& Vec3<T1, F1>::operator=(Vec3<T2, F2>&& other)
{
    x = other.x;
    y = other.y;
    z = other.z;

    return *this;
}

template<typename T, typename F>
template<typename T1, typename T2, typename T3>
void Vec3<T, F>::Set(T1 x, T2 y, T3 z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

template<typename T, typename F>
Vec3<T, F> Vec3<T, F>::operator-() const
{
    return Vec3(-x, -y, -z);
}

template<typename T1, typename F1>
template<typename T2, typename F2>
Vec3<T1, F1>& Vec3<T1, F1>::operator+=(Vec3<T2, F2> r)
{
    x += r.x;
    y += r.y;
    z += r.z;
    return *this;
}

template<typename T1, typename F1>
template<typename T2, typename F2>
Vec3<T1, F1>& Vec3<T1, F1>::operator-=(Vec3<T2, F2> r)
{
    return *this += -r;
}

template<typename T1, typename F1>
template<typename T2, typename F2>
Vec3<T1, F1>& Vec3<T1, F1>::operator*=(Vec3<T2, F2> r)
{
    x *= r.x;
    y *= r.y;
    z *= r.z;
    return *this;
}

template<typename T1, typename F1>
template<typename T2, typename F2>
Vec3<T1, F1>& Vec3<T1, F1>::operator/=(Vec3<T2, F2> r)
{
    x /= r.x;
    y /= r.y;
    z /= r.z;
    return *this;
}

template<typename T1, typename F1>
template<typename T2, typename F2>
Vec3<T1, F1> Vec3<T1, F1>::operator+(Vec3<T2, F2> r) const
{
    Vec3 v(*this);
    return v += r;
}

template<typename T1, typename F1>
template<typename T2, typename F2>
Vec3<T1, F1> Vec3<T1, F1>::operator-(Vec3<T2, F2> r) const
{
    Vec3 v(*this);
    return v -= r;
}

template<typename T1, typename F1>
template<typename T2, typename F2>
Vec3<T1, F1> Vec3<T1, F1>::operator*(Vec3<T2, F2> r) const
{
    Vec3 v(*this);
    return v *= r;
}

template<typename T1, typename F1>
template<typename T2, typename F2>
Vec3<T1, F1> Vec3<T1, F1>::operator/(Vec3<T2, F2> r) const
{
    Vec3 v(*this);
    return v /= r;
}

template<typename T, typename F>
F Vec3<T, F>::magnitude() const
{
    return std::sqrt(x * x + y * y + z * z);
}

template<typename T, typename F>
Vec3<T, F> Vec3<T, F>::normalized() const
{
    F mag = magnitude();
    if (mag < EPS)
    {
        return *this;
    }
    return Vec3(x / mag, y / mag, z / mag);
}

template<typename T, typename F>
template<typename T1>
Vec3<T, F>& Vec3<T, F>::operator*=(T1 r)
{
    x *= r;
    y *= r;
    z *= r;
    return *this;
}

template<typename T, typename F>
template<typename T1>
Vec3<T, F>& Vec3<T, F>::operator/=(T1 r)
{
    return *this *= 1 / r;
}

template<typename T, typename F>
template<typename T1>
Vec3<T, F> Vec3<T, F>::operator*(T1 r) const
{
    Vec3 v(*this);
    return v *= r;
}


template<typename T, typename F>
template<typename T1>
Vec3<T, F> Vec3<T, F>::operator/(T1 r) const
{
    Vec3 v(*this);
    return v /= r;
}

template<typename T, typename F>
std::istream& operator>>(std::istream& in, Vec3<T, F>& v)
{
    in >> v.x >> v.y >> v.z;
    return in;
}

template<typename T, typename F>
std::ostream& operator<<(std::ostream& out, const Vec3<T, F>& v)
{
    out << v.x << ' ' << v.y << ' ' << v.z;
    return out;
}

template<typename T, typename F>
T dot_prod(Vec3<T, F> l, Vec3<T, F> r)
{
    return l.x * r.x + l.y * r.y + l.z * r.z;
}

template<typename T, typename F>
Vec3<T, F> cross_prod(Vec3<T, F> l, Vec3<T, F> r)
{
    return Vec3<T, F>{
        l.y * r.z - l.z * r.y,
        l.x * r.z - l.z * r.x,
        l.x * r.y - l.y * r.x
    };
}

template<typename T, typename F>
F dist(Vec3<T, F> a, Vec3<T, F> b)
{
    return (a - b).magnitude();
}

template<typename T, typename F>
bool check_parallel(Vec3<T, F> a, Vec3<T, F> b)
{
    double amag = a.magnitude();
    double bmag = b.magnitude();

    if (amag < Vec3<T, F>::EPS || bmag < Vec3<T, F>::EPS)
    {
        return true;
    }

    return (std::abs(cross_prod(a, b) / amag / bmag) < Vec3<T, F>::EPS);
}

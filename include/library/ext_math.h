#pragma once

#include <cstdlib>
#include <random>
#include <cmath>
#include <ctime>
#include <climits>

#include <library/vec2.h>

namespace ExtMath {

extern const long double PI;

double ToRadian(double a);

double ToDegrees(double a);

float WeightedAverage(float a1, float p1, float a2, float p2);

float Hypot(float a1, float a2);

float Hypot(float x1, float y1, float x2, float y2);

float Hypot(Vec2<float> p1, Vec2<float> p2);

double Sigmoid(float x, float a);

int Sign(double a);

double RandomDouble(double a, double b);

int RandomInt(int a, int b);

double Interpolate(double a0, double a1, double p);
double Smootherstep(double a0, double a1, double p);

//   Interpolate values in square's corners and point inside the square
//
//   ^ y
//   |  p01          p11
// 1 -   * ---------- * 
//   |   |            |
//   |   |         <------- p=(x, y) in [0, 1]x[0, 1]
//   |   |            |
//   |   |            |
// 0 -   * ---------- * 
//   |  p00          p10
// --|---|------------|----------> x
//   |   0            1
// 
double InterpolateSquare(double p00, double p10, double p01, double p11, Vec2<double> p);
double SmootherstepSquare(double p00, double p10, double p01, double p11, Vec2<double> p);

template<typename T = double>
struct Polynomial {
    using Coefficients = std::vector<std::pair<uint32_t, T>>;

    T operator()(T x) const {
        T res = 0;
        for (const auto& [p, a] : coefficients) {
            res += std::pow(x, p) * a;
        }
        return res;
    }

    Coefficients coefficients;
};

double ModuleStepFunction(double x);

template<typename T = double>
struct Bounds {
    T min = -1e9;
    T max = 1e9;

    bool Contain(T x) const {
        return x >= min && x <= max;
    }
};

} // namespace ExtMath

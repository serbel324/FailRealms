#pragma once
#include "vec2.h"
#include <random>

/* Additional mathematical functions */
namespace NExtMath
{
	float GetRandomFloat(float min, float max);
	double GetRandomDouble(double min, double max);

	int GetRandomInt(int min, int max);

	double ToRadian(double a);
	double ToDegrees(double a);

	/* weighted average */
	double WeightedAverage(double a1, double p1, double a2, double p2);
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
	double InterpolateSquare(double p00, double p10, double p01, double p11, TVec2<double> p);
	double SmootherstepSquare(double p00, double p10, double p01, double p11, TVec2<double> p);

	double Hypot(double a1, double a2);
	double Hypot(double x1, double y1, double x2, double y2);
	double Hypot(TVec2<double> p1, TVec2<double> p2);

	/* Sigmoid function */
	double Sigmoid(double x, double a);

	int Sign(double a);

	constexpr double PI = 3.1415926535897932384626433832795028841971693993751058209749445923078164062;
};



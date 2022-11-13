#include "ext_math.h"

#include <cstdlib>
#include <random>
#include <cmath>
#include <ctime>
#include <climits>

namespace NExtMath {

int GetRandomInt(int min, int max)
{
	if (max <= min)
	{
		return min;
	}

	static std::mt19937_64 randomizer(std::time(0));
	unsigned long long base = randomizer(); /* in range [0; ULLONG_MAX) */
	long long normalized = base % (max - min);
	return normalized + min;
}

float GetRandomFloat(float min, float max) {
	return GetRandomDouble(min, max);
}

double GetRandomDouble(double min, double max) {
	if (max <= min)
	{
		return min;
	}

	static std::mt19937_64 randomizer(std::time(0));
	long double base = randomizer(); /* in range [0; ULLONG_MAX) */
	long double maxr = ULLONG_MAX;
	long double normalized = base / maxr; /* in range [0; 1) */
	return normalized * (max - min) + min;
}


double ToRadian(double a)
{
	return (a * PI / 180);
}

double ToDegrees(double a)
{
	return (a * 180 / PI);
}

double WeightedAverage(double a1, double p1, double a2, double p2)
{
	return (a1 * p1 + a2 * p2) / (p1 + p2);
}

double Interpolate(double a0, double a1, double p)
{
	return a1 * p + (1 - p) * a0;
}

double Smootherstep(double a0, double a1, double p)
{
	return (a1 - a0) * ((p * (p * 6.0 - 15.0) + 10.0) * p * p * p) + a0;
}

double InterpolateSquare(double p00, double p10, double p01, double p11, TVec2<double> p)
{
	return Interpolate(
		Interpolate(p00, p10, p.X),
		Interpolate(p01, p11, p.X),
		p.Y
	);
}

double SmootherstepSquare(double p00, double p10, double p01, double p11, TVec2<double> p)
{
	return Smootherstep(
		Smootherstep(p00, p10, p.X),
		Smootherstep(p01, p11, p.X),
		p.Y
	);
}

double Hypot(double a1, double a2)
{
	return(sqrt(a1 * a1 + a2 * a2));
}

double Hypot(double x1, double y1, double x2, double y2)
{
	return(sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2)));
}
double Hypot(TVec2<double> p1, TVec2<double> p2) {
	return(sqrt(pow(p1.X - p2.X, 2) + pow(p1.Y - p2.Y, 2)));
}

double Sigmoid(double x, double a)
{
	return 1 / (1 + exp(-x * a));
}

int Sign(double a)
{
	if (a == 0)	return 0;
	if (a > 0) return 1;
	return -1;
}

}

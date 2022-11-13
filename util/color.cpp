#include "color.h"
#include <util/ext_math.h>

#include <algorithm>

TColor::TColor(int r, int g, int b, int a)
{
	R = std::max(std::min(255, r), 0);
	G = std::max(std::min(255, g), 0);
	B = std::max(std::min(255, b), 0);
	A = std::max(std::min(255, a), 0);
}
TColor::TColor(int v)
{
	R = std::max(std::min(255, v), 0);
	G = std::max(std::min(255, v), 0);
	B = std::max(std::min(255, v), 0);
	A = 255;
}

TColor::~TColor()
{
}

TColor TColor::operator+(const TColor& right) const
{
	return TColor(R + right.R, G + right.G, B + right.B, A);
}

TColor TColor::operator+(const int right) const
{
	return TColor(R + right, G + right, B + right, A);
}

TColor TColor::operator-(const TColor& right) const
{
	return TColor(R - right.R, G - right.G, B - right.B, A);
}

TColor TColor::operator-(const int right) const
{
	return TColor(R - right, G - right, B - right, A);
}

TColor TColor::operator*(const float right) const
{
	return TColor(R * right, G * right, B * right, A);
}

TColor TColor::GetRandom()
{
	return TColor(
		NExtMath::GetRandomInt(0, 255), 
		NExtMath::GetRandomInt(0, 255), 
		NExtMath::GetRandomInt(0, 255)
	);
}

#pragma once
class TColor
{
public:
	TColor(int r, int g, int b, int a = 255);
	/* r, g, b are set to the same value v */
	TColor(int v = 0);		
	~TColor();

	TColor operator+ (const TColor& right) const;
	TColor operator- (const TColor& right) const;
	TColor operator+ (const int right) const;
	TColor operator- (const int right) const;
	TColor operator* (const float right) const;

	int R;
	int G;
	int B;
	int A;

	static TColor GetRandom();
};
#include "camera.h"

TCamera::TCamera()
{
	Position = TVec2<float>(0, 0);
	Angle = 0;
	Scale = 1;
}

TCamera::TCamera(float x, float y, float a, float s)
{
	Position = TVec2<float>(x, y);
	Angle = a;
	Scale = s;
}

TCamera::TCamera(TVec2<float> pos, float a, float s)
{
	Position = TVec2<float>(pos);
	Angle = a;
	Scale = s;
}

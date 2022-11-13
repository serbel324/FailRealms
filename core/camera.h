#pragma once
#include <util/vec2.h>
#include <memory>

class TCamera
{
public:
	TCamera();
	TCamera(float x, float y, float a = 0, float s = 1);
	TCamera(TVec2<float> pos, float a = 0, float s = 1);

	TVec2<float> Position;
	float Angle;
	float Scale;

	typedef std::shared_ptr<TCamera> SPtr;
};

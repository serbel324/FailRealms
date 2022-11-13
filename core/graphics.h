#pragma once
#include <util/vec2.h>
#include <util/color.h>
#include <core/camera.h>

#include <memory>
#include <string>

#include <SFML/Graphics.hpp>

/* Contains functions for drawing */
class TGraphics
{
public:
	typedef std::shared_ptr<TGraphics> SPtr;

public:
	/* requires RenderWindow pointer, Window's dimensions and TCamera object pointer (optionally) */
	TGraphics(std::shared_ptr<sf::RenderWindow> win, TVec2<int> ws);
	TGraphics(std::shared_ptr<sf::RenderWindow> win, TVec2<int> ws, TCamera::SPtr cam);

	/* draw a point with given coordinates */
	void DrawPoint(TVec2<float> pos);
	void DrawPoint(float x, float y);

	/* draw a point with given coordinates */
	void DrawCircle(float x, float y, float radius);
	void DrawCircle(TVec2<float> pos, float radius);

	/* draw broken line fith given verticies */
	void DrawBrokenLine(std::vector<TVec2<float>> t, TVec2<float> a, float s);

	/* draw straight line from one point to another */
	void DrawLine(TVec2<float> v1, TVec2<float> v2);
	void DrawLine(float x1, float y1, float x2, float y2);

	/* draw rectangle with given upper left Angle coordinates, width and height */
	void DrawRect(float x, float y, float W, float h);
	void DrawRect(TVec2<float> pos, TVec2<float> size);

	/* draw texture with given upper left Angle coordinates, width, height and rotation (rotation center is in the middle) */
	void DrawTexture(sf::Texture& tex, float x, float y, float W, float h);
	void DrawTexture(sf::Texture& tex, TVec2<float> pos, TVec2<float> size);
	void DrawTexture(sf::Texture& tex, TVec2<float> pos, TVec2<float> size, float a);

	/* Set color for drawing primitives */
	void SetFillColor(float r, float g, float b, float a);
	void SetFillColor(TColor col);

	/* Fill the screen with the same color */
	void Fill();

	/* Clear all */
	void Clear();

	/* draw text with given coordinates, size and font */
	void FillText(const std::string& text, float x, float y, float size, sf::Font& font);

	/* auxilary method */
	void ApplyCamera(TCamera::SPtr camera);

	void UpdateViewport();

	/* Set camera */
	void SetCamera(TCamera::SPtr camera);

	/* Set default camera parameters */
	void SetDefaultCamera();

	/* update the window */
	void Present();

private:
	std::shared_ptr<sf::RenderWindow> Window;
	TColor FillColor;

	TCamera::SPtr Camera;
	TVec2<int> WindowSize;
};
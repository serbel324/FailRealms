#pragma once

#include <library/vec2.h>
#include <rengine/core/color.h>
#include <rengine/core/camera.h>

#include <memory>
#include <string>

namespace REngine
{

/* Contains functions for drawing */
class Graphics
{
public:
    using SPtr = std::shared_ptr<Graphics>;

public:
    /* draw a point with given coordinates */
    virtual void DrawPoint(Vec2<float> pos, Color color) = 0;
    virtual void DrawPoint(float x, float y, Color color) = 0;

    /* draw a point with given coordinates */
    virtual void DrawCircle(float x, float y, float radius, Color fill_color) = 0;
    virtual void DrawCircle(Vec2<float> pos, float radius, Color fill_color) = 0;

    /* draw straight line from one point to another */
    virtual void DrawLine(Vec2<float> v1, Vec2<float> v2, Color color) = 0;
    virtual void DrawLine(float x1, float y1, float x2, float y2, Color color) = 0;

    /* draw rectangle with given upper left Angle coordinates, width and height */
    virtual void DrawRect(float x, float y, float w, float h, Color fill_color) = 0;
    virtual void DrawRect(Vec2<float> pos, Vec2<float> size, Color fill_color) = 0;

    /* draw texture with given upper left Angle coordinates, width, height and rotation (rotation center is in the middle) */
    // TODO: textures
    // virtual void DrawTexture(sf::Texture& tex, float x, float y, float w, float h);
    // virtual void DrawTexture(sf::Texture& tex, Vec2<float> pos, Vec2<float> size);
    // virtual void DrawTexture(sf::Texture& tex, Vec2<float> pos, Vec2<float> size, float a);

    /* Fill the screen with the same color */
    virtual void Fill(Color fill_color) = 0;

    /* Clear all */
    virtual void Clear() = 0;

    /* draw text with given coordinates, size and font */
    // TODO: fonts
    // virtual void FillText(const std::string& text, float x, float y, float size, sf::Font& font);

    /* Set camera */
    virtual void BindCamera(Camera::SPtr cam) = 0;

    virtual void UpdateCameraView() = 0;

    /* Set default camera parameters */
    virtual void ResetCamera() = 0;

    /* update the window */
    virtual void Present() = 0;
};

}
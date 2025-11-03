#pragma once

#include <library/vec2.h>
#include <memory>

namespace REngine {

class Camera
{
public:
    using SPtr = std::shared_ptr<Camera>;

public:
    Camera();
    Camera(float x, float y, float angle_rad = 0, Vec2f scale = Vec2f{1, 1});
    Camera(Vec2f pos, float angle_rad = 0, Vec2f scale = Vec2f{1, 1});

    Vec2f GetPosition() const;
    float GetAngleRad() const;
    Vec2f GetScale() const;

    void SetPosition(Vec2f position);
    void SetAngle(float angle_rad);
    void SetScale(Vec2f scale);

private:
    Vec2f _position;
    float _angle_rad;
    Vec2f _scale;

};

} // namespace REngine

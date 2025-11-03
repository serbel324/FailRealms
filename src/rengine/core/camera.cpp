#include <rengine/core/camera.h>

namespace REngine {

Camera::Camera()
    : _position(0, 0)
    , _angle_rad(0)
    , _scale(1, 1)
{}

Camera::Camera(float x, float y, float angle_rad, Vec2f scale)
    : _position(0, 0)
    , _angle_rad(angle_rad)
    , _scale(scale)
{}

Camera::Camera(Vec2<float> pos, float angle_rad, Vec2f scale)
    : _position(0, 0)
    , _angle_rad(angle_rad)
    , _scale(scale)
{}

Vec2f Camera::GetPosition() const {
    return _position;
}

float Camera::GetAngleRad() const {
    return _angle_rad;
}

Vec2f Camera::GetScale() const {
    return _scale;
}

void Camera::SetPosition(Vec2f position) {
    _position = position;
}

void Camera::SetAngle(float angle_rad) {
    _angle_rad = angle_rad;
}

void Camera::SetScale(Vec2f scale) {
    _scale = scale;
}

} // namespace REngine

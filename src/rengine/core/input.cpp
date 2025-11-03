#include <cassert>

#include <rengine/core/input.h>

namespace REngine {

void InputController::Init() {
    for (KeyCode key_code = KeyCode::kA; key_code < KeyCode::__KEY_CODE_ITEMS_COUNT__;
         key_code = static_cast<KeyCode>(static_cast<uint32_t>(key_code) + 1)) {
        _key_position[key_code] = false;
    }

    for (MouseButtonCode mb_code = MouseButtonCode::kLeftMouseButton;
         mb_code < MouseButtonCode::__MOUSE_BUTTON_ITEMS_COUNT__;
         mb_code = static_cast<MouseButtonCode>(static_cast<uint32_t>(mb_code) + 1)) {
        _mouse_button_position[mb_code] = false;
    }

    _mouse_position.Set(0, 0);
}

bool InputController::IsKeyDown(KeyCode key_code) const {
    assert(key_code < KeyCode::__KEY_CODE_ITEMS_COUNT__);
    return _key_position.at(key_code);
}

bool InputController::IsMouseButtonDown(MouseButtonCode mouse_button_code) const {
    assert(mouse_button_code < MouseButtonCode::__MOUSE_BUTTON_ITEMS_COUNT__);
    return _mouse_button_position.at(mouse_button_code);
}

Vec2f InputController::GetMousePosition() const {
    return _mouse_position;
}

void InputController::SetKeyPosition(KeyCode key_code, bool is_down) {
    assert(key_code < KeyCode::__KEY_CODE_ITEMS_COUNT__);
    _key_position[key_code] = is_down;
}

void InputController::SetMouseButtonPosition(MouseButtonCode mouse_button_code, bool is_down) {
    assert(mouse_button_code < MouseButtonCode::__MOUSE_BUTTON_ITEMS_COUNT__);
    _mouse_button_position[mouse_button_code] = is_down;
}

void InputController::SetMousePosition(float x, float y) {
    _mouse_position.Set(x, y);
}

void InputController::SetMousePosition(Vec2f position) {
    _mouse_position = position;
}

} // namespace Rengine

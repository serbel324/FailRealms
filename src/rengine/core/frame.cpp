#include <rengine/core/frame.h>

namespace REngine {

Frame::Frame(Frame::Settings settings)
    : _settings(std::move(settings))
    , _input_controller(new InputController)
    , _is_running(true)
{}

Graphics* Frame::Gr() {
    return _graphics.get();
}

InputController* Frame::Ic() {
    return _input_controller.get();
}

bool Frame::IsRunning() const {
    return _is_running;
}

void Frame::Render() {
    Gr()->Present();
}

void Frame::Initialize() {
    Ic()->Init();
}

bool Frame::Update(float) {
    if (_input_controller) {
        PollEvents();
    }
    return _is_running;
}

void Frame::PollEvents() {
    // do nothing
}

} // namespace REngine

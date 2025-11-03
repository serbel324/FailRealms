#pragma once

#include <vector>
#include <string>
#include <memory>
#include <deque>

#include <rengine/core/frame.h>

namespace REngine {

class Driver {
public:
    struct Settings {
        float minimum_update_delay_sec = 0;
    };

public:
    Driver(Frame::UPtr&& frame, Settings settings);
    void RunFrame();

private:
    Frame::UPtr _frame;
    Settings _settings;
};

} // namespace REngine

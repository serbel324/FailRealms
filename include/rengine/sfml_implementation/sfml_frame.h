#pragma once

#include <rengine/core/frame.h>
#include <SFML/Graphics.hpp>

namespace REngine {

class SFMLFrame : public Frame {
public:
    SFMLFrame(Frame::Settings settings);

    void PollEvents() override;

private:
    std::shared_ptr<sf::RenderWindow> _render_window;
};

} // namespace REngine

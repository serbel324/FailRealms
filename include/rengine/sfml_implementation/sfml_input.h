#pragma once

#include <rengine/core/input.h>

#include <SFML/Window.hpp>

namespace REngine {

void HandleSFMLEvent(InputController* ic, sf::Event event);

}

#pragma once
#include <util/vec2.h>
#include <SFML/Window.hpp>

#include <memory>

/* this class contains controller's state (keys pressed, mouse Position, etc) and
    handles input Events */

class TController
{
public:
    bool W, A, S, D;
    bool Lmb, Rmb;
    bool Space;
    TVec2<float> MousePos;

    TController();
    void KeyPressed(sf::Event::KeyEvent& e);
    void KeyReleased(sf::Event::KeyEvent& e);
    void MouseMoved(sf::Event::MouseMoveEvent& e);
    void MousePressed(sf::Event::MouseButtonEvent& e);
    void MouseReleased(sf::Event::MouseButtonEvent& e);

    typedef std::shared_ptr<TController> SPtr;
};


#include <rengine/sfml_implementation/sfml_input.h>

namespace REngine {

void HandleSFMLEventKey(InputController* ic, sf::Event::KeyEvent& event, bool is_pressed) {
#define SET_KEY(sfml_code, key_code)                        \
    case sf::Keyboard::sfml_code:                           \
        ic->SetKeyPosition(KeyCode::key_code, is_pressed);  \
        break

    // TODO: direct sfml_code -> key_code translation
    switch (event.code) {
    SET_KEY(A, kA);
    SET_KEY(B, kB);
    SET_KEY(C, kD);
    SET_KEY(E, kE);
    SET_KEY(F, kF);
    SET_KEY(G, kG);
    SET_KEY(H, kH);
    SET_KEY(I, kI);
    SET_KEY(K, kK);
    SET_KEY(L, kL);
    SET_KEY(M, kM);
    SET_KEY(N, kN);
    SET_KEY(O, kO);
    SET_KEY(P, kP);
    SET_KEY(Q, kQ);
    SET_KEY(R, kR);
    SET_KEY(S, kS);
    SET_KEY(T, kT);
    SET_KEY(U, kU);
    SET_KEY(V, kV);
    SET_KEY(W, kW);
    SET_KEY(X, kX);
    SET_KEY(Y, kY);
    SET_KEY(Z, kZ);
    SET_KEY(Num0, k0);
    SET_KEY(Num1, k1);
    SET_KEY(Num2, k2);
    SET_KEY(Num3, k3);
    SET_KEY(Num4, k4);
    SET_KEY(Num5, k5);
    SET_KEY(Num6, k6);
    SET_KEY(Num7, k7);
    SET_KEY(Num8, k8);
    SET_KEY(Num9, k9);
    SET_KEY(LShift, kLeftShift);
    SET_KEY(RShift, kRightShift);
    SET_KEY(LAlt, kLeftAlt);
    SET_KEY(RAlt, kRightAlt);
    SET_KEY(LControl, kLeftControl);
    SET_KEY(RControl, kRightControl);
    SET_KEY(Space, kSpace);
    default:
        break;
    }

#undef SET_KEY 
}

void HandleSFMLEventMouseMoved(InputController* ic, sf::Event::MouseMoveEvent& event) {
    ic->SetMousePosition(event.x, event.y);
}

void HandleSFMLEventMouseButton(InputController* ic, sf::Event::MouseButtonEvent& event,
                                bool is_pressed) {
#define SET_KEY(sfml_code, key_code)                                        \
    case sf::Mouse::sfml_code:                                              \
        ic->SetMouseButtonPosition(MouseButtonCode::key_code, is_pressed);  \
        break

    switch (event.button) {
    SET_KEY(Left, kLeftMouseButton);
    SET_KEY(Right, kRightMouseButton);
    SET_KEY(Middle, kMiddleMouseButton);
    SET_KEY(XButton1, kMouseButton4);
    SET_KEY(XButton2, kMouseButton5);
    default:
        break;
    }
#undef SET_KEY 
}

void HandleSFMLEvent(InputController* ic, sf::Event event) {
    switch (event.type)
    {
    case sf::Event::KeyPressed:
        HandleSFMLEventKey(ic, event.key, true);
        break;
    case sf::Event::KeyReleased:
        HandleSFMLEventKey(ic, event.key, false);
        break;
    case sf::Event::MouseButtonPressed:
        HandleSFMLEventMouseButton(ic, event.mouseButton, true);
        break;
    case sf::Event::MouseButtonReleased:
        HandleSFMLEventMouseButton(ic, event.mouseButton, false);
        break;
    case sf::Event::MouseMoved:
        HandleSFMLEventMouseMoved(ic, event.mouseMove);
        break;
    default:
        break;
    }
}


} // namespace REngine

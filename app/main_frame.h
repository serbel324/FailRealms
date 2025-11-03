#include <rengine/sfml_implementation/sfml_frame.h>
#include <library/vec2.h>

#include "world.h"
#include "parse_config.h"

#include <fstream>

using namespace REngine;

const Vec2i _screenSize{1500, 1500};

class MainFrame : public SFMLFrame {
public:
    MainFrame()
        : SFMLFrame(
            Frame::Settings{
                .screen_size = _screenSize,
                .window_name = "MainFrame",
            })
    {}

    void RegenerateWorld() {
        _world.Generate(ParseConfigFromFile("world_settings.json"));
    }

    void Initialize() override {
        std::cout << "Init" << std::endl;
        Frame::Initialize();
        RegenerateWorld();
    }

    void Input() {
        if (Ic()->IsKeyDown(KeyCode::kSpace)) {
            _world.Regenerate();
        }
        if (Ic()->IsKeyDown(KeyCode::kT)) {
            _world.SetRenderedLayer(World::Layer::TEMPERATURE);
        }
        if (Ic()->IsKeyDown(KeyCode::kH)) {
            _world.SetRenderedLayer(World::Layer::HUMIDITY);
        }
        if (Ic()->IsKeyDown(KeyCode::kS)) {
            _world.SetRenderedLayer(World::Layer::SURFACE);
        }
    }

    bool Update(float elapsedSec) override {
        Gr()->Fill(REngine::Color::WHITE);
        Input();
        _world.TickAndRender(elapsedSec * 1000, GetGraphics<SFMLGraphics>(), _screenSize);
        Frame::Render();
        return Frame::Update(elapsedSec * 1000);
    }

private:
    World _world;
};

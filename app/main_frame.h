#include <core/frame.h>
#include <core/color.h>
#include <library/vec2.h>

#include "world.h"
#include "parse_config.h"

#include <fstream>

using namespace REngine;

const Vec2i _worldSize{300, 300};
const Vec2i _screenSize{800, 800};

class MainFrame : public Frame {
public:
    MainFrame()
        : Frame(
            Frame::Settings{
                .id = "MainFrame",
                .screenSize = _screenSize,
            },
            nullptr,
            MakeGenericWindow(_screenSize, "Demo app"))
    {}

    void Initialize() override {
        std::cout << "Init" << std::endl;
        _world.Generate(ParseConfigFromFile("world_settings.json"));

        Ic()->keyPressedCallback = [&](const sf::Keyboard::Key& key) {
            switch (key) {
            case sf::Keyboard::S:
                _world.SetRenderedLayer(World::Layer::SURFACE);
                break;
            case sf::Keyboard::T:
                _world.SetRenderedLayer(World::Layer::TEMPERATURE);
                break;
            case sf::Keyboard::H:
                _world.SetRenderedLayer(World::Layer::HUMIDITY);
                break;
            case sf::Keyboard::Space:
                _world.Generate(ParseConfigFromFile("world_settings.json"));
                break;
            default:
                break;
            }
        };

        Ic()->keyReleasedCallback = [&](const sf::Keyboard::Key& key) {
            switch (key) {
            case sf::Keyboard::S:
                _world.SetRenderedLayer(World::Layer::SURFACE);
                break;
            case sf::Keyboard::T:
                _world.SetRenderedLayer(World::Layer::SURFACE);
                break;
            case sf::Keyboard::H:
                _world.SetRenderedLayer(World::Layer::SURFACE);
                break;
            default:
                break;
            }
        };
    }

    bool Update(float elapsedMs) override {
        _world.Tick(elapsedMs);
        return Frame::Update(elapsedMs);
    }

    void Render() override {
        Gr()->SetFillColor(REngine::Color::WHITE);
        Gr()->Fill();

        _world.Render(Gr(), _screenSize);
        Frame::Render();
    }

private:
    World _world;
};

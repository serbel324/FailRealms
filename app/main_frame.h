#include <core/frame.h>
#include <core/color.h>
#include <library/vec2.h>

#include "world.h"

#include <iostream>

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
        _world.Generate({
            .dayDuration = 4000,
            .worldSize = _worldSize,
            .mainNoiseSettings = PerlinNoise::Settings{},
            .biomes = { World::Settings::Biome{} }
        });
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

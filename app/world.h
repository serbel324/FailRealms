#pragma once

#include <atomic>
#include <algorithm>
#include <cassert>
#include <functional>
#include <vector>
#include <thread>
#include <mutex>

#include <library/vec2.h>
#include <library/vec3.h>
#include <library/ext_math.h>

#include <SFML/Graphics.hpp>

#include "perlin.h"

#include <rengine/core/color.h>
#include <rengine/core/graphics.h>
#include <rengine/sfml_implementation/sfml_graphics.h>

using namespace REngine;
using ExtMath::Bounds;

class World {
public:
    enum class Layer : uint32_t {
        SURFACE = 0,
        TEMPERATURE,
        HUMIDITY,
    };

public:
    struct Settings {

        struct Biome {
            enum class SurfaceType {
                NORMAL = 0,
                WATER,
                ICE,
            };
            std::string name = "TabulaRasa";
            // Terrain
            Bounds<double> heightBounds{-10000, 10000};
            Bounds<double> slopeBounds{0, 90};

            Bounds<double> temperatureBounds{-278, 5000};
            Bounds<double> humidityBounds{-1000, 1000};

            SurfaceType surfaceType = SurfaceType::NORMAL;

            // Surface
            double surfaceAlbedo = 1;
            Color surfaceColor = Color(255, 255, 255);
        };

        struct LightSource {
            std::string name = "Sol";
            double brightness = 1;
            double cycleDuration = 1000;
            double phase = 0;
        };
    
        double dayDuration = 4000;
        Vec2ui32 worldSize = Vec2ui32{100, 100};
        double islandSize = 1.5;

        PerlinNoise::Settings heightNoiseSettings;
        PerlinNoise::Settings temperatureNoiseSettings;
        PerlinNoise::Settings humidityNoiseSettings;

        std::vector<LightSource> lightSources;
        std::vector<Biome> biomes;
    };

public:
    World();

    void Generate(const Settings& settings);
    void Regenerate();
    void TickAndRender(double elapsedMs, REngine::SFMLGraphics* gr, Vec2ui32 windowSize);

    void SetRenderedLayer(Layer layer);

private:
    double GetHeight(uint32_t x, uint32_t y) {
        return _map[y][x].height;
    }

    Vec3d GetNormal(uint32_t x, uint32_t y) {
        Vec3d p(x, y, GetHeight(x, y));
        Vec3d p10(x + 1, y, GetHeight(x + 1, y));
        Vec3d p01(x, y + 1, GetHeight(x, y + 1));
        return cross_prod(p10 - p, p01 - p).normalized();
    }

    void UpdateVertexArray(uint32_t y);

    Layer _renderedLayer = Layer::SURFACE;

    double _time = 0;
    Settings _settings;

    double _dayDuration = 5000;

    Vec3d _sunLight;
    Vec3d _moonLight;

    double _sunBrightness = 1.0;
    double _moonBrightness = 0.2;
    double _starBrightness = 0.1;

    Vec2ui32 _size;

    struct Cell {
        double height;
        double temperature;
        double humidity;
        Vec3d normal;
        uint32_t biome;
    };

    std::vector<std::vector<Cell>> _map;

    PerlinNoise _heightNoise;
    PerlinNoise _temperatureNoise;
    PerlinNoise _humidityNoise;

    sf::VertexArray _vertexArray;

public:
    struct WorldWorker;

private:
    static constexpr uint32_t MAX_WORKERS = 32;
    void StartWorkers();

    [[nodiscard]] std::vector<std::unique_lock<std::mutex>> Blockade();

    // workers
    uint32_t _numWorkers;
    std::vector<std::thread> _workers;
    std::array<std::mutex, MAX_WORKERS> _mutex;

    uint32_t _stripe_size = 10;
    uint32_t _stripe_count;

    std::atomic<uint64_t> _stripe;
    std::atomic<uint64_t> _stripes_done;
};
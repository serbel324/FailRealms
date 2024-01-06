#pragma once

#include <algorithm>
#include <vector>

#include <library/vec2.h>
#include <library/vec3.h>
#include <library/ext_math.h>

#include "perlin.h"

#include <core/color.h>
#include <core/graphics.h>

using namespace REngine;
using ExtMath::Bounds;

class World {
public:
    struct Settings {

        struct Biome {
            std::string name = "TabulaRasa";
            // Terrain
            Bounds<double> heightBounds{-10000, 10000};
            Bounds<double> slopeBounds{0, 90};

            bool water = false;

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
    
        double dayDuration;
        Vec2u worldSize = Vec2u{100, 100};

        PerlinNoise::Settings heightNoiseSettings;
        PerlinNoise::Settings temperatureNoiseSettings;

        std::vector<LightSource> lightSources;
        std::vector<Biome> biomes;
    };

public:
    World();

    void Generate(Settings settings);
    void Render(Graphics* gr, Vec2u windowSize);
    void Tick(double dtime);

private:
    double GetHeight(uint32_t x, uint32_t y) {
        return _heightMap[y][x];
    }

    Vec3d GetNormal(uint32_t x, uint32_t y) {
        Vec3d p(x, y, _heightMap[y][x]);
        Vec3d p10(x + 1, y, _heightMap[y][x + 1]);
        Vec3d p01(x, y + 1, _heightMap[y + 1][x]);
        return cross_prod(p10 - p, p01 - p).normalized();
    }

    double _time = 0;
    Settings _settings;

    double _dayDuration = 5000;

    Vec3d _sunLight;
    Vec3d _moonLight;

    double _sunBrightness = 1.0;
    double _moonBrightness = 0.2;
    double _starBrightness = 0.1;

    Vec2u _size;

    std::vector<std::vector<double>> _heightMap;
    std::vector<std::vector<double>> _temperatureMap;
    std::vector<std::vector<Vec3d>> _normalMap;
    std::vector<std::vector<uint32_t>> _biomeMap;

    PerlinNoise _heightNoise;
    PerlinNoise _temperatureNoise;
};
#include "world.h"

#include <set>

World::World()
    : _time(0) 
{}

void World::Generate(Settings settings) {
    std::cout << "Generate" << std::endl;
    _settings = settings;

    {
        uint32_t depth = 8;
        PerlinNoise::Settings settings{
            .depth = depth,
            .baseGridResolution = 4,
            .amplitudeGenerator = [=](uint32_t x) {
                return std::pow(2, depth - 1 - x) * 2;
            }
        };
        _heightNoise.Generate(_settings.heightNoiseSettings);
        _temperatureNoise.Generate(_settings.temperatureNoiseSettings);
    }

    _heightMap.assign(_settings.worldSize.y + 1, std::vector<double>(_settings.worldSize.x + 1));
    _temperatureMap.assign(_settings.worldSize.y + 1, std::vector<double>(_settings.worldSize.x + 1));
    _biomeMap.assign(_settings.worldSize.y + 1, std::vector<uint32_t>(_settings.worldSize.x + 1));
    _normalMap.assign(_settings.worldSize.y, std::vector<Vec3d>(_settings.worldSize.x));
    // heights
    for (uint32_t y = 0; y < _settings.worldSize.y; ++y) {
        for (uint32_t x = 0; x < _settings.worldSize.x; ++x) {
            Vec2d p = Vec2d{x, y} / _settings.worldSize;
            double height = _heightNoise(p);
            double island = -10 * (std::pow(p.x * 4 - 2, 4) + std::pow(p.y * 4 - 2, 4));
            _heightMap[y][x] = (height + island);
            _temperatureMap[y][x] = _temperatureNoise(p);
        }
    }

    // normals
    for (uint32_t y = 0; y < _settings.worldSize.y; ++y) {
        for (uint32_t x = 0; x < _settings.worldSize.x; ++x) {
            _normalMap[y][x] = GetNormal(x, y);
        }
    }

    // biomes
    for (uint32_t y = 0; y < _settings.worldSize.y; ++y) {
        for (uint32_t x = 0; x < _settings.worldSize.x; ++x) {
            double height = _heightMap[y][x];
            const auto& normal = _normalMap[y][x];
            double slope = ExtMath::ToDegrees(angle(Vec3d{0, 0, 1}, normal));
            std::vector<uint32_t> candidates;
            for (uint32_t i = 0; i < _settings.biomes.size(); ++i) {
                const auto& candidate = _settings.biomes[i];
                if (!candidate.heightBounds.Contain(height)) {
                    continue;
                }
                if (!candidate.slopeBounds.Contain(slope)) {
                    continue;
                }
                candidates.push_back(i);
            }
            assert(!candidates.empty());
            _biomeMap[y][x] = *(candidates.begin());
        }
    }
}

void World::Render(Graphics* gr, Vec2<uint32_t> windowSize) {
    sf::Image imageTerrain;
    imageTerrain.create(_settings.worldSize.x, _settings.worldSize.y, sf::Color::Red);
    for (uint32_t y = 0; y < _settings.worldSize.y; ++y) {
        for (uint32_t x = 0; x < _settings.worldSize.x; ++x) {
            double height = _heightMap[y][x];
            const auto& biome = _settings.biomes[_biomeMap[y][x]];
            const auto& normal = _normalMap[y][x];
            Color fillColor;
            double sun = std::max(0., dot_prod(_sunLight, normal));
            double moon = std::max(0., dot_prod(_moonLight, normal));
            double light = _starBrightness + sun * _sunBrightness + moon * _moonBrightness;

            if (biome.water) {
                light *= std::exp(height * 0.5) * 0.8;
                double surfaceLight = dot_prod(Vec3d{0, 0, 1}, _sunLight) * _sunBrightness;
                light += surfaceLight * ExtMath::RandomDouble(0.9, 1);
            }

            fillColor = biome.surfaceColor;
            fillColor = fillColor * light * biome.surfaceAlbedo;

          //  double t = _temperatureMap[y][x];
          //  fillColor = Color(1, 1, 1) * t;

            imageTerrain.setPixel(x, y, sf::Color(fillColor.r, fillColor.g, fillColor.b));
        }
    }
    sf::Texture tex;
    tex.create(_settings.worldSize.x, _settings.worldSize.y);
    tex.update(imageTerrain);

    gr->DrawTexture(tex, windowSize * 0.5, windowSize);
}

void World::Tick(double elapsedMs) {
    _time += elapsedMs;
    if (_time >= _settings.dayDuration) {
        _time -= _settings.dayDuration;
        Generate(_settings);
    }
    double a = (_time / _settings.dayDuration + 0.5) * 2 * ExtMath::PI;
    _sunLight = Vec3d(0, std::sin(a), std::cos(a));
    _moonLight = Vec3d(0, std::sin(a + ExtMath::PI), std::cos(a + ExtMath::PI));
}
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
        _mainNoise.Generate(settings);
    }

    _heightMap.assign(_settings.worldSize.y + 1, std::vector<double>(_settings.worldSize.x + 1));
    _biomeMap.assign(_settings.worldSize.y + 1, std::vector<uint32_t>(_settings.worldSize.x + 1));
    _normalMap.assign(_settings.worldSize.y, std::vector<Vec3d>(_settings.worldSize.x));
    // heights
    for (uint32_t y = 0; y < _settings.worldSize.y; ++y) {
        for (uint32_t x = 0; x < _settings.worldSize.x; ++x) {
            Vec2d p = Vec2d{x, y} / _settings.worldSize;
            double noise = _mainNoise(p);
            double sign = ExtMath::Sign(noise);
            double mainNoise = sign * std::pow(std::abs(noise / 200), 2.5) * 200;
            //  double mountains = MountainNoise.Get(p);
            double island = (1 - std::pow(p.x * 4 - 2, 4) - std::pow(p.y * 4 - 2, 4)) * 10;
            _heightMap[y][x] = (mainNoise + island) / 5;
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
            std::set<uint32_t> biomeOptions;
            for (uint32_t i = 0; i < _settings.biomes.size(); ++i) {
                if (height >= _settings.biomes[i].minHeight && height < _settings.biomes[i].maxHeight) {
                    biomeOptions.insert(i);
                }
            }
            assert(!biomeOptions.empty());
            _biomeMap[y][x] = *(biomeOptions.begin());
        }
    }
}

void World::Render(Graphics* gr, Vec2<uint32_t> windowSize) {
    sf::Image imageTerrain;
    imageTerrain.create(_settings.worldSize.x, _settings.worldSize.y, sf::Color::Red);
    for (uint32_t y = 0; y < _settings.worldSize.y; ++y) {
        for (uint32_t x = 0; x < _settings.worldSize.x; ++x) {
            double height = _heightMap[y][x];
            auto normal = _normalMap[y][x];
            Color fillColor;
            double sun = std::max(0., dot_prod(_sunLight, normal));
            double moon = std::max(0., dot_prod(_moonLight, normal));
            double light = _starBrightness + sun * _sunBrightness + moon * _moonBrightness;

            if (height < 0) {
                double depth = std::max(0., 1 + height / 100);
                double sunLight1 = std::max(0., dot_prod(_sunLight, Vec3d(0, 0, 1)));
                double light1 = _starBrightness + sunLight1 * _sunBrightness;
                fillColor = Color(70, 220, 250) * light * light1 * depth;
            } else {
                if (height > _snowHeight) {
                    fillColor = Color(250, 250, 250);
                } else if (height > _rockHeight) {
                    fillColor = Color(140, 140, 140);
                } else if (height > _grassHeight) {
                    fillColor = Color(60, 160, 70);
                } else {
                    fillColor = Color(250, 230, 150);
                }
                fillColor = fillColor * light;
            }
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
    if (_time >= _dayDuration) {
        _time -= _dayDuration;
    }
    double a = (_time / _dayDuration + 0.5) * 2 * ExtMath::PI;
    _sunLight = Vec3d(0, std::sin(a), std::cos(a));
    _moonLight = Vec3d(0, std::sin(a + ExtMath::PI), std::cos(a + ExtMath::PI));
}
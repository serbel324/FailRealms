#include "world.h"

#include <set>

World::World()
    : _time(0) 
{}

void World::Regenerate() {
    std::cout << "Generate" << std::endl;
    _tex.create(_settings.worldSize.x, _settings.worldSize.y);

    _heightNoise.Generate(_settings.heightNoiseSettings);
    _temperatureNoise.Generate(_settings.temperatureNoiseSettings);
    _humidityNoise.Generate(_settings.humidityNoiseSettings);

    _map.assign(_settings.worldSize.y + 1, std::vector<Cell>(_settings.worldSize.x + 1));
    // heights
    for (uint32_t y = 0; y < _settings.worldSize.y; ++y) {
        for (uint32_t x = 0; x < _settings.worldSize.x; ++x) {
            auto& cell = _map[y][x];
            Vec2d p = Vec2d{x, y} / _settings.worldSize;
            double height = _heightNoise(p);
            double is = _settings.islandSize;
            double island = -10 * (std::pow(p.x * 2 * is - is, 4) + std::pow(p.y * 2 * is - is, 4));
            cell.height = (height + island);
            cell.temperature = _temperatureNoise(p);
            cell.humidity = _humidityNoise(p);
        }
    }

    // normals
    for (uint32_t y = 0; y < _settings.worldSize.y; ++y) {
        for (uint32_t x = 0; x < _settings.worldSize.x; ++x) {
            _map[y][x].normal = GetNormal(x, y);
        }
    }

    // biomes
    for (uint32_t y = 0; y < _settings.worldSize.y; ++y) {
        for (uint32_t x = 0; x < _settings.worldSize.x; ++x) {
            auto& cell = _map[y][x];
            double slope = ExtMath::ToDegrees(angle(Vec3d{0, 0, 1}, cell.normal));
            std::vector<uint32_t> candidates;
            for (uint32_t i = 0; i < _settings.biomes.size(); ++i) {
                const auto& candidate = _settings.biomes[i];
                if (!candidate.heightBounds.Contain(cell.height)) {
                    continue;
                }
                if (!candidate.slopeBounds.Contain(slope)) {
                    continue;
                }
                if (!candidate.humidityBounds.Contain(cell.humidity)) {
                    continue;
                }
                if (!candidate.temperatureBounds.Contain(cell.temperature)) {
                    continue;
                }
                candidates.push_back(i);
            }
            assert(!candidates.empty());
            cell.biome = *(candidates.begin());
        }
    }
}

void World::Generate(const Settings& settings) {
    _settings = settings;
    Regenerate();
}

void World::Render(Graphics* gr, Vec2<uint32_t> windowSize) {
    sf::Image imageTerrain;
    imageTerrain.create(_settings.worldSize.x, _settings.worldSize.y, sf::Color::Red);
    for (uint32_t y = 0; y < _settings.worldSize.y; ++y) {
        for (uint32_t x = 0; x < _settings.worldSize.x; ++x) {
            auto& cell = _map[y][x];
            Color fillColor;
            switch (_renderedLayer) {
            case Layer::SURFACE: {
                const auto& biome = _settings.biomes[cell.biome];

                auto lightReflected = [](Vec3d lightSource, Vec3d surfaceNormal, double brightness) {
                    return std::max(0., dot_prod(lightSource, surfaceNormal)) * brightness;
                };

                double light;
                switch (biome.surfaceType) {
                    case Settings::Biome::SurfaceType::NORMAL: {
                        light = lightReflected(_sunLight, cell.normal, _sunBrightness) +
                                lightReflected(_moonLight, cell.normal, _moonBrightness) +
                                _starBrightness;
                        break;
                    }
                    case Settings::Biome::SurfaceType::WATER: {
                        light = lightReflected(_sunLight, cell.normal, _sunBrightness) +
                                lightReflected(_moonLight, cell.normal, _moonBrightness) +
                                _starBrightness;
                        light *= std::exp(cell.height * 0.5) * 0.8;
                        double surfaceLight = lightReflected(_sunLight, Vec3d{0, 0, 1}, _sunBrightness) +
                                lightReflected(_moonLight, Vec3d{0, 0, 1}, _moonBrightness) +
                                _starBrightness;
                        light += surfaceLight * ExtMath::RandomDouble(0.9, 1);
                        break;
                    }
                    case Settings::Biome::SurfaceType::ICE: {
                        light = lightReflected(_sunLight, Vec3d{0, 0, 1}, _sunBrightness) +
                                lightReflected(_moonLight, Vec3d{0, 0, 1}, _moonBrightness) +
                                _starBrightness;
                        break;
                    }
                }

                fillColor = biome.surfaceColor * light * biome.surfaceAlbedo;
                break;
            }
            case Layer::TEMPERATURE: {
                double t = cell.temperature / 60 * 255;
                if (cell.temperature < 0) {
                    fillColor = Color(255 + t, 255 + t, 255);   
                } else {
                    fillColor = Color(255, 255 - t, 255 - t);   
                }
                break;
            }
            case Layer::HUMIDITY: {
                double t = cell.humidity / 100 * 255;
                fillColor = Color(255 - t, 255 - t, 255);
                break;
            }
            }

            // fillColor = Color(1, 1, 1) * (cell.humidity / 100 * 255);

            imageTerrain.setPixel(x, y, sf::Color(fillColor.r, fillColor.g, fillColor.b));
        }
    }
    
    _tex.update(imageTerrain);

    gr->DrawTexture(_tex, windowSize * 0.5, windowSize);
}

void World::Tick(double elapsedMs) {
    _time += elapsedMs;
    if (_time >= _settings.dayDuration) {
        _time -= _settings.dayDuration;
    }
    double a = (_time / _settings.dayDuration + 0.5) * 2 * ExtMath::PI;
    _sunLight = Vec3d(0, std::sin(a), std::cos(a));
    _moonLight = Vec3d(0, std::sin(a + ExtMath::PI), std::cos(a + ExtMath::PI));
}

void World::SetRenderedLayer(Layer layer) {
    _renderedLayer = layer;
}

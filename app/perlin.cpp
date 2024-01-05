#include "perlin.h"

void PerlinNoise::Generate(Settings settings) {
    _settings = settings;

    _layers.resize(_settings.depth);
    for (uint32_t i = 0; i < _settings.depth; ++i) {
        _layers[i].Generate(Vec2<uint32_t>(_settings.baseGridResolution * (1 << i), _settings.baseGridResolution * (1 << i)));
    }
}

double PerlinNoise::operator()(Vec2<double> p) {
    double res = 0;
    for (uint32_t i = 0; i < _settings.depth; ++i) {
        res += _layers[i](p * _settings.baseGridResolution * (1 << i)) * _settings.amplitudeGenerator(i);
    }
    return res;
}
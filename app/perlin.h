#pragma once

#include <cmath>
#include <vector>

#include <library/vec2.h>
#include <library/ext_math.h>

class PerlinNoise {
public:
    struct Settings {
        uint32_t depth = 5;
        uint32_t baseGridResolution = 8;
        std::function<double(uint32_t)> amplitudeGenerator = [](uint32_t) { return 1; };
        std::function<double(double)> transformerFunction = [](double x) { return x; };
    };

private:
    struct PerlinLayer {
        std::vector<std::vector<Vec2d>> gradients;
        Vec2u gridSize;

        void Generate(Vec2u size) {
            gridSize = size;
            gradients.assign(size.y + 2, std::vector<Vec2d>(size.x + 2, Vec2d(0, 0)));
            for (uint32_t y = 0; y < size.y + 1; ++y) {
                for (uint32_t x = 0; x < size.x + 1; ++x) {
                    double a = ExtMath::RandomDouble(0, 2 * ExtMath::PI);
                    gradients[y][x] = Vec2d(std::cos(a), std::sin(a));
                }
            }
        }

        double GetDotGrid(uint32_t ix, uint32_t iy, Vec2d p) {
            Vec2d dp = Vec2d(p.x - ix, p.y - iy);
            return dot_prod(dp, gradients[iy][ix]);
        }

        double operator()(Vec2d p) {
            uint32_t ix = std::floor(p.x);
            uint32_t iy = std::floor(p.y);
            double p00 = GetDotGrid(ix, iy, p);
            double p10 = GetDotGrid(ix + 1, iy, p);
            double p01 = GetDotGrid(ix, iy + 1, p);
            double p11 = GetDotGrid(ix + 1, iy + 1, p);
            return ExtMath::SmootherstepSquare(p00, p10, p01, p11, Vec2d(p.x - ix, p.y - iy));
        }
    };

public:
    PerlinNoise() = default;

    void Generate(Settings settings);
    double operator()(Vec2<double> p);

private:
    Settings _settings;
    std::vector<PerlinLayer> _layers;
};

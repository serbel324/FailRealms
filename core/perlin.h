#pragma once

#include <cmath>
#include <vector>

#include <util/vec2.h>
#include <util/ext_math.h>
#include <core/types.h>

class TPerlinNoise {
    struct TPerlinLayer {
        std::vector<std::vector<TVec2d>> Gradients;
        TVec2<ui32> GridSize;

        void Generate(TVec2<ui32> size) {
            GridSize = size;
            Gradients.assign(size.Y + 2, std::vector<TVec2d>(size.X + 2, TVec2d(0, 0)));
            for (ui32 y = 0; y < size.Y + 1; ++y) {
                for (ui32 x = 0; x < size.X + 1; ++x) {
                    double a = NExtMath::GetRandomDouble(0, 2 * NExtMath::PI);
                    Gradients[y][x] = TVec2d(std::cos(a), std::sin(a));
                }
            }
        }

        double GetDotGrid(ui32 ix, ui32 iy, TVec2d p) {
            TVec2d dp = TVec2d(p.X - ix, p.Y - iy);
            return dot_prod(dp, Gradients[iy][ix]);
        }

        double Get(TVec2d p) {
            ui32 ix = std::floor(p.X);
            ui32 iy = std::floor(p.Y);
            double p00 = GetDotGrid(ix, iy, p);
            double p10 = GetDotGrid(ix + 1, iy, p);
            double p01 = GetDotGrid(ix, iy + 1, p);
            double p11 = GetDotGrid(ix + 1, iy + 1, p);
            return NExtMath::SmootherstepSquare(p00, p10, p01, p11, TVec2d(p.X - ix, p.Y - iy));
        }
    };

public:
    TPerlinNoise() = default;

    void Generate(ui32 depth, ui32 baseGridSize, std::function<double(ui32)> amplitudes = {}) {
        Depth = depth;
        BaseGridSize = baseGridSize;
        Amplitudes = amplitudes;

        Layers.resize(depth);
        for (ui32 i = 0; i < depth; ++i) {
            Layers[i].Generate(TVec2<ui32>(BaseGridSize * (1 << i), BaseGridSize * (1 << i)));
        }
    }

    double Get(TVec2<double> p) {
        double res = 0;
        for (ui32 i = 0; i < Depth; ++i) {
            res += Layers[i].Get(p * BaseGridSize * (1 << i)) * Amplitudes(i);
        }
        return res;
    }

private:
    ui32 Depth;
    ui32 BaseGridSize;
    std::vector<TPerlinLayer> Layers;
    std::function<double(ui32)> Amplitudes;
};

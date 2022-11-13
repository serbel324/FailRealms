#pragma once

#include <algorithm>
#include <vector>

#include <util/vec2.h>
#include <util/vec3.h>
#include <util/ext_math.h>

#include <core/types.h>
#include <core/perlin.h>

#include <core/graphics.h>

class TWorld {
public:
    TWorld() = default;

    void Generate(TVec2<ui32> size) {
        Size = size;
        {
            ui32 worldDepth = 8;
            ui32 baseGridSize = 4;
            auto amplitudes = [=](ui32 x) {
                return std::pow(2, worldDepth - 1 - x) * 2;
            };
            MainNoise.Generate(worldDepth, baseGridSize, amplitudes);
        }
        {
            ui32 worldDepth = 4;
            ui32 baseGridSize = 4;
            auto amplitudes = [=](ui32 x) {
                return std::pow(3, worldDepth - x) * 3;
            };
            MountainNoise.Generate(worldDepth, baseGridSize, amplitudes);
        }

        HeightMap.assign(Size.Y + 1, std::vector<double>(Size.X + 1));
        for (ui32 x = 0; x < Size.X; ++x) {
            for (ui32 y = 0; y < Size.Y; ++y) {
                TVec2d p(1. * x / Size.X, 1. * y / Size.Y);
                double noise = MainNoise.Get(p);
                double sign = NExtMath::Sign(noise);
                double mainNoise = sign * std::pow(std::abs(noise / 200), 2.5) * 200;
              //  double mountains = MountainNoise.Get(p);
                double island = (1 - std::pow(p.X * 4 - 2, 4) - std::pow(p.Y * 4 - 2, 4)) * 10;
                HeightMap[y][x] = (mainNoise + island) / 5;
            }
        }
    }

    void Render(TGraphics::SPtr gr, double scale) {
        for (ui32 x = 0; x < Size.X; ++x) {
            for (ui32 y = 0; y < Size.Y; ++y) {
                double height = HeightMap[y][x];
                auto normal = GetNormal(x, y);
                double sunLight = std::max(0., dot_prod(SunLight, normal));
                double moonLight = std::max(0., dot_prod(MoonLight, normal));
                double light = 0.1 + 0.9 * (sunLight + moonLight * MoonIntensity);

                if (height < 0) {
                    double depth = std::max(0., 1 + height / 100);
                    gr->SetFillColor(TColor(70, 220, 250) * (0.1 + 0.9 * std::pow(depth * light, 3)));
                } else {
                    TColor fillColor;
                    if (height > SnowHeight) {
                        fillColor = TColor(250, 250, 250);
                    } else if (height > RockHeight) {
                        fillColor = TColor(140, 140, 140);
                    } else if (height > GrassHeight) {
                        fillColor = TColor(60, 160, 70);
                    } else {
                        fillColor= TColor(250, 230, 150);
                    }
                    gr->SetFillColor(fillColor * light);
                }
                gr->DrawRect(TVec2f(x, y) * scale, TVec2f(scale, scale));
            }
        }
    }

    void Tick(double dtime) {
        Time += dtime;
        double a = Time / 3000;
        SunLight = TVec3d(0, std::sin(a), std::cos(a));
        MoonLight = TVec3d(0, std::sin(a + NExtMath::PI), std::cos(a + NExtMath::PI));
    }

private:
    double GetHeight(ui32 x, ui32 y) {
        return HeightMap[y][x];
    }

    TVec3d GetNormal(ui32 x, ui32 y) {
        TVec3d p(x, y, HeightMap[y][x]);
        TVec3d p10(x + 1, y, HeightMap[y][x + 1]);
        TVec3d p01(x, y + 1, HeightMap[y + 1][x]);
        return cross_prod(p10 - p, p01 - p).norm();
    }

    double Time = 0;
    TVec3d SunLight;
    TVec3d MoonLight;
    double MoonIntensity = 0.1;

    double GrassHeight = 1;
    double RockHeight = 3;
    double SnowHeight = 10;

    TVec2<ui32> Size;
    std::vector<std::vector<double>> HeightMap;
    TPerlinNoise MainNoise;
    TPerlinNoise MountainNoise;
};
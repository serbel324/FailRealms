#include "parse_config.h"
#include <library/ext_math.h>
#include <nlohmann/json.hpp>

using Biome = World::Settings::Biome;
using LightSource = World::Settings::Biome;
using namespace REngine;
using namespace ExtMath;


#define GET_IF_PRESENT(var, name) if (json.contains(name)) { var = json[name]; }
#define PARSE_IF_PRESENT(var, name) if (json.contains(name)) { Parse(var, json[name]); }

template<class T>
void Parse(T& var, const Json&/* json*/) {}

template<typename T>
void Parse(Vec2<T>& var, const Json& json) {
    GET_IF_PRESENT(var.x, "width") else
    GET_IF_PRESENT(var.x, "w") else
    GET_IF_PRESENT(var.x, "x")

    GET_IF_PRESENT(var.y, "height") else
    GET_IF_PRESENT(var.y, "h") else
    GET_IF_PRESENT(var.y, "y")
}

template<typename T>
void Parse(Bounds<T>& bounds, const Json& json) {
    GET_IF_PRESENT(bounds.min, "min")
    GET_IF_PRESENT(bounds.max, "max")
}

template<>
void Parse(Color& var, const Json& json) {
    GET_IF_PRESENT(var.r, "red") else
    GET_IF_PRESENT(var.r, "r")

    GET_IF_PRESENT(var.g, "green") else
    GET_IF_PRESENT(var.g, "g")

    GET_IF_PRESENT(var.b, "blue") else
    GET_IF_PRESENT(var.b, "b")
}

template<>
void Parse(Biome& var, const Json& json) {
    GET_IF_PRESENT(var.name, "name")
    PARSE_IF_PRESENT(var.heightBounds, "height_bounds")
    GET_IF_PRESENT(var.surfaceAlbedo, "surface_albedo")
    PARSE_IF_PRESENT(var.surfaceColor, "surface_color")
    PARSE_IF_PRESENT(var.slopeBounds, "slope_bounds")
    GET_IF_PRESENT(var.water, "water")
}

template<>
void Parse(ExtMath::Polynomial<double>& poly, const Json& json) {
    std::vector<uint32_t> powers;
    std::vector<double> coeffs;

    for (const auto& p : json["powers"]) {
        powers.push_back(p);
    }

    for (const auto& c : json["coefficients"]) {
        coeffs.push_back(c);
    }

    for (uint32_t i = 0; i < powers.size() && i < coeffs.size(); ++i) {
        poly.coefficients.emplace_back(powers[i], coeffs[i]);
    }
}

template<typename Callback>
void ParseNoiseTransformer(Callback& callback, const Json& json) {
    double magnitude = 1;
    double variable_amplifier = 1;
    double base = 1;
    GET_IF_PRESENT(magnitude, "magnitude")
    GET_IF_PRESENT(variable_amplifier, "variable_amplifier")
    GET_IF_PRESENT(base, "base")

    if (json.contains("polynomial")) {
        ExtMath::Polynomial poly;
        Parse(poly, json["polynomial"]);
        callback = [=](double x) {
            return ExtMath::ModuleStepFunction(poly(x * variable_amplifier)) * magnitude + base;
        };
    } else {
        callback = [=](double x) {
            return ExtMath::ModuleStepFunction(x * variable_amplifier) * magnitude + base;
        };
    }
}

template<>
void Parse(PerlinNoise::Settings& settings, const Json& json) {
    if (json.contains("transformer_function")) {
        ParseNoiseTransformer(settings.transformerFunction, json["transformer_function"]);
    }
    GET_IF_PRESENT(settings.depth, "depth");
    settings.amplitudeGenerator = [=](uint32_t x) {
        return std::pow(2, settings.depth - 1 - x) * 2;
    };
    GET_IF_PRESENT(settings.baseGridResolution, "base_grid_resolution");
}

Config ParseConfig(const Json& json) {
    World::Settings settings;

    PARSE_IF_PRESENT(settings.worldSize, "world_size")
    GET_IF_PRESENT(settings.dayDuration, "day_duration")
    PARSE_IF_PRESENT(settings.heightNoiseSettings, "height_noise")
    PARSE_IF_PRESENT(settings.temperatureNoiseSettings, "temperature_noise")

    for (const auto& b : json["biomes"]) {
        Biome biome;
        Parse(biome, b);
        settings.biomes.push_back(biome);
    }
    assert(!settings.biomes.empty());

    return settings;
}

#undef GET_IF_PRESENT
#undef PARSE_IF_PRESENT

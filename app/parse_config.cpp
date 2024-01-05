#include "parse_config.h"

#include <nlohmann/json.hpp>

TConfig ParseConfig(TJson json) {
    World::Settings settings;

	if (json.contains("world_size")) {
		settings._worldSize = Vec2i(json["world_size"]["width"], json["world_size"]["height"]);
	}

	if (json.contains("main_noise")) {
		const auto& daySettings = json["main_noise"];
		if (daySettings.contains("day_duration")) {
			settings._dayDuration = json["day_duration"];
		}
	}

	if (json.contains("day_night_cycle")) {
		const auto& daySettings = json["day_night_cycle"];
		if (daySettings.contains("day_duration")) {
			settings._dayDuration = json["day_duration"];
		}
	}

	if (json.contains("biomes")) {
		const auto& daySettings = json["day_night_cycle"];
		if (json.contains("day_duration")) {
			settings._dayDuration = json["day_duration"];
		}
	}

    return settings;
}
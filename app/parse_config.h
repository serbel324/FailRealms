#include "world.h"

#include <nlohmann/json.hpp>

using Json = nlohmann::json;
using Config = World::Settings;

Config ParseConfig(const Json& json);

#include <app/world.h>

#include <nlohmann/json.hpp>

using TJson = nlohmann::json;
using TConfig = World::Settings;

TConfig ParseConfig(TJson json);
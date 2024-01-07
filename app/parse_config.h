#include "world.h"
#include <string>

using Config = World::Settings;

Config ParseConfigFromFile(const std::string& path);

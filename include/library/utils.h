#pragma once

#include <memory>

template <typename T>
class SmartPointerAliases {
public:
    using UPtr = std::unique_ptr<T>;
    using SPtr = std::shared_ptr<T>;
    using WPtr = std::weak_ptr<T>;
};

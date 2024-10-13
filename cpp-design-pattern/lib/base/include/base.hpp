#pragma once

#include <cstddef>
namespace DesignPatternBase
{
template <typename F>
void repeat(size_t n, F f) {
    while (n--) f();
}
} // namespace DesignPatternBase

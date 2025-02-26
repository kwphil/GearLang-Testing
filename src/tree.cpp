#include <functional>
#include <vector>
#include "compiler.cpp"

#pragma once

namespace std_gearlang {
    template<class Signature>
    using ParserList = std::vector<std::function<Signature>>;
}
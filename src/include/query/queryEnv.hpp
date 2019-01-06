#pragma once

#include <sol.hpp>

#include "query.hpp"

namespace PanCake
{
    [[nodiscard]] std::string runQuery(PanCake::Query&,sol::state&);
    [[nodiscard]] bool setupEnv(PanCake::Query&,sol::state&);
}

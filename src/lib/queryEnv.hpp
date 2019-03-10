#pragma once

#define SOL_PRINT_ERRORS 1
#include <sol.hpp>

#include "query.hpp"

namespace PanCake
{
    [[nodiscard]] std::string runQuery(PanCake::Query&,sol::state&);
    void printEnv(PanCake::Query&,sol::state&);
    [[nodiscard]] bool setupEnv(PanCake::Query&,sol::state&);
}

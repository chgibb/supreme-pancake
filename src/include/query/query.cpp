#include <sol.hpp>

#include "query.hpp"
#include "queryEnv.hpp"

namespace
{
    sol::state defualtLuaInit()
    {
        sol::state lua;
        lua.open_libraries(sol::lib::base);
        return lua;
    }
}

[[nodiscard]] std::string PanCake::Query::runQueryFromFile(std::string filePath)
{
    sol::state lua = defualtLuaInit();

    lua.script_file(filePath.c_str());

    if(!PanCake::setupEnv(*this,lua))
        return "";
    return PanCake::runQuery(*this,lua);
}

[[nodiscard]] std::string PanCake::Query::runQueryFromString(std::string filePath)
{
    sol::state lua = defualtLuaInit();

    lua.script(filePath.c_str());

    if(!PanCake::setupEnv(*this,lua))
        return "";
    return PanCake::runQuery(*this,lua);
}
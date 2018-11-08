#pragma once

#include <istream>
#include <string>

#include <rapidjson/document.h>
#include <rapidjson/istreamwrapper.h>
#include <rapidjson/ostreamwrapper.h>
#include <rapidjson/prettywriter.h>

namespace PanCake
{
    rapidjson::GenericDocument<rapidjson::UTF8<>> loadJSONFromStream(std::istream&);
    rapidjson::GenericDocument<rapidjson::UTF8<>> loadJSONFromString(std::string&);
}
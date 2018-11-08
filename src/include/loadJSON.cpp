#include "loadJSON.hpp"

rapidjson::GenericDocument<rapidjson::UTF8<>> PanCake::loadJSONFromStream(std::istream&stream)
{
    rapidjson::GenericDocument<rapidjson::UTF8<>> document;
    rapidjson::IStreamWrapper jsonStream(stream);
    document.ParseStream(jsonStream);
    return document;
}

rapidjson::GenericDocument<rapidjson::UTF8<>> PanCake::loadJSONFromString(std::string&str)
{
    rapidjson::GenericDocument<rapidjson::UTF8<>> document;
    document.Parse(str.c_str());
    return document;
}
#include "loadJSONFromStream.hpp"

rapidjson::GenericDocument<rapidjson::UTF8<>> PanCake::loadJSONFromStream(std::istream&stream)
{
    rapidjson::GenericDocument<rapidjson::UTF8<>> document;
    rapidjson::IStreamWrapper jsonStream(stream);
    document.ParseStream(jsonStream);
    return document;
}
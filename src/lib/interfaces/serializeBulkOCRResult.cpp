#include <rapidjson/document.h>
#include <rapidjson/ostreamwrapper.h>
#include <rapidjson/writer.h>

#include "serializeBulkOCRResult.hpp"

[[nodiscard]] std::string PanCake::serializeBulkOCRResult(PanCake::BulkOCRResult&result)
{
    rapidjson::GenericDocument<rapidjson::UTF8<>> doc;
    doc.SetObject();
    rapidjson::Document::AllocatorType& allocator = doc.GetAllocator();

    doc.AddMember("attempted",rapidjson::Value(result.attempted),allocator);

    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    doc.Accept(writer);

    return std::string(buffer.GetString(),buffer.GetSize());
}


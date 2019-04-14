#include <rapidjson/document.h>
#include <rapidjson/ostreamwrapper.h>
#include <rapidjson/writer.h>

#include "serializeOCRResult.hpp"

[[nodiscard]] std::string PanCake::serializeOCRResult(PanCake::OCRResult&result)
{
    rapidjson::GenericDocument<rapidjson::UTF8<>> doc;
    doc.SetObject();
    rapidjson::Document::AllocatorType& allocator = doc.GetAllocator();

    doc.AddMember("text",rapidjson::StringRef(result.text.c_str()),allocator);
    doc.AddMember("lang",rapidjson::StringRef(result.lang.c_str()),allocator);
    doc.AddMember("comparativeSentimentScore",rapidjson::Value(result.comparativeSentimentScore),allocator);
    doc.AddMember("sentimentScore",rapidjson::Value(result.sentimentScore),allocator);

    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    doc.Accept(writer);

    return std::string(buffer.GetString(),buffer.GetSize());
}


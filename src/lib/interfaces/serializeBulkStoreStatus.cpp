#include <algorithm>

#include <rapidjson/document.h>
#include <rapidjson/ostreamwrapper.h>
#include <rapidjson/writer.h>

#include "serializeBulkStoreStatus.hpp"

[[nodiscard]] std::string PanCake::serializeBulkStoreStatus(PanCake::BulkStoreStatus&status)
{
    rapidjson::GenericDocument<rapidjson::UTF8<>> doc;
    doc.SetObject();
    rapidjson::Document::AllocatorType& allocator = doc.GetAllocator();

    doc.AddMember("added",rapidjson::Value(status.added),allocator);
    doc.AddMember("duplicates",rapidjson::Value(status.duplicates),allocator);
    doc.AddMember("metaUpdates",rapidjson::Value(status.metaUpdates),allocator);
    doc.AddMember("savedImages",rapidjson::Value(status.savedImages),allocator);
    doc.AddMember("success",rapidjson::Value(status.success),allocator);

    rapidjson::Value binsWithNewTweets(rapidjson::kArrayType);
    std::for_each(
        status.binsWithNewTweets.begin(),
        status.binsWithNewTweets.end(),
        [&binsWithNewTweets,&allocator](const std::string&str) -> void {
            binsWithNewTweets.PushBack(rapidjson::StringRef(str.c_str()),allocator);
    });

    doc.AddMember("binsWithNewTweets",binsWithNewTweets,allocator);

    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    doc.Accept(writer);

    return std::string(buffer.GetString(),buffer.GetSize());
}


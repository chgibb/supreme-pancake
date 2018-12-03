#include <fstream>
#include <algorithm>
#include <experimental/filesystem>

#include <rapidjson/ostreamwrapper.h>
#include <rapidjson/prettywriter.h>

#include "nerTagBin.hpp"
#include "loadJSON.hpp"
#include "directoryExists.hpp"

[[nodiscard]] std::string PanCake::makeNERStorageBinHash(std::string token)
{
    if(token.size() >= 3)
        return std::string("") + token[0] + token[1] + token[2];
    else if(token.size() >= 2)
        return std::string("") + token[0] + token[1];
    else if(token.size() == 1)
        return std::string("") + token[0];
    return "";
}

[[nodiscard]] std::string PanCake::makeNERStorageBinPath(const char*dataDirectory,std::string token)
{
    return std::string(dataDirectory) + std::string("/") + PanCake::makeNERStorageBinHash(token) + std::string(".json");
}

PanCake::NERTagBin::NERTagBin(std::string binPath,std::string binFileName)
{
    this->binPath = binPath;
    this->binFileName = binFileName;
}

[[nodiscard]] bool PanCake::NERTagBin::saveBin()
{
    rapidjson::GenericDocument<rapidjson::UTF8<>> doc(rapidjson::kArrayType);
    rapidjson::Document::AllocatorType& allocator = doc.GetAllocator();

    std::for_each(
        this->tags.begin(),
        this->tags.end(),
        [&doc,&allocator](const PanCake::NERTagBin::NERTag&tag) -> void {
            rapidjson::Value val(rapidjson::kObjectType);

            val.AddMember("token",rapidjson::StringRef(tag.token.c_str()),allocator);
            val.AddMember("entity",rapidjson::StringRef(tag.entity.c_str()),allocator);
            doc.PushBack(val,allocator);
    });

    if(!PanCake::directoryExists(this->binPath.c_str()))
    {
        std::experimental::filesystem::create_directories(this->binPath);
    }

    std::ofstream file(this->binFileName);
    if(file.fail())
        return false;
    
    rapidjson::OStreamWrapper osw(file);
    rapidjson::PrettyWriter<rapidjson::OStreamWrapper> writer(osw);
    return doc.Accept(writer);
}

[[nodiscard]] bool PanCake::NERTagBin::loadBin()
{
    std::ifstream file(this->binFileName.c_str());
    
    if(file.fail())
        return false;

    rapidjson::GenericDocument<rapidjson::UTF8<>> doc = PanCake::loadJSONFromStream(file);

    for(auto it = doc.Begin(); it != doc.End(); ++it)
    {
        this->tags.push_back({
            (*it)["token"].GetString(),
            (*it)["entity"].GetString()
        });
    }

    return true;
}

void PanCake::NERTagBin::addTag(std::string token,std::string entity)
{
    this->tags.push_back({token,entity});
}

[[nodiscard]] bool PanCake::NERTagBin::tagExists(std::string token)
{
    auto end = this->tags.end();
    for(auto it = this->tags.begin(); it != end; ++it)
    {
        if(it->token == token)
            return true;
    }
    return false;
}

[[nodiscard]] std::string PanCake::NERTagBin::getTagType(std::string token)
{
    auto end = this->tags.end();
    for(auto it = this->tags.begin(); it != end; ++it)
    {
        if(it->token == token)
            return it->entity;
    }
    return "";
}

void PanCake::NERTagBin::initAsEmptyBin()
{

}
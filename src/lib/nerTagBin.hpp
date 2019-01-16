#pragma once

#include <string>
#include <vector>

#include <rapidjson/document.h>

namespace PanCake
{
    [[nodiscard]] std::string makeNERStorageBinHash(std::string);
    [[nodiscard]] std::string makeNERStorageBinPath(const char*,std::string);

    class NERTagBin
    {
        public:
            NERTagBin(std::string,std::string);
            ~NERTagBin() = default;
            struct NERTag
            {
                std::string token;
                std::string entity;
            };

            [[nodiscard]] bool saveBin();
            [[nodiscard]] bool loadBin();
            void addTag(std::string,std::string);
            [[nodiscard]] bool tagExists(std::string);
            [[nodiscard]] std::string getTagType(std::string);
            void initAsEmptyBin();

        private:
            std::string binPath;
            std::string binFileName;
            std::vector<PanCake::NERTagBin::NERTag> tags;
    };
}
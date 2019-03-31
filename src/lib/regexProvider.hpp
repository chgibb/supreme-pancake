#pragma once
#include <vector>
#include <string>
#include <regex.h>

namespace PanCake
{
    class RegexProvider
    {
        public:
            RegexProvider() = default;
            ~RegexProvider();
            
            void addRegex(std::string);
            bool match(int,std::string);

        private:
            std::vector<::regex_t> regexs;
    };
}


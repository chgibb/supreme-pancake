#include <iostream>

#include "vendor/cxxopts/include/cxxopts.hpp"

#include "lib/OCRTweetBin.hpp"
#include "lib/bulkOCRResult.hpp"
#include "lib/serializeBulkOCRResult.hpp"
#include "lib/loadJSON.hpp"

int main(int argc,char*argv[])
{
    cxxopts::Options options("OCRTweetBins", "Extract text from images in given bins");

    options.add_options()("d,dir","Storage directory path",cxxopts::value<std::string>());

    auto result = options.parse(argc,argv);

    std::string storageDir = result["dir"].as<std::string>();

    std::string raw;

    std::getline(std::cin,raw);

    auto json = PanCake::loadJSONFromString(raw);

    PanCake::BulkOCRResult res;

    for(const auto&binPath : json.GetArray())
    {
        PanCake::BulkOCRResult curRes = PanCake::OCRTweetBin(storageDir.c_str(),binPath.GetString());

        res.attempted += curRes.attempted;
    }

    std::cout<<PanCake::serializeBulkOCRResult(res);
    std::cout.flush();

    return 0;
}

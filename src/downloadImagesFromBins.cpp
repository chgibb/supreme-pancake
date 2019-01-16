#include <iostream>
#include <string>
#include <algorithm>

#include "vendor/cxxopts/include/cxxopts.hpp"

#include "lib/loadJSON.hpp"
#include "lib/tweetBin.hpp"
#include "lib/loadTweetBin.hpp"
#include "lib/saveTweetBin.hpp"
#include "lib/downloadImagesFromBin.hpp"
#include "lib/OCRImage.hpp"

int main(int argc,char*argv[])
{
    cxxopts::Options options("downloadImagesFromBins", "Download images from tweets in the given list of bins");

    options.add_options()("d,dir","Storage directory path",cxxopts::value<std::string>());

    auto result = options.parse(argc,argv);

    std::string storageDir = result["dir"].as<std::string>();

    std::string raw;
    
    std::getline(std::cin,raw);
    
    auto json = PanCake::loadJSONFromString(raw);

    PanCake::BulkImageDownloadStatus dlStatus;

    for(const auto&binPath : json.GetArray())
    {
        PanCake::TweetBin*bin = PanCake::loadTweetBin(binPath.GetString());

        PanCake::BulkImageDownloadStatus binStatus = PanCake::downloadImagesFromBin(storageDir.c_str(),*bin);

        dlStatus.attempted += binStatus.attempted;
        dlStatus.succeeded += binStatus.succeeded;
        dlStatus.failed += binStatus.failed;

        bool saved = PanCake::saveTweetBin(*bin,binPath.GetString());
        if(!saved)
            return 1;

        delete bin;
    }
    
    std::cout<<"{\"attempted\":"<<dlStatus.attempted<<",\"succeeded\":"<<dlStatus.succeeded<<",\"failed\":"<<dlStatus.failed<<"}";

    std::cout.flush();

    return 0;
}
